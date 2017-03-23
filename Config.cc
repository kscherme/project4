/*	Config.cc

	This file implements the functions defined in Config.h
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include "Config.h"

using namespace std;

Config::Config(string configFile) {

//void Config::setParams( string configFile ) {

	PERIOD_FETCH=180;
	NUM_FETCH=1;
	NUM_PARSE=1;
	SEARCH_FILE="search.txt";
	SITE_FILE="sites.txt";

	ifstream infile(configFile);
	if(!infile) {
		cout << configFile << " could not be opened." << endl;
		exit(1);
	}

	list<string> tokens;
	string line;

	while(getline(infile, line)) {
		string param;
		string value;

		stringstream s(line);
		getline(s, param, '=');
		getline(s, value, '=');

		// cout << param << endl;
		// cout << value << endl;

		if ((param).compare("PERIOD_FETCH") == 0) {

			PERIOD_FETCH = stoi(value);

		}
		else if((param).compare("NUM_FETCH") == 0) {

			NUM_FETCH = stoi(value);

		}
		else if((param).compare("NUM_PARSE") == 0) {

			NUM_PARSE = stoi(value);

		}	
		else if((param).compare("SEARCH_FILE") == 0) {

			SEARCH_FILE = value;
			//cout << "SEARCH_FILE= " << value << endl;

		}	
		else if((param).compare("SITE_FILE") == 0) {

			SITE_FILE = value;
			//cout << "SITE_FILE= " << value << endl;
		}

	}



} 