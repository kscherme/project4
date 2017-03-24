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
The queue class is one of the most parts of our program. It is a wrapper class that ensures the underlying `list<Node>` variable is threadsafe. It contains the normal `fill`, `pop`, `empty`, and `push` functions, but it also contains a `pthread_mutex_t` called `queue_mutex` and a `pthread_cond_t` called `queue_cond`. Anytime a thread wants to fill, pop, or push to the list variable, the mutex locks the operation, executes it, then unlockes the mutex. This ensures that no two threads can pop or push to the list at the same. In the `pop` function, if a thread tries to pop and the list is empty, it throws a `pthread_cond_wait( &queue_cond, &queue_mutex )`. This means the thread will wait for a signal to `queue_cond` to start back up, and temporarily release the mutex while it waits. This signal comes in the form of a `pthread_cond_broadcast( &queue_cond )`. We perform a broadcast anytime after a new item is pushed to the `list`, this happens in the `fill` and `push` functions. So anytime one of these functions is called, the new Node will be pushed to the list, the function will broadcast and wake up any sleeping threads, which are waiting for Nodes to be pushed to the list.

main.cc
-------