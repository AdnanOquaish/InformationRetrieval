#include "postingList.h"

PostingList::PostingList(int docId, string word){
    this->word = word;
    insertPostingListNode(docId);
}

void PostingList::setWord(string word){
    this->word = word;
}

string PostingList::getWord(){
    return this->word;
}

void PostingList::insertPostingListNode(int docId){
    PostingListNode* node;
    if(postingList.find(docId) == postingList.end()){
        node = new PostingListNode(docId);
        node->computeLogTermFreq();
        node->insertWordPos();
        postingList[docId] = node;
    } 
    else{
        node = postingList[docId];
        node->incrementTermFreq();
        node->insertWordPos();
        node->computeLogTermFreq();
    }
}

const map<int, PostingListNode*> & PostingList::getActualPostingList(){
    return this->postingList;
}


int PostingList::sizePostingList(){
    return this->postingList.size();
}

void PostingList::computeTermFreqInvDocFreqForAll(double invDocFreq){
    map<int, PostingListNode*> :: iterator it;
    for(it = this->postingList.begin(); it != this->postingList.end(); it++){
            (*it).second->computeTermFreqInvDocFreq(invDocFreq);
            documentMagnitude[(*it).first] += ((*it).second->getTermFreqInvDocFreqSqr());
    }
}