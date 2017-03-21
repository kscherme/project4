/*	CurlSite.h

	This class will curl the content of the website passed to the constructor. 
*/

#ifndef CURLSITE_H_
#define CURLSITE_H_

#include <iostream>
#include <string>

using namespace std;

class CurlSite {

	public:
		CurlSite();
		char* getSite( const char* site );
		static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

};


#endif