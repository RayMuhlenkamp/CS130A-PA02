// Test code for perfectHash
// for cs130A, S18, PA01
// by Ray Muhlenkampi
// Run and follow prompts to test the code for given input (.txt) files

#include <iostream>
#include <fstream>
#include "perfectHash.h"
#include <string>
#include "string.h"

using namespace std;
using namespace rbmuhl;

int main(int argc, char *argv[]) {

	string testInput;
	string input;
	bool goodInput=false;

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
	
	cout << input;
	perfectHash* test = new perfectHash(input);

	string x;
	bool goodOutput = false;

	while (!goodOutput) {
		cout << "What would you like your output file to be? It will overwrite. ";
		cin >> x;

		if (x.substr(0,10) == "perfectHash") {
			cout << "Uh-oh! Don't do that. Abort!\n\n";
			return 1;
		}

		else if (x.find(".txt") == string::npos) {
			cout << "It seems you didn't specify a \".txt\" file.\n\n";
		}

		else {
			goodOutput = true;
			test->output(x);
		}
	}
 				
	delete test;
	cout << "Goodbye!\n";

	return 0;
}




