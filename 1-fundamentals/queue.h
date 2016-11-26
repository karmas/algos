#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
struct QueueFixed {
	QueueFixed(int alloc)
		: _arr(new T[alloc]()), _alloc(alloc)
	{ }

	void enqueue(const T &item) {
		if (isFull()) {
			cerr << "error: queue full" << endl;
			return;
		}
	}

	T dequeue() {
		if (isEmpty()) {
			cerr << "error: queue empty" << endl;
			return T();
		}
		return T();
	}

	bool isEmpty() const { return true; }
	int size() const { return 0; }
	bool isFull() const { return false; }

	T *_arr = 0;
	int _alloc = 0;
};

#endif
