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
	pthread_mutex_unlock( &queue_mutex );

}

Node Queue::pop() {

	pthread_mutex_lock( &queue_mutex );
	Node value = data.front();
	data.pop_front();
	pthread_mutex_unlock( &queue_mutex );
	return value;

}

void Queue::printQueue() {

	for (list<Node>::iterator it=data.begin(); it != data.end(); ++it) {
		cout << (*it).siteName << endl;
	}

}