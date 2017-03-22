/*	Queue.cc
*/

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <pthread.h>
#include "Queue.h"
#include "Node.h"

using namespace std;

Queue::Queue() {}

void Queue::fill( vector<string> v ) {

	pthread_mutex_lock( &queue_mutex );
	for (vector<string>::iterator it=v.begin(); it != v.end(); ++it) {
		Node siteNode;
		siteNode.siteName = *it;
		data.push_back(siteNode);
	}
	pthread_cond_broadcast( &queue_cond );
	pthread_mutex_unlock( &queue_mutex );

}

Node Queue::pop() {

	pthread_mutex_lock( &queue_mutex );

	// Check if empty
	while (data.empty()) {
		pthread_cond_wait( &queue_cond, &queue_mutex );
	}

	// do normal pop
	Node value = data.front();
	data.pop_front();

	pthread_mutex_lock( &queue_mutex );
	return value;

}

int Queue::empty() {

	int value;

	cout << "in empty..." << endl;
	pthread_mutex_lock( &queue_mutex );
	cout << "acquired lock..." << endl;

	if (data.empty()) {
		value = 1;
	}
	else {
		value = 0;
	}
	cout << "past empty" << endl;

	cout << "unlocking..." << endl;
	pthread_mutex_lock( &queue_mutex );
	cout << "unlocking..." << endl;
	
	return value;

}

void Queue::push( Node newNode ) {

	pthread_mutex_lock( &queue_mutex );
	data.push_back(newNode);
	pthread_cond_broadcast( &queue_cond );
	pthread_mutex_lock( &queue_mutex );

}

void Queue::printQueue() {

	for (list<Node>::iterator it=data.begin(); it != data.end(); ++it) {
		cout << (*it).siteName << endl;
	}

}