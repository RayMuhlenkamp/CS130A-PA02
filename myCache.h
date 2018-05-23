// myCache.h
// Documentation for part 2 of PA01
// by Ray Muhlenkamp
// for CS130A, S18
// 
// Hash Table/Max Heap stores arrays of ints in the order of [key, value, priority]
// 

#ifndef RBMUHL_MYCACHE_H
#define RBMUHL_MYCACHE_H

#include <unordered_map>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

namespace rbmuhl 
{
	struct ComparePriority {		
		bool operator()(vector<int> const v1, vector<int> const v2) {
			if (v1[2] != v2[2]) { return v1[2] < v2[2]; }
			else { return v1[0] < v2[0]; }
		}
	};

	typedef unordered_map<int,vector<int>> HashTable;
	typedef priority_queue<vector<int>, vector<vector<int>>, ComparePriority> MaxHeap;


	class myCache 
	{
	
	public:

		// CONSTRUCTOR, DESTRUCTOR (WIPE)
		myCache(string inputFile, string outputFile);
		void wipe();

		// MODIFICATION MEMBER FUNCTIONS

		void load_MH();
		void load_HT(int k);
		void access(int key);
		void performTestCase();
		void executeQuery(int operation, int key);

		// CONSTANT MEMBER FUNCTINS
		void display() const;
		string printMH(MaxHeap input) const;
		string printHT(HashTable input) const;

	private:

		HashTable* HT;
		mutable MaxHeap* MH;
		string inputFileName;	
		string outputFileName; 
		mutable string output;
                vector<vector<int>> elements;
		int nTests;
		int sizeHT;
		int nInputs;
		int nQueries;
		mutable streampos currentIn;
		mutable streampos currentOut;

	};

	



}


#endif
