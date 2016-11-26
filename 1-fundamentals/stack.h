#ifndef STACK_H
#define STACK_H

#include <cstring>
#include <iostream>
using namespace std;

template <typename T>
struct Stack {
	void resize(int alloc) {
		T *arr = _arr;
		_arr = new T[alloc]();
		_alloc = alloc;
		memcpy(_arr, arr, _size * sizeof(T));
		delete[] arr;
	}
	void push(const T &item) {
		if (isFull()) {
			resize(_alloc * 2);
		}
		_arr[_size++] = item;
	}

	T pop() {
		if (isEmpty()) {
			cerr << "error: stack empty" << endl;
			return T();
		}
		if (_size < _alloc / 4) {
			resize(_alloc / 2);
		}
		return _arr[--_size];
	}

	bool isEmpty() const { return _size == 0; }
	int size() const { return _size; }
	bool isFull() const {  return _size == _alloc; }

	T *_arr = new T[1]();
	int _alloc = 1;
	int _size = 0;
};

template <typename T>
struct StackFixed {
	StackFixed(int alloc)
		: _arr(new T[alloc]()), _alloc(alloc), _size(0)
	{ }

	void push(const T &item) {
		if (isFull()) {
			cerr << "error: full" << endl;
			return;
		}
		_arr[_size++] = item;
	}

	T pop() {
		if (isEmpty()) {
			cerr << "error: empty" << endl;
			return T();
		}
		return _arr[--_size];
	}

	bool isEmpty() const { return _size == 0; }
	int size() const { return _size; }
	bool isFull() const { return _size == _alloc; }

	T *_arr = 0;
	int _alloc = 0;
	int _size = 0;
};

template <typename T>
struct StackList {
	struct Node {
		Node(const T &item, Node *next)
			: _item(item), _next(next)
		{ }
		T _item = T();
		Node *_next = 0;
	};
	void push(const T &item) {
		Node *node = new Node(item, _top);
		_top = node;
		//++_size;
	}

	T pop() {
		if (isEmpty()) {
			cerr << "error: empty" << endl;
			return T();
		}
		const T ret = _top->_item;
		delete _top;
		_top = _top->_next;
		//--_size;
		return ret;
	}

	bool isEmpty() const { return _top == 0; }
	int size() const {
		//return _size;
		//return sizeIter();
		return sizeRecur(_top);
	}
	int sizeIter() const {
		int s = 0;
		for (Node *node = _top; node; node = node->_next) {
			++s;
		}
		return s;
	}
	int sizeRecur(Node *node) const {
		if (!node) {
			return 0;
		}
		return 1 + sizeRecur(node->_next);
	}

	//int _size = 0;
	Node *_top = 0; // points to top
};

#endif
