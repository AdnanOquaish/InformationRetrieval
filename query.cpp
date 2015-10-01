#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include "query.h"
#include "porter2_stemmer.h"
#include "bigram.h"

Query::Query(Trie* trie){
	this->trie = trie;
	this -> magnitude = 0;
}

Query::~Query(){
	processedQueries.clear();
	answer.clear();
}


double Query::getMagnitude(){
	return this->magnitude;
}

void Query::inputQuery(){
	string typeQuery;
	cout << "\nType of query? p/n: ";
	cin >> typeQuery;
	if(typeQuery[0] == 'N' || typeQuery[0] == 'n'){
		cout << "\nInput your normal query: ";
		string query;
		cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, query);
		this->unprocessedQuery = query;
		cout << "\nprocessed query: ";
		std::size_t prev = 0, pos;
		string word;
	    while((pos = query.find_first_of(" '&:#!+;?/,.-_<=>^()[]\t\r\n\v\f", prev)) != std::string::npos){
	        if (pos > prev){
	        	word = query.substr(prev, pos-prev);
	        	Porter2Stemmer::stem(word);
	        	cout << word << " ";
	        	if(word[0] == '*' || word[word.length()-1] == '*'){
	        		bg->wildCardQuery(this, word);
	        	}
	        	else{ 
	        		bg->checkWord(word);
	        		insertProcessedQueries(word);
	        	}
	        }
	        prev = pos+1;
	    }
	    if (prev < query.length()){
	    	word = query.substr(prev, std::string::npos);
	    	Porter2Stemmer::stem(word);
	    	cout << word << " ";
	        if(word[0] == '*' || word[word.length()-1] == '*'){
	        	bg->wildCardQuery(this, word);
        	}
        	else{
        		bg->checkWord(word);
        		insertProcessedQueries(word);
        	}
	    }
	    cout << "\ncorrected query: ";
	    map< string, QueryWeights* >::iterator itr;
	    for(itr = processedQueries.begin(); itr != processedQueries.end(); itr++){
	    	cout << itr->first << " ";
	    }
	    cout << endl;
	    queryMagnitude();
		cosineSimilarity();
		printCosineSimilarity();
	}
	else if(typeQuery[0] == 'P' || typeQuery[0] == 'p'){
		cout << "\nInput your phrase query: ";
		string query;
		cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, query);
		cout << "\nprocessed query: ";
		this->unprocessedQuery = query;

		std::size_t prev = 0, pos;
		string word;
	    while((pos = query.find_first_of(" '&:#!+;?/,.-_<=>^()[]\t\r\n\v\f", prev)) != std::string::npos){
	        if (pos > prev){
	        	word = query.substr(prev, pos-prev);
	        	Porter2Stemmer::stem(word);
	        	cout << word << " ";
	        	bg->checkWord(word);
	        	insertProcessedQueries(word);
	        }
	        prev = pos+1;
	    }
	    if (prev < query.length()){
	    	word = query.substr(prev, std::string::npos);
	    	Porter2Stemmer::stem(word);
	    	cout << word << " ";
	        if(word[0] == '*' || word[word.length()-1] == '*'){
	        	bg->wildCardQuery(this, word);
        	}
        	else{
        		bg->checkWord(word);
        		insertProcessedQueries(word);
        	}
	    }
	    cout << "\ncorrected query: ";
	    map< string, QueryWeights* >::iterator itr;
	    for(itr = processedQueries.begin(); itr != processedQueries.end(); itr++){
	    	cout << itr->first << " ";
	    }
	    cout << endl;
	    queryMagnitude();
		phraseQuery();
		printCosineSimilarity();
	}
	else{
		cout << "wrong query type" << endl;
	}
	
}

void Query::insertProcessedQueries(string queryToken){		
	TrieNode* node = this->trie->findWord(queryToken);
	if(node == NULL){
		return;
	}
	if(processedQueries.find(queryToken) == processedQueries.end()){
		QueryWeights* newTokenWeight = new QueryWeights();
		newTokenWeight->incrementTermFreq();
		newTokenWeight->computeLogTermFreq();
		newTokenWeight->setDocFreq(node->getDocFreq());
		newTokenWeight->setInvDocFreq(node->getInvDocFreq());
		newTokenWeight->computeWeight();
		processedQueries[queryToken] = newTokenWeight;
	}
	else{
		QueryWeights* existingTokenWeight = processedQueries[queryToken];
		existingTokenWeight->incrementTermFreq();
		existingTokenWeight->computeLogTermFreq();
		existingTokenWeight->computeWeight();			
	}
}

void Query::queryMagnitude(){
	map< string, QueryWeights* > :: iterator it;
	for(it = this->processedQueries.begin(); it != this->processedQueries.end(); it++){
		this->magnitude += (((*it).second->getWeight())*((*it).second->getWeight()));
	}
	this -> magnitude += 1;
}

void Query::phraseQuery(){
	map< string, QueryWeights* > :: iterator it;
	map< string, QueryWeights* > :: iterator itSecond;
	map<int, PostingListNode*> :: iterator postingit;
	PostingList* nodeFirstPostingList;
	PostingList* nodeSecondPostingList;
	map<int, PostingListNode*> temp;
	map<int, PostingListNode*> tempSecond;
	double cosineScore;
	Trie *root = this->trie;
	TrieNode *nodeFirst;
	TrieNode *nodeSecond;
	bool flag = true;
	set<int> pos;
	set<int> posSecond;
	set<int>::iterator posIt;
	it = this->processedQueries.begin();
	itSecond = this->processedQueries.begin();
	itSecond++;

	for(; itSecond != this->processedQueries.end();it++, itSecond++)
	{	
		nodeFirst = root->findWord((it)->first);
		nodeSecond = root->findWord((itSecond)->first);
		if(nodeFirst == NULL || nodeSecond == NULL)
			continue;
		else
		{
			nodeFirstPostingList = nodeFirst->getPostingList();
			nodeSecondPostingList = nodeSecond->getPostingList();
			temp = nodeFirstPostingList->getActualPostingList();
			tempSecond = nodeSecondPostingList->getActualPostingList();
			for(postingit = temp.begin(); postingit != temp.end(); postingit++)
			{
				cosineScore = ((it)->second->getWeight()) * ((postingit)->second->getTermFreqInvDocFreq());
				cosineScore /= sqrt(this->magnitude);
				cosineScore /= sqrt(documentMagnitude[postingit->first]);
				if(tempSecond.find(postingit->first) != tempSecond.end()){
					pos = (postingit)->second->getPositionSet();
					posSecond = tempSecond.find(postingit->first)->second->getPositionSet();
					for(posIt = pos.begin(); posIt != pos.end(); posIt++){
						if(posSecond.find((*posIt)+1) != posSecond.end()){
							if(answer.find(postingit->first) == answer.end()){
								answer[postingit->first] = cosineScore;
							}
							else{
								answer[postingit->first] += cosineScore;
							}
							break;
						}
					}
					
				}
				
			}
		}
	}
}


void Query::cosineSimilarity(){
	map< string, QueryWeights* > :: iterator it;
	map<int, PostingListNode*> :: iterator postingit;
	PostingList* nodePostingList;
	map<int, PostingListNode*> temp;
	double cosineScore;
	Trie *root = this->trie;
	TrieNode *node;

	for(it = this->processedQueries.begin(); it != this->processedQueries.end();it++)
	{	
		node = root->findWord((it)->first);
		if(node == NULL)
			continue;
		else
		{
			nodePostingList = node->getPostingList();
			temp = nodePostingList->getActualPostingList();
			for(postingit = temp.begin(); postingit != temp.end(); postingit++)
			{
				cosineScore = ((it)->second->getWeight()) * ((postingit)->second->getTermFreqInvDocFreq());
				cosineScore /= sqrt(this->magnitude);
				cosineScore /= sqrt(documentMagnitude[postingit->first]);
				if(answer.find(postingit->first) == answer.end()){
					answer[postingit->first] = cosineScore;
				}
				else{
					answer[postingit->first] += cosineScore;
				}
			}
		}
	}
}

void Query::printCosineSimilarity(){
	int answerSize = answer.size();
	cout << "\nresult size: " << answerSize << endl;
	pair<double, int> ans[answerSize];
	map<int, double>:: iterator itr;
	int i;
	for(itr = answer.begin(), i = 0; itr != answer.end(); itr++, i++){
		ans[i] = make_pair(itr->second, itr->first);
	}		
	sort(ans, ans+answerSize);
	int numResults = 10;
	int numResultsCnt = 0;
	for(i = answerSize-1; i >= 0; i--){
		cout << "DocId: "<<ans[i].second << " -> " << "Weight: " << ans[i].first << endl;
		numResultsCnt++;
		if(numResultsCnt == numResults){
			numResultsCnt = 0;
			cout << "\nDo you want to see more results? y/n: ";
			char in;
			cin >> in;
			if(in == 'y' || in == 'Y'){
				continue;
			}
			else{
				break;
			}
		}
	}
}

int totalDocs;
int wordCount;
double* documentMagnitude;
Trie* dict = new Trie();
bigram* bg = new bigram();

int main(int argc, char** argv){
	cout << "Indexing started please wait..." << endl;
	char filename[] = "posts.csv";
	if(argc == 2){
		strcpy(filename, argv[1]);
	} 
	else if(argc > 2){
		cerr << "The correct format is ./search <argv>" << endl;
		return 1;
	}
	index(filename);
	cout << "Indexing finished" << endl;
	cout << "Total documents in corpus: " << totalDocs << endl;
	cout << "Total words in corpus: " << dict->getWordCount() << endl;
	dict->computeWeights();
	Query* q = new Query(dict);
	q->inputQuery();
	while(1){
		cout << "\nDo you have any more queries? y/n: ";
		string in;
		cin >> in;
		cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
		if(in[0] == 'y' || in[0] == 'Y'){
			Query* q = new Query(dict);
			q->inputQuery();
			delete q;
		}
		else{
			break;
		}
	}
	cout << endl;	
	return 0;
}
