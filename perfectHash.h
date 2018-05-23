// perfectHash.h
// by Ray Muhlenkamp, for CS130A, S18, PA01

#ifndef RBMUHL_PERFECTHASH_H
#define RBMUHL_PERFECTHASH_H

#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <random>

using namespace std;


namespace rbmuhl
{
 
	typedef vector<int> Vec;
	typedef vector<Vec> Mat;

	Vec operator*(const Mat &a, const Vec &x);
	string printVec(Vec input);
	
	class perfectHash
	{

	public:

		// CONSTRUCTOR, DESTRUCTOR
		perfectHash(string& inputFile);
		~perfectHash();

		// MODIFICATION MEMBER FUNCTIONS
		void getKeys(string& inputFile);
		void handleFirstLevel(); 
		void handleSecondLevel(minstd_rand& generator);
            
		// CONSTANT MEMBER FUNCTIONS
		Mat generateHash(int rows, int columns, minstd_rand& generator) const; 
		void output(string outputFile) const;
                int handleHash(Mat a, Vec x) const;
		int maxSize(Vec* inputTable, int size) const;
		int findBits(int x) const;
		int getSpace() const;
		int search(Vec key) const;
	private:
		
		Mat keys; // Matrix of the keys from the input file, each row is a vector representation of a new key

		Mat firstHash; // First Level Hash function, a matrix

		Vec* firstLevelTable; // Pointer to Array of vectors that represents the number of keys that hash to each bin in first level hashing, as well as the key's index number in the keys Matrix

		Mat* secondHash; // Pointer to Array of matrices, where each matrix is the given hash function for the bin

		Vec** secondLevelTable; // Pointer to an array of pointers to an array of Vectors that represent the various hash tables for the second level	

	};


}

#endif
