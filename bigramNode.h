#include <list>
#include <string>
#include <map>

using namespace std;

class bigramNode{

private:
	bool isWord;
	char alphabet;
	list<string> bigramList;
	map<char, bigramNode*> children;

public:
	bigramNode();

	bigramNode(char alph);

	bigramNode* insertChild(char alph);


	bigramNode* findChild(char alph);

	void setIsWord();

	void resetIsWord();

	bool getIsWord();

	void setAlphabet(char alph);

	char getAlphabet();

	void insertWord(string word);

	const list<string> & getWordList();
};
