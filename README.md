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

The CurlSite Class
------------------

The Queue Class
---------------

main.cc
-------