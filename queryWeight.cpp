#include <cmath>
#include "queryWeight.h"

QueryWeights::QueryWeights(){
	termFreq = 0;
	docFreq = 0;
	logTermFreq = 0;
	invDocFreq = 0;
	weight = 0;
}

int QueryWeights::getTermFreq(){
	return this->termFreq;
}

void QueryWeights::incrementTermFreq(){
	this->termFreq += 1;
}

int QueryWeights::getDocFreq(){
	return this->docFreq;
}

void QueryWeights::setDocFreq(int docFreq){
	this->docFreq = docFreq;
}


double QueryWeights::getLogTermFreq(){
	return logTermFreq;
}

double QueryWeights::getInvDocFreq(){
	return invDocFreq;
}

double QueryWeights::getWeight(){
	return weight;
}


void QueryWeights::computeLogTermFreq(){
	logTermFreq = log10(termFreq) + 1;
}

void QueryWeights::setInvDocFreq(double invDocFreq){
	this->invDocFreq = invDocFreq;
}

void QueryWeights::computeWeight(){
	weight = logTermFreq*invDocFreq;
}