#include "bigramNode.h"

using namespace std;

class bigram{
private:
	bigramNode* root;
	int wordCount;
	map<string, double> correct;

public:
	bigram();

	void incrementWordCount();

	int getWordCount();

	void insertWord(string word);

	void checkWord(string& word);

	void printCorrectWord(string& word);
	
	void wildCardQuery(query* q, string word);
};

extern bigram* bg;
