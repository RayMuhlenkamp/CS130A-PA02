// Implementation of testing for part2 for PA01
// by Ray Muhlenkamp
// for CS130A, S18

#include <iostream>
#include "myCache.h"

using namespace std;
using namespace rbmuhl;

int main(int argc, char *argv[]) {

	string testInput;
	string testOutput;
	string input;
	string output;
	bool goodInput=false;
	bool goodOutput=false;

        while (!goodInput) {
                cout << "Hello! Please enter the input (.txt) file name: ";
                cin >> testInput;

                if (testInput.find(".txt") == string::npos) {
                        cout << "It seems you didn't specify a \".txt\" file.\n\n";
                }

                else {
                        goodInput = true;
                        input = testInput;
                }

        }  
   
	while (!goodOutput) {
                cout << "Please enter the output (.txt) file name: ";
                cin >> testOutput;

                if (testOutput.find(".txt") == string::npos) {
                        cout << "It seems you didn't specify a \".txt\" file.\n\n";
                }

                else {
                        goodOutput = true;
                        output = testOutput;
                }

        }


	myCache test(input, output);
	
	return 0;

}
