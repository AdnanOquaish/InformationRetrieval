#include <cmath>
#include "trieNode.h"

TrieNode::TrieNode(){
	this->isWord = false;
	this->docFreq = 0;
	this->alphabet = '\0';
	this->postingList = NULL;
}

TrieNode::TrieNode(char alph){
	this->alphabet = alph;
	this->isWord = false;
	this->docFreq = 0;
	this->postingList = NULL;
}

void TrieNode::setIsWord(){
	this->isWord = true;
}

void TrieNode::resetIsWord(){
	this->isWord = false;
}

bool TrieNode::getIsWord(){
	return this->isWord;
}

void TrieNode::setAlphabet(char alph){
	this->alphabet = alph;
}

char TrieNode::getAlphabet(){
	return this->alphabet;
}

void TrieNode::setDocFreq(){
	this->docFreq = this->postingList->sizePostingList();
}

int TrieNode::getDocFreq(){
	return this->docFreq;
}

void TrieNode::instantiatePostingList(string word){
	if(this->postingList == NULL){
		this->postingList = new PostingList(totalDocs, word);
	}
	else{
		this->postingList->insertPostingListNode(totalDocs);
	}
}

PostingList* TrieNode::getPostingList(){
	return this->postingList;
}

void TrieNode::computeInvDocFreq(){
	this->invDocFreq = log10((double)totalDocs/(double)this->postingList->sizePostingList());
}
double TrieNode::getInvDocFreq(){
	return this->invDocFreq;
}

TrieNode* TrieNode::insertChild(char alph){
	TrieNode* node = new TrieNode(alph);
	this->children[alph] = node;
	return node;
}

TrieNode* TrieNode::findChild(char alph){
	if(this->children.find(alph) == this->children.end()){
		return NULL;
	}
	else{
		return this->children[alph];
	}
}

void TrieNode::computeWeight(){
	for(map<char, TrieNode*>::iterator itr = this->children.begin(); itr != this->children.end(); itr++){
		TrieNode* temp = (*itr).second;
		if(temp->isWord == true){
			temp->computeInvDocFreq();
			temp->postingList->computeTermFreqInvDocFreqForAll(temp->getInvDocFreq());
		}
		temp->computeWeight();
	}
}