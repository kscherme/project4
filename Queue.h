/*	Queue.h

	This is a wrapper class for...
*/

#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Queue {
	public:
		Queue();
		~Queue();
		list<string> data;

};

#endif