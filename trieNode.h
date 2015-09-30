#include "postingList.h"

using namespace std;

class TrieNode{

private:
	char alphabet;
	bool isWord;
	int docFreq;
	double invDocFreq;
	PostingList* postingList;
	map<char, TrieNode*> children;

public:
	TrieNode();

	TrieNode(char alph);
	
	void setIsWord();

	void resetIsWord();

	bool getIsWord();
	
	void setAlphabet(char alph);

	char getAlphabet();
	
	void setDocFreq();

	int getDocFreq();

	void instantiatePostingList(string word);

	PostingList* getPostingList();

	void computeInvDocFreq();

	double getInvDocFreq();

	TrieNode* insertChild(char alph);

	TrieNode* findChild(char alph);

	void computeWeight();
};