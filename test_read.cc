/*	test_read.cc

	This file tests the Config class.
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h> 
#include <curl/curl.h>
#include "Config.h"
#include "Parse.h"
#include "CurlSite.h"

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

	// Get website contents
	const char* c = sites.front().c_str();
	CurlSite curl;
	char* data = curl.getSite(c);
	cout << data << endl;

	return 0;

}
