// perfectHash.cpp
// by Ray Muhlenkamp for CS130A, S18, PA01
//
// Matrix code built from the code found at http://www.physics.utah.edu/~detar/lessons/c++/matrices/node4.html
// findBits() code built from the code found at https://stackoverflow.com/questions/3272424/compute-fast-log-base-2-ceiling
//



#include <iostream>
#include "perfectHash.h"
#include "time.h"
#include <cmath>
#include <random>

using namespace std;
using rbmuhl::perfectHash;

namespace rbmuhl{

	Vec operator*(const Mat &a, const Vec &x){
          int i,j;
          int m = a.size();
          int n = x.size();

          Vec prod(m);

          for(i = 0; i < m; i++){
                    prod[i] = 0;
            for(j = 0; j < n; j++)
                      prod[i] += a[i][j]*x[j];
            prod[i] = prod[i] % 2;
	  }


          return prod;
	}
	
	string printVec(Vec input) {
		string result = "";
		for (int i=0; i < input.size(); i++){
		       	result += input[i] + " ";
		}
		return result;
	}

	// CONSTRUCTOR, DESTRUCTOR
	perfectHash::perfectHash(string& inputFile){
		cout << "Initializing...\n";

		unsigned seed = time(NULL);
		minstd_rand generator (seed);

		getKeys(inputFile);
		int numKeys = keys.size();
		int maxFirstSize = keys.size();		
		int maxTotal = 4 * numKeys;
		int r = findBits(numKeys);

		cout << "Creating Perfect Hash Table of " << numKeys << " keys...\n";
	     do {
		// Generate the First Level Hash Table
		while (maxFirstSize >= sqrt(numKeys)) {
			firstHash = generateHash(r, keys[0].size(), generator); 	
			handleFirstLevel();
			maxFirstSize = maxSize(firstLevelTable, numKeys);
		}

		// Handle the Second Level
		handleSecondLevel(generator);

	     }  while (getSpace() > maxTotal);

	     cout << "Done!\n"; 
	}
	
	perfectHash::~perfectHash() {
		int numKeys = keys.size();
		for (int i=0; i < numKeys; i++) {
			delete [] secondLevelTable[i];
		}	
		delete [] secondLevelTable;
		delete [] secondHash; 
		delete [] firstLevelTable; 

	}

	// MODIFICATION MEMBER FUNCTIONS
	
	// Loads the keys from the specified inputFile into this->keys
	void perfectHash::getKeys(string& inputFile) {
		ifstream inFile;
		string x;
		int temp;
		inFile.open(inputFile);

		if (inFile.is_open()) {
			while( getline(inFile,x) ) {
				Vec currentVec;
				for (int i=0; i<x.size()-1; i++) {	
					if (x[i] == '0') {temp=0;}
					else temp=1;
					currentVec.push_back(temp);	
				}
				this->keys.push_back(currentVec);
			}
		}
	
		inFile.close();
	}

	// Iterate through all the keys. Hash them out, and store the key in the given 
	void perfectHash::handleFirstLevel() {
		int current;
		firstLevelTable = new Vec[keys.size()]();

		for (int i=0; i<keys.size(); i++) {
			firstLevelTable[i].push_back(-1);
		}

		for (int i=0; i<keys.size(); i++) {
			current = handleHash(firstHash, keys[i]);
			
			if (firstLevelTable[current].front() == -1) {
				firstLevelTable[current].clear();
			}

			firstLevelTable[current].push_back(i);
		}

	}

	// Iterate through the firstLevelTable, rehashing when needed and filling out the secondLevelTable
	void perfectHash::handleSecondLevel(minstd_rand& generator) {
		Vec tempVec;
		tempVec.push_back(-1);
		secondHash = new Mat[keys.size()]();
		secondLevelTable = new Vec*[keys.size()]();
		int maxSecondSize;
		int current;
		int n;

		for (int i=0; i < keys.size(); i++) {
			maxSecondSize = firstLevelTable[i].size();
			if (firstLevelTable[i].size() == 1 ) {
				secondHash[i].push_back(tempVec);
				secondLevelTable[i] == NULL;
			}
			else {
				n = pow(firstLevelTable[i].size(),2);
				int r = findBits(n);
				while (maxSecondSize > 1) {
					secondHash[i] = generateHash(r, keys[0].size(), generator);
					secondLevelTable[i] = new Vec[n]();
					for (int j=0; j < n; j++) { 
						secondLevelTable[i][j].push_back(-1);
					}

					for (int k=0; k < firstLevelTable[i].size(); k++) {
						current = handleHash(secondHash[i], keys[firstLevelTable[i][k]]) % n;
						if (secondLevelTable[i][current].front() == -1) {
							secondLevelTable[i][current].clear();
						}
						secondLevelTable[i][current].push_back(firstLevelTable[i][k]);
					}

					maxSecondSize = maxSize(secondLevelTable[i], n);
					
				}

			}	
		}
	}

	// CONSTANT MEMBER FUNCTIONS

	// Generates a Hash Function matrix with random binary values of size m by n
	Mat perfectHash::generateHash(int rows, int columns, minstd_rand& generator) const {
  	        Vec row(columns);
		Mat result;

		for (int m=0; m<rows; m++){
			for (int n=0; n<columns; n++) {
				row[n] = generator() % 2;
			}
			result.push_back(row);
		}

		return result;
	}

	// Outputs the required output to the specified text file
	void perfectHash::output(string outputFile) const {
		ofstream outFile;
		outFile.open(outputFile);

                int numKeys = keys.size();
                int r = findBits(numKeys);

                for (int i=0; i < r; i++) {
                        for (int j=0; j < firstHash[i].size(); j++) {
                                outFile << firstHash[i][j];
                        }
                        outFile << endl;
                }

                outFile << endl;

                for (int a=0; a < numKeys; a++) {
			if (secondLevelTable[a] == NULL) {
				outFile << "NULL" << endl;
			}
                        else {
                                for (int i=0; i < secondHash[a].size(); i++) {
                                        for (int j=0; j < secondHash[a][i].size(); j++) {
                                                outFile << secondHash[a][i][j];
                                        }
                                        outFile << endl;
                                }
                               
                        }
			outFile << endl;

                }

		outFile << getSpace() << endl << endl;

		for (int i=0; i<numKeys; i++) {
			outFile << search(keys[i]) << endl;
		}
		



	}


        // Returns the Hash value using the given function and key
        int perfectHash::handleHash(Mat a, Vec x) const{
                Vec dest = a*x;

                int n = dest.size();
                int result = 0;

                for (int i=0; i<n; i++) {
                        result += (pow(2, n-1-i) * dest[i]);
                }
                return result;
        }

	
	// Returns the Maximum Number of Collisions in the Hash Table
	int perfectHash::maxSize(Vec* inputTable, int size) const {
		int result = 0;
		
		for (int i = 0; i < size; i++) {
			if (inputTable[i].size() > result) {
				result = inputTable[i].size();
			}
		}

		return result;
	}

	// Returns the number of bits neccessary to represent the number
	// Using the algorithm and code found at https://stackoverflow.com/questions/3272424/compute-fast-log-base-2-ceiling
	//
	
	int perfectHash::findBits(int x) const {
                  static const unsigned long long t[6] = {
		    0xFFFFFFFF00000000ull,
		    0x00000000FFFF0000ull,
		    0x000000000000FF00ull,
		    0x00000000000000F0ull,
		    0x000000000000000Cull,
		    0x0000000000000002ull
		  };

		  int y = (((x & (x - 1)) == 0) ? 0 : 1);
		  int j = 32;
		  int i;
	
		  for (i = 0; i < 6; i++) {
		    int k = (((x & t[i]) == 0) ? 0 : j);
		    y += k;
		    x >>= k;
		    j >>= 1;
	 	  }

		  return y;
	}

	// Returns the total amount of space used in the hash tables
	int perfectHash::getSpace() const {
		int numKeys = keys.size();
		int result = numKeys;

		for (int i=0; i<numKeys; i++) {
			if (secondLevelTable[i] !=  NULL) {
				result += pow(firstLevelTable[i].size(), 2);
			}
		}

		return result;
	}

	// Returns the amount of hashes needed to find the value in the Tables
	// If zero is return, the value is not in the hash table
	int perfectHash::search(Vec  key) const {
		int result = 1;
		int firstBin = handleHash(firstHash, key);
	       	if (firstLevelTable[firstBin].size() > 1) {
			result ++;
		}	
		
		return result;
	}

}
