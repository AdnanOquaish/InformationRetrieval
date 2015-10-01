#include "bigram.h"
#include "query.h"

bigram::bigram(){
	this->root = new bigramNode();
	this->wordCount = 0;
}

void bigram::incrementWordCount(){
	this->wordCount += 1;
}

int bigram::getWordCount(){
	return this->wordCount;
}

void bigram::insertWord(string word){
	string tempWord = '$'+word+'$';
	incrementWordCount();
	for(unsigned int i = 0; i < tempWord.length()-1; i++){
		bigramNode* node = root;
		if(node->findChild(tempWord[i]) == NULL){
			node = node->insertChild(tempWord[i]);
		}
		else{
			node = node->findChild(tempWord[i]);
		}
		if(node->findChild(tempWord[i+1]) == NULL){
			node = node->insertChild(tempWord[i+1]);
		}
		else{
			node = node->findChild(tempWord[i+1]);
		}
		node->setIsWord();
		node->insertWord(word);
	}
}

void bigram::checkWord(string& word){
	string tempWord = '$'+word+'$';
	for(unsigned int i = 0; i < tempWord.length()-1; i++){
		bigramNode* node = root;
		if(node->findChild(tempWord[i]) == NULL){
			continue;
		}
		else{
			node = node->findChild(tempWord[i]);
		}
		if(node->findChild(tempWord[i+1]) == NULL){
			continue;
		}
		else{
			node = node->findChild(tempWord[i+1]);
		}
		set<string> words = node->getWordList();
		set<string>::iterator itr;
		for(itr = words.begin(); itr != words.end(); itr++){
			if(correct.find(*itr) == correct.end()){
				correct[*itr] = 1.0;
			}
			else{
				correct[*itr] += 1.0;
			}
		}
	}
	map<string, double>:: iterator it;
	for(it = correct.begin(); it != correct.end(); it++){
		//cout << it->second << endl;
		it->second /= ((it->first).length()+1) + (word.length()+1) - it->second; 
	}
	printCorrectWord(word);
	correct.clear();
}

void bigram::printCorrectWord(string& word){
	map<string, double>:: iterator itr;
	double jaccard = 0.0;
	string correctWord;
	for(itr = correct.begin(); itr != correct.end(); itr++){
		if(itr->second > jaccard){
			jaccard = itr->second;
			correctWord = itr->first;
		}
	}		
	//cout << jaccard << endl;
	if(jaccard > 0.45){
		word = correctWord;
	}	
}

void bigram::wildCardQuery(query* q, string word){
	if(word[0] != '*'){
		word = '$'+word;
	}
	if(word[word.length()-1] != '*'){
		word = word + '$';
	}
	if(word[0] == '*'){
		word = word.substr(1, word.length()-1);
	}
	if(word[word.length()-1] == '*'){
		word = word.substr(0, word.length()-1);
	}
	for(unsigned int i = 0; i < word.length()-1; i++){
		bigramNode* node = root;
		if(node->findChild(word[i]) == NULL){
			continue;
		}
		else{
			node = node->findChild(word[i]);
		}
		if(node->findChild(word[i+1]) == NULL){
			continue;
		}
		else{
			node = node->findChild(word[i+1]);
		}
		set<string> words = node->getWordList();
		set<string>::iterator itr;
		for(itr = words.begin(); itr != words.end(); itr++){
			if(correct.find(*itr) == correct.end()){
				correct[*itr] = 1.0;
			}
			else{
				correct[*itr] += 1.0;
			}
		}
	}
	map<string, double>:: iterator it;
	for(it = correct.begin(); it != correct.end(); it++){
		if(it->second == word.length()-1){
			q->insertProcessedQueries(word);	
		}
	}
	correct.clear();
}
