EXE = search
OBJS = porter2_stemmer.o postingListNode.o postingList.o trieNode.o trie.o bigramNode.o bigram.o queryWeight.o query.o
CC = g++ -std=c++11
CCOPTS = -O3
LINKER = g++ -std=c++11

all: $(EXE)

$(EXE): $(OBJS)
	$(LINKER) -o $@ $(OBJS)

porter2_stemmer.o: porter2_stemmer.h porter2_stemmer.cpp
	$(CC) $(CCOPTS) -c porter2_stemmer.cpp -o $@

postingListNode.o: postingListNode.h postingListNode.cpp
	$(CC) -c postingListNode.cpp -o $@

postingList.o: postingList.h postingList.cpp
	$(CC) -c postingList.cpp -o $@

trieNode.o: trieNode.h trieNode.cpp
	$(CC) -c trieNode.cpp -o $@

trie.o: bigram.h porter2_stemmer.h trie.h trie.cpp
	$(CC) -c trie.cpp -o $@

bigramNode.o: bigramNode.h bigramNode.cpp
	$(CC) -c bigramNode.cpp -o $@

bigram.o: query.h bigram.h bigram.cpp
	$(CC) -c bigram.cpp -o $@

queryWeight.o: queryWeight.h queryWeight.cpp
	$(CC) -c queryWeight.cpp -o $@

query.o: bigram.h query.h porter2_stemmer.h query.cpp
	$(CC) -c query.cpp -o $@

clean:
	rm -f *.o $(EXE)
