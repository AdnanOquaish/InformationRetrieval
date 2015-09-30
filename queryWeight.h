#include "trie.h"

using namespace std;

class QueryWeights{

private:
	int termFreq;
	int docFreq;
	double logTermFreq;
	double invDocFreq; 
	double weight;

public:
	QueryWeights();

	int getTermFreq();

	void incrementTermFreq();

	int getDocFreq();

	void setDocFreq(int docFreq);

	double getLogTermFreq();

	double getInvDocFreq();

	double getWeight();

	void computeLogTermFreq();

	void setInvDocFreq(double invDocFreq);

	void computeWeight();
};
