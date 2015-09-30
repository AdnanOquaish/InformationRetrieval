# Vector Space model based ranked textual information retrival system

Authors:
Abhimanyu Siwach
Adnan Oquaish
Deevankshu Garg

Requirements:
	g++ version 4.9.1

To compile:
First delete all the binaries:
	make clean
And then:
	make

To run:
	./search <name of the file>	
If no argument is provided the default search is on the file "posts.csv" already present in the folder. 

Assumption of the input document:
	Each row of the CSV file is considered to be a different document.


Precision and Recall:
	The whole program was run on more than 100 queries. Few of the instances are as follows:
	-> iphone broken
			Documents retrieved: 288
			Documents relevant in the dataset: 332
			Documents relevant in the retrieved dataset: 264 
			Precision: 79.5%
			Recall: 91.67%
	-> ipad hang
			Documents retrieved: 73
			Documents relevant in the dataset: 87
			Documents relevant in the retrieved dataset: 60 
			Precision: 83.9%
			Recall: 82.19%