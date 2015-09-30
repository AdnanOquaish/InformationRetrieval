#include <set>

extern double* documentMagnitude; // lookup array for weight of each documents
extern int totalDocs; // used keep count of total number of doucmnets
extern int wordCount;

using namespace std;

class PostingListNode{

private:
    int docId; //stores the docId of document
    int termFreq; // stores the term frequency of the particular word for that document
    double logTermFreq; // equivalent to 1+log(termFreq)
    double termFreqInvDocFreq; // represents the weight associated with that docId for a particular word, equivalent to termFreq*invDocFreq
    set<int> position;

public:
    PostingListNode(int docId); // constructor for the posting List node, takes docId as input

    int getDocId(); // getter for docID

    void incrementTermFreq(); // increment termFreq by 1
    
    int getTermFreq(); // getter for termFreq

    void computeLogTermFreq(); // compute logTermFreq = 1+log(termFreq)
    
    double getLogTermFreq(); // getter for logTermFreq
    
    double getTermFreqInvDocFreq(); // getter for tf-idf

    double getTermFreqInvDocFreqSqr(); // getter for square of tf-idf, used in computation of magnitude of vector

    void computeTermFreqInvDocFreq(double invDocFreq); // computes tf-idf = termFreq*invDocFreq

    void insertWordPos(); // inserts the position of word into set

    const set<int> & getPositionSet();

};
