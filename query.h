#include "queryWeight.h"

using namespace std;

class Query{

private:
	string unprocessedQuery;
	map< string, QueryWeights* > processedQueries;
	map< int,double > answer; 
	Trie* trie;
	double magnitude;

public:
	Query(Trie* trie);

	double getMagnitude();

	void inputQuery();

	void insertProcessedQueries(string queryToken);

	void queryMagnitude();

	void cosineSimilarity();

	void phraseQuery();

	void printCosineSimilarity();
};