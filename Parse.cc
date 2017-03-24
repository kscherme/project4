/*	Parse.cc

	This file implements the functions defined in Parse.h

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parse.h"

using namespace std;

Parse::Parse( string parseFile, int NUM_PARSE ) {

	ifstream inFile(parseFile);
	if(!inFile) {
		cout << parseFile << " could not be opened." << endl;
		exit(1);
	}

	string line;
	while (inFile >> line) {
		data.push_back(line);
	}

}

vector<string> Parse::getData() {

	return data;

}
