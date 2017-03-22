/*	test_read.cc

	This file tests the Config class.
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h> 
#include <curl/curl.h>
#include <fstream>
#include "Config.h"
#include "Parse.h"
#include "CurlSite.h"
#include "Queue.h"

using namespace std;

int main() {

	// Configure parameters
	Config config("config.txt");

	// Parse search file
	Parse search(config.SEARCH_FILE, config.NUM_PARSE);
	vector<string> keywords = search.getData();

	// Parse sites file
	Parse psites(config.SITE_FILE, config.NUM_PARSE);
	vector<string> sites = psites.getData();

	// Make output file
	int fileCount = 1;
	ofstream outputFile;
	string filename = to_string(fileCount) + ".csv";
	outputFile.open (filename);


	// Get website contents
	const char* c = sites.front().c_str();
	CurlSite curl;
	const char* data = curl.getSite(c);
	string data1 = string(data);
	cout << data1 << endl;

	// Perform keyword search on data
	for (vector<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
		int count = 0;
		size_t nPos = data1.find(*it, 0);
		while(nPos != string::npos) {
			count++;
			nPos = data1.find(*it, nPos + 1);
		}
		cout << *it << ": " << count << endl;
		outputFile << *it << ": " << count << endl;

	}

	outputFile.close();

	return 0;

}
