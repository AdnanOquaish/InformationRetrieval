#include <map>
#include <string>
#include "postingListNode.h"

using namespace std;

class PostingList{

private:
    map<int, PostingListNode*> postingList; // stores the posting list in a map for log(n) lookup and insertion
    string word; // represents the word

public:
    PostingList(int docId, string word); // constructor for postingList takes docId and word as input, if docId is new make a new postingListNode

    void setWord(string word); // setter for word
    
    string getWord(); // getter for word

    void insertPostingListNode(int docId); // insert postingListNode by checking if node already exists or not, if already exitt increment term frequency

    const map<int, PostingListNode*> & getActualPostingList(); // returns reference to postingList map

    int sizePostingList(); // returns size of this postingList

    void computeTermFreqInvDocFreqForAll(double invDocFreq); // compute weights for all postinListNodes
};
