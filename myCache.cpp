// myCache.cpp
// Implementation for myCache.h
// by Ray Muhlenkamp
// for CS130A, S18


#include <iostream>
#include "myCache.h"


using namespace std;
using namespace rbmuhl;

namespace rbmuhl 
{
	
	// CONSTRUCTOR, DESTRUCTOR (FULL AND PARTIAL)
	
	// Constructs and exacutes a myCache object for the given input file, and produces 
	// results in the given output file
	myCache::myCache(string inputFile, string outputFile) {
		string x;
		stringstream stream;
		int temp;
		ifstream inFile;
		ofstream outFile;
		inputFileName = inputFile;
		outputFileName = outputFile;

		inFile.open(inputFile);
		outFile.open(outputFile);

		if(inFile.is_open()) {
			getline(inFile, x);
			stream << x;
			stream >> nTests;
			currentIn = inFile.tellg();
			inFile.close();
			for (int i=0; i<nTests; i++) {
				performTestCase();
				if (i != nTests-1) { output += "\n"; }
				wipe();
			}
		}

		outFile << output;
	}

	void myCache::wipe() {
		if (MH) { MH = new MaxHeap(); }
		if (HT) { delete HT; }
		elements.clear();

	}


	// MODIFICATION MEMBER FUNCTIONS
	
	// Loads elements from input list into MH
	void myCache::load_MH() {
		for (int i=0; i<elements.size(); i++) {
			MH->push(elements[i]);
		}	
	}

	// Resets the contents of HT
	// First pushes all elements in HT onto MH, if any, clears HT,
	// and then loads HT from MH
	void myCache::load_HT(int k) {
		if (!HT->empty()) {	
			HashTable::iterator it = HT->begin();
			while(it != HT->end()) {
				MH->push(it->second);
				it++;
			}
			HT->clear();
		}

		for (int i=0; i<k; i++) {
			pair<int,vector<int>> temp = {MH->top()[0], MH->top()};
			HT->insert(temp);
			MH->pop();
		}
	}

	void myCache::access(int key) {
		int result = -1;
		int value;
		if (HT->count(key)) {
			result = 0;
			value = (*HT)[key][1];
			(*HT)[key][2]++;
		}

		else {
			MaxHeap* tempHeap = new MaxHeap();
			vector<int> temp;
			for (int i=0; i<MH->size(); i++) {
				temp = MH->top();
				MH->pop();
				if (temp[0] == key) {
					result = 1;
					value = temp[1];
					temp[2]++;
				}
				tempHeap->push(temp);
			}
			delete MH;
			MH = tempHeap;
		}

		output += to_string(result);
		if (result != -1) { output += " " + to_string(value); }
		output += "\n";

	}
	
	// Performs the actions in a given Test Case
	void myCache::performTestCase(){
		string x;
		stringstream stream;
		vector<int> input = {0,0,0};
		int operation;
		int key;
		ifstream inFile;
		inFile.open(inputFileName);
		inFile.seekg(currentIn);

		// Read parameters of Test Case
		getline(inFile, x);
		stream << x;
		stream >> sizeHT;
		stream.str("");
		stream.clear();
		getline(inFile, x);
		stream << x;
		stream >> nInputs;
		stream.str("");
		stream.clear();
		getline(inFile, x);
		stream << x; 
		stream >> nQueries;
		stream.str("");
		stream.clear();

		MH = new MaxHeap();
		HT = new HashTable(sizeHT);

		// Read inputs
		for (int i=0; i<nInputs; i++) {
			getline(inFile, x);
			stream << x; 
			stream >> input[0];
			stream >> input[1];
			stream.str("");
			stream.clear();
			elements.push_back(input);
		}
		
		// Load MH and HT
		executeQuery(0, -1);
		executeQuery(1, -1);

		currentIn = inFile.tellg();
		inFile.close();

		// Execute Queries
		for (int i=0; i<nQueries; i++) {
			inFile.open(inputFileName);
			inFile.seekg(currentIn);

			getline(inFile,x);
			stream << x;
			stream >> operation;
			if (stream.eof()) { key = -1; }
			else { stream >> key; }

			currentIn = inFile.tellg();
			inFile.close();

			executeQuery(operation, key);
			stream.str("");
			stream.clear();
		}	

	}
	

	// Executes a given query. 
	// If operation is not 2, then key will be -1 (but not used)
	void myCache::executeQuery(int operation, int key) {
		if(operation == 0) { load_MH(); }
		else if (operation == 1) { load_HT(sizeHT); }
		else if (operation == 2) { access(key); }
		else { display(); }
	}

	// CONSTANT MEMBER FUNCTIONS


	void myCache::display() const {
		output += printHT(*HT) + printMH(*MH);
	}

	string myCache::printMH(MaxHeap input) const {
		string result = "";
		vector<vector<int>> temp;
		
		while(!input.empty()) {
			temp.push_back(input.top());
			input.pop();
		}

		for (int i=0; i<temp.size()-1; i++) {
			result += to_string(temp[i][0]) + " ";
		}
		result += to_string(temp[temp.size()-1][0]) + "\n";

		return result;
		
	}

	string myCache::printHT(HashTable input) const {
		string result = "";

                if (!HT->empty()) {
                        HashTable::iterator it = HT->begin();
		        for (int i=0; i<HT->size()-1; i++) {
        	                result += to_string(it->second[0]) + " ";
                                it++;
                        }
			result += to_string(it->second[0]);
		}
		result += "\n";

		return result;
		
	}



}
