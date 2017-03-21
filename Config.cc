/*	Config.cc

	This file implements the functions defined in Config.h
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Config.h"

using namespace std;

Config::Config( string configFile ) {

	PERIOD_FETCH=180;
	NUM_FETCH=1;
	NUM_PARSE=1;
	SEARCH_FILE="Search.txt";
	SITE_FILE="Sites.txt";

	ifstream infile(configFile);
	if(!infile) {
		cout << configFile << " could not be opened." << endl;
		exit(1);
	}

	vector<string> tokens;
	string param;

	while(!infile.eof()) {
		getline(infile, param, '=');
		tokens.push_back(param);
		//cout << param << endl;
	}

	for( vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it ) {
		//cout << *it << endl;
		if (*it == "PERIOD_FETCH") {
			++it;
			PERIOD_FETCH = stoi(*it);
			//cout << PERIOD_FETCH << endl;
		}
		else if(*it == "NUM_FETCH") {
			++it;
			NUM_FETCH = stoi(*it);
		}
		else if(*it == "NUM_PARSE") {
			++it;
			NUM_PARSE = stoi(*it);
		}	
		else if(*it == "SEARCH_FILE") {
			++it;
			SEARCH_FILE = *it;
		}	
		else if(*it == "SITE_FILE") {
			++it;
			SITE_FILE = *it;
		}

	}



} 