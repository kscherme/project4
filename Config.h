/*	Config.h

	This class wil parse the configuration file.
*/

#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <string>

using namespace std;

class Config {
	public:
		Config( string configFile );
		/*
		PERIOD_FETCH=180;
		NUM_FETCH=1;
		NUM_PARSE=1;
		SEARCH_FILE=Search.txt;
		SITE_FILE=Sites.txt;
		*/
	private:
};

#endif