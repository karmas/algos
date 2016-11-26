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

#endif
