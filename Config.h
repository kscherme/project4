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
		//void setParams( string configFile );
		
		int PERIOD_FETCH;
		int NUM_FETCH;
		int NUM_PARSE;
		string SEARCH_FILE;
		string SITE_FILE;
		
	private:

};

#endif