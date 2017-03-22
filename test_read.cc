/*	test_read.cc

	This file tests the Config class.
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h> 
#include <curl/curl.h>
#include <signal.h>
#include <fstream>
#include "Config.h"
#include "Parse.h"
#include "CurlSite.h"
#include "Queue.h"

using namespace std;

// Global Variables
Queue fetchQueue;
Config config("config.txt");
int FILECOUNT = 0;

// Functions
void data_fetch();


int main() {

	// Configure parameters
	//Config config("config.txt");

	// Parse search file
	Parse search(config.SEARCH_FILE, config.NUM_PARSE);
	vector<string> keywords = search.getData();

	// Parse sites file
	Parse psites(config.SITE_FILE, config.NUM_PARSE);
	vector<string> sites = psites.getData();

	// Fill fetch queue for the first run
	fetchQueue.fill(sites);

	// Set timer
	//signal(SIGALRM, wake_up_threads);
	//alarm(180)

	// Perform data fetch
	data_fetch();

	// Perform keyword search on data
	for (vector<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
		int count = 0;
		size_t nPos = data.find(*it, 0);
		while(nPos != string::npos) {
			count++;
			nPos = data.find(*it, nPos + 1);
		}
		cout << *it << ": " << count << endl;
		outputFile << *it << ": " << count << endl;

	}

	outputFile.close();

	fetchQueue.printQueue();

	return 0;

}

void data_fetch() {

	// Make output file
	FILECOUNT++;
	ofstream outputFile;
	string filename = to_string(fileCount) + ".csv";
	outputFile.open (filename);

	// Create threads
	pthread_t *threads = malloc( sizeof(pthread_t) * config.NUM_FETCH)
	int rc;

	for( int i = 0; i < config.NUM_FETCH; i++) {
		rc = pthread_create(&threads[i], NULL, curl_site, args);
	}

	// Get website contents
	const char* c = sites.front().c_str();
	CurlSite curl;
	string data = curl.getSite(c);
	cout << data << endl;	


}
