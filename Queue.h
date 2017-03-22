/*	Queue.h

	This is a wrapper class for...
*/

#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <string>
#include <list>
#include <pthread.h>
#include "Node.h"

using namespace std;

class Queue {
	public:
		Queue();
		void fill( vector<string> );
		Node pop();
		void printQueue();
		list<Node> data;
	private:
		pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;

};

#endif