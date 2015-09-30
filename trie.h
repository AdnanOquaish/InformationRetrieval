#include "trieNode.h"

using namespace std;

class Trie{

private:
	TrieNode* root;
	int wordCount;

public:
	Trie();

	void incrementWordCount();

	int getWordCount();

	TrieNode* findWord(string word);
	
	void insertWord(string word);

	void computeWeights();

	void instantiateDocMagn();
};

extern Trie* dict;

void index(const char* fileName);