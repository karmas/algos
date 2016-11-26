#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

/**
 * Empty : _head == _tail
 * Full : (_tail + 1) % _alloc == _head
 */
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
		_arr[_tail++] = item;
		_tail = _tail % _alloc;
	}

	T dequeue() {
		if (isEmpty()) {
			cerr << "error: queue empty" << endl;
			return T();
		}
		const T &ret = _arr[_head++];
		_head = _head % _alloc;
		return ret;
	}

	bool isEmpty() const { return _head == _tail; }
	int size() const
	{
		if (_tail >= _head) return _tail - _head;
		else return _tail + _alloc - _head;
	}
	bool isFull() const { return (_tail + 1) % _alloc == _head; }

	T *_arr = 0;
	int _alloc = 0;
	int _head = 0; // first item
	int _tail = 0; // where new item is put
};

/**
 * Empty : _head == _tail
 * Full : (_tail + 1) % _alloc == _head
 */
template <typename T>
struct Queue {
	/**
	 * Move the elements around to break fullness.
	 */
	void resize(int new_size) {
		//printf("resize: %d -> %d\n", _alloc, new_size);
		if (new_size < 1 ) {
			cerr << "error: can't resize to " << new_size << endl;
			return;
		}
		T *old_arr = _arr;
		int old_alloc = _alloc;
		const int tocopy = size();
		_arr = new T[new_size]();
		_alloc = new_size;

		int i = _head;
		int j = 0;
		for (int copied = 0; copied < tocopy; ++copied) {
			_arr[j++] = old_arr[i++];
			i = i % old_alloc;
		}

		_head = 0;
		_tail = j;
	}

	void enqueue(const T &item) {
		if (isFull()) {
			resize(_alloc * 2);
		}
		_arr[_tail++] = item;
		_tail = _tail % _alloc;
	}

	T dequeue() {
		if (isEmpty()) {
			cerr << "error: queue empty" << endl;
			return T();
		}
		if (size() < _alloc / 4) {
			resize(_alloc / 2);
		}
		const T &ret = _arr[_head++];
		_head = _head % _alloc;
		return ret;
	}

	bool isEmpty() const { return _head == _tail; }
	int size() const
	{
		if (_tail >= _head) return _tail - _head;
		else return _tail + _alloc - _head;
	}
	bool isFull() const { return (_tail + 1) % _alloc == _head; }

#define ALLOC 1
	T *_arr = new T[ALLOC];
	int _alloc = ALLOC;
#undef ALLOC
	int _head = 0; // first item
	int _tail = 0; // where new item is put
};

template <typename T>
struct QueueList {
	struct Node {
		Node(const T &item, Node *next)
			: _item(item), _next(next)
		{ }
		T _item;
		Node *_next;
	};

	void enqueue(const T &item) {
		Node *node = new Node(item, 0);
		if (isEmpty()) {
			_head = node;
		}
		else {
			_tail->_next = node;
		}
		_tail = node;
		++_size;
	}

	T dequeue() {
		if (isEmpty()) {
			cerr << "error: queue empty" << endl;
			return T();
		}
		Node *old_head = _head;
		T val = old_head->_item;
		_head = _head->_next;
		if (!_head) _tail = 0;
		delete old_head;
		--_size;
		return val;
	}

	bool isEmpty() { return !_head; }
	int size() { return _size; }

	Node *_head = 0; // will get removed
	Node *_tail = 0; // previous of new item
	int _size = 0;
};

#endif
