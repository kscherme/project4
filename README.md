Project 4
=========

**Pair**: Kathleen Schermerhorn & Courtney Kelly

How to build, run, and configure our code
-----------------------------------------
We created a simple Makefile which will compile our code with all the appropriate flags for you. You just simply need to run `make` and the executable: `site-tester` will be produced. Make sure you create your desired `sites.txt` and `search.txt` files. 

* The search file contains the list of strings that will be searched within the downloaded content
* The site file contains the list of sites that should be fetched each period

To run the program, simply type: `./site-tester`.

The Config Class
----------------
We created a configuration class to handle the parsing of the configuration file. The Constructor takes in a string with the filename of `config.txt`. The class then opens the file and sets the appropriate parameters for the `PERIOD_FETCH`, `NUM_FETCH`, `NUM_PARSE`, `SEARCH_FILE`, and `SITE_FILE` parameters. If no such file exists or only some of the paramters are defined in the file, then the missing parameters are set to their appropraite default values. 

The Parse Class
---------------
The parsing class is responsible for parsing the `SEARCH_FILE` and `SITE_FILE` parameters. The Constructor is passed a string with the filename and the class then opens the file (or throws an error if it doesn't exist) and reads the file line by line, putting eah line into a private `vector<string>` variable called `data`. The `data` variable will then contain either a vector of keywords or a vector a sites to search.

The CurlSite Class
------------------
The curl class models the `getinmemory` code given in the Project 4 documentation. It uses libcurl to fetch a webpage and then store the contents in memory. We modfied the getinmemory code so it returns a `string` with the webpage contents. We will later search this string for the keywords. We also modified the getinmemory code to include `CURLOPT_TIMEOUT` and `CURLOPT_NOSIGNAL` options. These two options are very important for handling the case when sites have errors. We set this option to 15 seconds. So if a request takes longer than 15 seconds, libcurl will timeout (won't get the webpage content for that site). But the program won't stop running, it will proceed curling the rest of the sites, and attempt to curl the site that timed out the next time the alarm goes off. 

The Queue Class
---------------

main.cc
-------