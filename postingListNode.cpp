#include <cmath>
#include "postingListNode.h"

PostingListNode::PostingListNode(int docId){
    this->docId = docId;
    this->termFreq = 1;
    computeLogTermFreq();
}

int PostingListNode::getDocId(){
    return this->docId;
}

void PostingListNode::incrementTermFreq(){
    this->termFreq += 1;
}

int PostingListNode::getTermFreq(){
    return this->termFreq;
}

void PostingListNode::computeLogTermFreq(){
    this->logTermFreq = 1 + log10(this->termFreq);
}

double PostingListNode::getLogTermFreq(){
    return this->logTermFreq;
}

double PostingListNode::getTermFreqInvDocFreq(){
    return this->termFreqInvDocFreq;
}

double PostingListNode::getTermFreqInvDocFreqSqr(){
    return (this->termFreqInvDocFreq) * (this->termFreqInvDocFreq);
}

void PostingListNode::computeTermFreqInvDocFreq(double invDocFreq){
    this->termFreqInvDocFreq = (this->logTermFreq) * (invDocFreq);
}

void PostingListNode::insertWordPos(){
    this->position.insert(wordCount);
}

const set<int> & PostingListNode::getPositionSet(){
    return this->position;
}
