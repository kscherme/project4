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
		int isEmpty();
		void push( Node );
		void printQueue();
		list<Node> data;
	private:
		pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

};

#endif