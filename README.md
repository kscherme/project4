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

The Node Class
--------------
This is a simple class that has no implementation file. It contains two variables, string siteName and string siteData. We instantiate a list of Nodes in the following Queue class. This is useful to keep the siteName and siteData connected for parsing and printing. We know which wepage data came from which site, and when we search/count the webpage content for keywords we know which site contains how many keywords and can easily indicate those results in the output file.

The Queue Class
---------------
The queue class is one of the most parts of our program. It is a wrapper class that ensures the underlying `list<Node>` variable is threadsafe. It contains the normal `fill`, `pop`, `empty`, and `push` functions, but it also contains a `pthread_mutex_t` called `queue_mutex` and a `pthread_cond_t` called `queue_cond`. Anytime a thread wants to fill, pop, or push to the list variable, the mutex locks the operation, executes it, then unlocks the mutex. This ensures that no two threads can pop or push to the list at the same. In the `pop` function, if a thread tries to pop and the list is empty, it throws a `pthread_cond_wait( &queue_cond, &queue_mutex )`. This means the thread will wait for a signal to `queue_cond` to start back up, and temporarily release the mutex while it waits. This signal comes in the form of a `pthread_cond_broadcast( &queue_cond )`. We perform a broadcast anytime after a new item is pushed to the list variable, this happens in the `fill` and `push` functions. So anytime one of these functions is called, the new Node will be pushed to the list, the function will broadcast and wake up any sleeping threads, which are waiting for Nodes to be pushed to the list.

main.cc
-------
With all the above classes included, the main function actually runs pretty simply. It contains 13 Global Variables:

* `Queue fetchQueue`: This is an object of the Queue class, which will be continually filled and emptied of sites. The fetch threads will be constantly waiting for Nodes to be put into this queue. When a Node is pushed to the queue, the queue will broadcast, wake up the sleepings threads. One of the sleeping threads will be able to pop successfully. It will take that Node, curl the corresponding siteName, and fill the siteData variable with the webpage content.

* `Queue parseQueue`: Once a thread is able to fetch and fill a Node with siteData, this node will then be pushed to the parseQueue. The parse threads will be constantly waiting for Nodes to be put into this queue. When a Node is pushed to the queue, the queue will broadcast, wake up the sleepings threads. One of the sleeping threads will be able to pop successfully. It will take this node, and search/count the siteData for keywords. It will push the results to an `output` vector.

* `Config config("config.txt")`: This instantiates the configuration parameters. It needs to be global so it can be accessed by other functions in `main`.

* `int FILECOUNT = 0`: This variable keeps track of the number of files the program has written. Each time a new outfile is witten, `FILECOUNT` is incremented, so all the output files can have different names. 

* `vector<string> keywords`: This contains a vector of all the keywords parsed from `search.txt`. This needs to be global so it can be accessed by other functions in `main`.

* `vector<string> sites`: This contains a vector of all the sites parsed from `sites.txt`. This needs to be global so it can be accessed by other functions in `main`.

* `vector<string> output`: This is the output vector mentioned above. Each time a thread successfully parses website content, its results, the sitename, keyword, and keyword count are all pushed to this vector. This vector is later used after all the threads have completed, to write the results to an output file. 

* `int keepRunning = 1`: This is a variable that keeps `main`, and all of the threads constantly running. When ^C is called, this variable is set to 0, so all the threads will finished and the program and the threads can exit gracefully. 

* `pthread_t* fetchthreads = new pthread_t[config.NUM_FETCH]`: This initializes and keeps track of all the threads needed for fetching site data. 

* `pthread_t* parsethreads = new pthread_t[config.NUM_PARSE]`: This initializes and keeps track of all the threads needed for parsing the site data.

* `pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER`: This mutex locks the output vector, so no two threads can write/push things to it at the same time.

* `string LOCALTIME`: This variable gets the local time whenever the alarm goes off and stores it. This is used when writing the output file. 

* `ofstream outputFile`: This is the output file stream. This also needs to be global so it can be accessed by multiple functions. The alarm handler and the exit handler. 

Main then starts by parsing the search file, then parsing the sites file, then it fills fetch queue for the first run. It then sets the singals for SIGALRM and SIGINT. It then creates the threads and sets off the alarm for the first time, going to the `alarmHandler` function. Then main gets local time for the output file and enters the main loop, controlled by the `keepRunning` variable. When this variable changes to 0 when ^C is called, this loop exits, the threads are collected and main returns 0.


EOF
