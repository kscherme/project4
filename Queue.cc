/*	Queue.cc
*/

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <pthread.h>
#include "Queue.h"

using namespace std;

Queue::Queue() {}

void Queue::fill( vector<string> v ) {

	pthread_mutex_lock( &queue_mutex );
	for (vector<string>::iterator it=v.begin(); it != v.end(); ++it) {
		data.push_back(*it);
	}
	pthread_mutex_unlock( &queue_mutex );

}

string Queue::pop() {

	pthread_mutex_lock( &queue_mutex );
	string value = data.front();
	data.pop_front();
	pthread_mutex_unlock( &queue_mutex );
	return value;

}

void Queue::printQueue() {

	for (list<string>::iterator it=data.begin(); it != data.end(); ++it) {
		cout << *it << endl;
	}

}