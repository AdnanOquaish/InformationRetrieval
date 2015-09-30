#include <iostream>
#include <cstdlib>
#include <fstream>
#include "trie.h"
#include "porter2_stemmer.h"
#include "bigram.h"

Trie::Trie(){
	root = new TrieNode();
	this->wordCount = 0;
}

void Trie::incrementWordCount(){
	this->wordCount += 1;
}

int Trie::getWordCount(){
	return this->wordCount;
}

TrieNode* Trie::findWord(string word){
	TrieNode* node = root;
	for(unsigned int i = 0; i < word.length(); i++){
		if(node->findChild(word[i]) == NULL){
			return NULL;
		}
		else{
			node = node->findChild(word[i]);
		}
		if(i == word.length()-1){
			if(node->getIsWord() == true){
				return node;
			}
			else{
				return NULL;
			}
		}
	}
}

void Trie::insertWord(string word){
	incrementWordCount();
	TrieNode* node = root;
	for(unsigned int i = 0; i < word.length(); i++){
		if(node->findChild(word[i]) == NULL){
			node = node->insertChild(word[i]);
		}
		else{
			node = node->findChild(word[i]);
		}
	}
	node->setIsWord();
	node->instantiatePostingList(word);
	node->setDocFreq();
}

void Trie::computeWeights(){
	instantiateDocMagn();
	cout << "documentMagnitude instantiated" << endl;
	this->root->computeWeight();
	cout << "all weights computed" << endl;
}

void Trie::instantiateDocMagn(){
	documentMagnitude = (double *) calloc(sizeof(double),totalDocs+10);
}

void index(const char* fileName){
	ifstream fIn;
	fIn.open(fileName);
	string document;
	while(getline(fIn, document)){
		wordCount = 0;
		totalDocs++;
		cout << "DocId: " << totalDocs << " indexed"<< endl;
		std::size_t prev = 0, pos;
		string word;
	    while ((pos = document.find_first_of(" ';,.-_<=>^()[]\t\r\n\v\f", prev)) != std::string::npos){
	        if (pos > prev){
	        	word = document.substr(prev, pos-prev);
	        	Porter2Stemmer::stem(word);
	        	wordCount++;
	        	dict->insertWord(word);
	        	bg->insertWord(word);
	        }
	        prev = pos+1;
	    }
	    if (prev < document.length()){
	    	word = document.substr(prev, std::string::npos);
	    	Porter2Stemmer::stem(word);
	    	wordCount++;
	        dict->insertWord(word);
	        bg->insertWord(word);
	    }
	}
}