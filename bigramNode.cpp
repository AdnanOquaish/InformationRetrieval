#include "bigramNode.h"

bigramNode::bigramNode(){
	this->isWord = false;
	this->alphabet = '\0';
}

bigramNode::bigramNode(char alph){
	this->alphabet = alph;
	this->isWord = false;
}

bigramNode* bigramNode::insertChild(char alph){
	bigramNode* node = new bigramNode(alph);
	this->children[alph] = node;
	return node;
}


bigramNode* bigramNode::findChild(char alph){
	if(this->children.find(alph) == this->children.end()){
		return NULL;
	}
	else{
		return this->children[alph];
	}
}

void bigramNode::setIsWord(){
	this->isWord = true;
}

void bigramNode::resetIsWord(){
	this->isWord = false;
}

bool bigramNode::getIsWord(){
	return this->isWord;
}

void bigramNode::setAlphabet(char alph){
	this->alphabet = alph;
}

char bigramNode::getAlphabet(){
	return this->alphabet;
}

void bigramNode::insertWord(string word){
	this->bigramList.push_front(word);
}

const list<string> & bigramNode::getWordList(){
    return this->bigramList;
}