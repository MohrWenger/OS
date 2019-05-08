// ------------------------------ includes ------------------------------
#include "MapReduceClient.h"
#include "MapReduceFramework.h"
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <setjmp.h>
#include <unistd.h>
#include "string.h"
#include <unistd.h>
#include <queue>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
// -------------------------- using definitions -------------------------
using namespace std;
// -------------------------- definitions -------------------------------
typedef std::vector<InputPair> IN_ITEMS_LIST;
typedef std::pair<K1*, V1*> IN_ITEM;
typedef std::vector<OutputPair> OUT_ITEMS_LIST;
typedef std::pair<K3*, V3*> OUT_ITEM;

class FileToSearch : public K1 {
public:
	char* file;
	bool operator<(const K1 &other) const{
		return true;
	}
};

class WordToSearch : public V1 {
public:
	string word;
};

class Word : public K2 {
public:
	char* word;
	bool operator<(const K2 &other) const{
		Word* temp = (Word*) &other;
		Word* temp2 = (Word*) this;
		if(strcmp(temp -> word, temp2 -> word) <= 0){
			return false;
		}
		return true;
	}
};

class ApperanceOfWord : public V2 {
public:
	int num;
};


class Word2 : public K3 {
public:
	char* word2;
	bool operator<(const K3 &other) const{
		Word2* temp = (Word2*) &other;
		Word2* temp2 = (Word2*) this;
		if(strcmp(temp2 -> word2, temp -> word2) < 0){
			return true;
		}
		return false;
	}
};

class ApperanceOfWordList : public V3{
public:
	int num;
};

class Count : public MapReduceClient{
public:

	void map(const K1 *const key, const V1 *const val, void* context) const{

		DIR *dir;
		struct dirent *ent;
		const char* file = ((FileToSearch*) key) -> file;
		ifstream myfile;
		myfile.open(file);
		string wordToSearch = ((WordToSearch*) val) -> word;
        while (myfile.good())
        {
            string word;
            myfile >> word;

            if ( word == wordToSearch)
            {
	            ApperanceOfWord* apperanceOfWord = new ApperanceOfWord();
	        	apperanceOfWord -> num = 1;
	        	Word* k2 = new Word();
	        	k2 -> word = strdup(wordToSearch.c_str());
		        emit2(k2,apperanceOfWord, context);
        	}
        }
        myfile.close();	

	}

    void reduce(const IntermediateVec* pairs,
				void* context) const{

		string word = static_cast<const Word*>(pairs->at(0).first)->word;
		int count = 0;
		for (IntermediatePair pairr : *pairs)
		{
			V2* val = pairr.second;
			count += ((ApperanceOfWord*)val) -> num;
		}

		Word2* myWord2 = new Word2();
		myWord2 -> word2 = strdup(word.c_str());

		ApperanceOfWordList* apperanceOfWordList = new ApperanceOfWordList();
		apperanceOfWordList -> num = count;

		emit3(myWord2,apperanceOfWordList, context);
    }
};


IN_ITEMS_LIST getData(int argc,char *argv[])
{
	IN_ITEMS_LIST res;

	for (int i = 5; i < 10; ++i)
	{
		for (int j = 1; j < 5; ++j)
		{
			FileToSearch* file1 = new FileToSearch();
			file1 -> file = argv[i];
			WordToSearch* word1 = new WordToSearch();
			word1 -> word = argv[j];
			res.push_back(IN_ITEM(file1,word1));
		}
	}
	return res;
}

int main(int argc,char *argv[])
{
	Count count;
	IN_ITEMS_LIST res = getData(argc,argv);
	for(IN_ITEM item : res)
	{
		FileToSearch* a = (FileToSearch*) item.first;
		WordToSearch* b = (WordToSearch*) item.second;
	}

	struct timeval diff, startTV, endTV;
	OUT_ITEMS_LIST finalRes;

    JobHandle x = startMapReduceJob(count, res ,finalRes, 1);
    closeJobHandle(x);

	cout << "***************************************" << endl;
	cout << "uncle sam has a farm,but all his animals escaped and hid" << endl;
	cout << "kids,help uncle sam find his animals in the files" << endl;
	cout << "***************************************" << endl;
	cout << "Recieved: " << endl;

	for(OUT_ITEM& temp : finalRes)
	{

		Word2* temp1 = (Word2*) temp.first;
		ApperanceOfWordList* temp2 = (ApperanceOfWordList*) temp.second;
		cout << temp2 -> num << " "<< temp1 -> word2 << endl;
	}

	cout << "***************************************" << endl;
	cout << "Excpected: " << endl;
	cout << "(the order matter,mind you)" << endl;
	cout << "6 Cat " << endl;
	cout << "12 Dog " << endl;
	cout << "10 Fish " << endl;
	cout << "8 Sheep " << endl;

	return 0;
}