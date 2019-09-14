#include<bits/stdc++.h>
using namespace std;



class TrieNode
{
public:
    char data;
    map<char, TrieNode*> children;
    bool isTerminal;
    TrieNode(char data) : data(data), isTerminal(false) {}
};

class Trie
{
     TrieNode * root;
    void insertWordHelper(TrieNode * root, string & word, int index = 0)
    {
        if(index == word.size())
        {
            root -> isTerminal = true;
            //cout<<word<<endl;
            return;
        }
        if(root -> children.find(word[index]) == root -> children.end())
            root -> children[word[index]] = new TrieNode(word[index]);
        insertWordHelper(root -> children[word[index]], word, index + 1);
    }
    
    bool searchHelper(TrieNode * root, string & word, int index = 0)
    {
        if(index == word.size())
            return root -> isTerminal;
        if(root -> children.find(word[index]) == root -> children.end())
            return false;
        return searchHelper(root -> children[word[index]], word, index + 1);
    }
    
    void deleteWordHelper(TrieNode * root, string & word, int index = 0)
    {
        if(index == word.size())
            root -> isTerminal = false;
        if(root -> children.find(word[index]) == root -> children.end())
            return;
        deleteWordHelper(root -> children[word[index]], word, index + 1);
        if(root -> children.empty() && !root -> isTerminal)
            root -> children.erase(word[index]);
    }
public:
   
    Trie() : root(new TrieNode(char(0))) {}
    
    void insertWord(string & word)
    {
        insertWordHelper(this -> root, word);
    }
    
    bool search(string & word)
    {
        return searchHelper(this -> root, word);
    }
    
    void deleteWord(string & word)
    {
        deleteWordHelper(this -> root, word);
    }
    
    // This function takes string as an input and prints out all the words inserted in the trie which start with this string
    // For example: 
    // input string = "app"
    // Strings inserted in the trie = {"app", "apps", "apple", "aps"}
    // ouput = "app", "apps", "apple"
    
    
    void autoCompleteHelper (TrieNode * root, string currPrefix, vector<string> & ans){
    	
    	if(root->isTerminal) {
    		ans.push_back(currPrefix);
    	}
    	
    	if(root->children.empty()) return;
    	
    	for( auto i : root->children){
    	
    		currPrefix.push_back(i.first);
    	
        	autoCompleteHelper (root->children[i.first],currPrefix,ans);
        	currPrefix.pop_back();
    	}
    }
    
    
    
    vector<string> autoComplete(string & input, vector<string> & wordsToBeInserted)
    {
        

        for( string a : wordsToBeInserted) {

            this->insertWord(a);
        }
        
        
        TrieNode *temp = this->root;
        int len = input.length(),i;
        
        for( i=0; i<len; i++){
        
        	if(temp -> children.find(input[i]) == temp -> children.end()){
        	
        		return {};
        	}
        	
        	temp = temp->children[input[i]];
        }
        
        bool isWord = temp->isTerminal;
        vector<string> ans;
        //if(isWord) ans.push_back(input);
        
        autoCompleteHelper(temp,input,ans);
        
        return ans;
		
        

    }
};

int main() {
	
	
vector<string> words;
int n;
cin>>n;
string h;
while(n--){
	cin>>h;
	words.push_back(h);
}

cin>>h;
Trie T;
vector<string> pq = T.autoComplete(h,words);

for( string a : pq){
	cout<<a<<endl;
}


	
	
	
	return 0;
}
