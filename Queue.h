/*	Queue.h

	This is a wrapper class for...
*/

#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <string>
#include <list>
#include <pthread.h>

using namespace std;

class Queue {
	public:
		Queue();
		void fill( vector<string> );
		string pop();
		void printQueue();
		list<string> data;
		pthread_mutex_t queue_mutex;

};

#endif