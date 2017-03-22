/*	Parse.h

	This class will parse the search.txt and sites.txt files.
*/

#ifndef PARSE_H_
#define PARSE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Parse {

	public:
		Parse( string parseFile, int NUM_PARSE );
		vector<string> getData();

	private:
		vector<string> data;
};

#endif