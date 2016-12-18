#ifndef PQ_H
#define PQ_H

#include <iostream>
#include <sstream>

template<typename T>
void swap(T *arr, int i, int j)
{
	T temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

template<typename T>
class MinPQ_unordered_array {
public:
	MinPQ_unordered_array(int len)
		: _len(len), _arr(new T[len]()), _size(0)
	{ }
	~MinPQ_unordered_array() {
		delete[] _arr;
	}

	void insert(const T &item) {
		if (isFull()) {
			return;
		}
		_arr[_size++] = item;
	}

	int findMin() const {
		int m = _arr[0];
		for (int i = 1; i < _size; i++) {
			if (_arr[i] < _arr[m]) {
				m = i;
			}
		}
		return m;
	}

	T min() const {
		if (isEmpty()) {
			return T();
		}
		return _arr[findMin()];
	}

	T delMin() {
		if (isEmpty()) {
			return T();
		}
		int m = findMin();
		swap(_arr, m, --_size);
		return _arr[_size];
	}

	bool isFull() const { return _size == _len; }
	bool isEmpty() const { return _size == 0; }
	int size() const { return _size; }

	int _len;
	T *_arr;
	int _size; // next item goes here
};

template<typename T>
class MinPQ_ordered_array {
public:
	MinPQ_ordered_array(int len)
		: _len(len), _arr(new T[len]()), _size(0)
	{ }
	~MinPQ_ordered_array() {
		delete[] _arr;
	}

	void insert(const T &item) {
		if (isFull()) {
			return;
		}
		// (i, _size) < smaller
		int i = _size - 1;
		while (i >= 0 &&_arr[i] < item) {
			_arr[i+1] = _arr[i];
			--i;
		}
		_arr[i+1] = item;
		++_size;
	}

	T min() const {
		if (isEmpty()) {
			return T();
		}
		return _arr[_size - 1];
	}

	T delMin() {
		if (isEmpty()) {
			return T();
		}
		return _arr[--_size];
	}

	bool isFull() const { return _size == _len; }
	bool isEmpty() const { return _size == 0; }
	int size() const { return _size; }

	int _len;
	T *_arr;
	int _size; // next item goes here
};

template<typename T>
struct Node {
	Node(const T &val, Node *next)
		: _val(val), _next(next)
	{ }
	static void printList(const Node<T> *node) {
		std::cout << "list: ";
		for ( ; node; node = node->_next) {
			std::cout << node->_val << ",";
		}
		std::cout << std::endl;
	}
	T _val;
	Node *_next;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const Node<T> &node)
{
	out << node._val;
	return out;
}

template<typename T>
class MinPQ_unordered_list {
public:
	MinPQ_unordered_list()
		: _head(0), _size(0)
	{ }
	~MinPQ_unordered_list() {
	}

	void insert(const T &item) {
		_head = new Node<T>(item, _head);
		++_size;
		//Node<T>::printList(_head);
	}

	Node<T> *findMin(Node<T> *&minPred) const {
		minPred = 0;
		Node<T> *min = _head;
		for (Node<T> *node = min->_next, *pred = min;
				node;
				pred = node, node = node->_next) {
			if (node->_val < min->_val) {
				min = node;
				minPred = pred;
			}
		}
		assert (!minPred || minPred->_next == min);
		return min;
	}

	T min() const {
		if (isEmpty()) {
			return T();
		}
		Node<T> *pred = 0;
		return findMin(pred)->_val;
	}

	T delMin() {
		if (isEmpty()) {
			return T();
		}
		Node<T> *pred = 0;
		Node<T> *min = findMin(pred);
		T val = min->_val;
		if (pred) {
			pred->_next = min->_next;
		}
		else {
			_head = _head->_next;
		}
		delete min;
		--_size;
		//Node<T>::printList(_head);
		return val;
	}

	bool isEmpty() const { return _size == 0; }
	int size() const { return _size; }

	Node<T> *_head;
	int _size;
};

template<typename T>
class MinPQ_ordered_list {
public:
	MinPQ_ordered_list()
		: _head(0), _size(0)
	{ }
	~MinPQ_ordered_list() {
	}

	void insert(const T &item) {
		Node<T> *pred = 0;
		Node<T> *curr = _head;
		// [_head, curr) < item
		while (curr && curr->_val < item) {
			pred = curr;
			curr = curr->_next;
		}
		assert(!pred || pred->_next == curr);
		Node<T> *node = new Node<T>(item, curr);
		if (pred) pred->_next = node;
		else _head = node;
		++_size;
	}

	T min() const {
		if (isEmpty()) {
			return T();
		}
		return _head->_val;
	}

	T delMin() {
		if (isEmpty()) {
			return T();
		}
		Node<T> *min = _head;
		T val = min->_val;
		_head = _head->_next;
		delete min;
		--_size;
		return val;
	}

	bool isEmpty() const { return _size == 0; }
	int size() const { return _size; }

	Node<T> *_head;
	int _size;
};

template<typename T>
class MinPQ {
public:
	MinPQ(int max)
		: _len(max + 1), _arr(new T[_len]()), _size(0)
	{ }
	~MinPQ() {
		delete[] _arr;
	}

	void swim(int i) {
		// i is smaller than children
		while (i/2 > 0 && _arr[i/2] > _arr[i]) {
			swap(_arr, i, i/2);
			i /= 2;
		}
	}

	void sink(int i) {
		// i is bigger than parent
		int l = i*2;
		int r = l+1;
		while (l <= _size) {
			int c = l;
			if (r <= _size && _arr[r] < _arr[c]) {
				c = r;
			}
			if (_arr[i] <= _arr[c]) {
				break;
			}
			swap(_arr, i, c);
			i = c;
			l = i*2;
			r = l+1;
		}
	}

	void insert(const T &item) {
		if (isFull()) {
			return;
		}
		_arr[++_size] = item;
		swim(_size);
	}

	T min() const {
		if (isEmpty()) {
			return T();
		}
		return _arr[1];
	}

	T delMin() {
		if (isEmpty()) {
			return T();
		}
		swap(_arr, 1, _size--);
		sink(1);
		return _arr[_size + 1];
	}

	bool isFull() const { return _size + 1 == _len; }
	bool isEmpty() const { return _size == 0; }
	int size() const { return _size; }

	int _len;
	T *_arr;
	int _size;
};

template <typename T>
void printArray(const T *arr, int n)
{
    for (int i = 0; i < n; i++) {
        if (i > 0) std::cout << " ";
        std::cout << arr[i];
    }
    std::cout << std::endl;
}

/**
 * _pq holds indices
 * _qp is inverse of pq
 * _keys holds the values
 */
template<typename T>
class IndexMinPQ {
public:
    IndexMinPQ(int max)
        : _len(max + 1),
        _keys(new T[_len]()),
        _pq(new int[_len]()),
        _qp(new int[_len]()),
        _size(0)
    {
        for (int i = 0; i < _len; i++) {
            _qp[i] = -1;
        }
    }
    ~IndexMinPQ() {
        delete[] _keys;
        delete[] _pq;
        delete[] _qp;
    }

    void swap(int i, int j) {
        ::swap(_pq, i, j);
        ::swap(_qp, i, j);
    }

    bool less(int i, int j) {
        return _keys[_pq[i]] < _keys[_pq[j]];
    }

    void swim(int i) {
        // i is smaller than children
        while (i/2 > 0 && less(i, i/2)) {
            swap(i, i/2);
            i /= 2;
        }
    }

    void sink(int i) {
        // i is bigger than parent
        int l = i*2;
        int r = l+1;
        while (l <= _size) {
            int c = l;
            if (r <= _size && less(r, c)) {
                c = r;
            }
            if (less(i, c)) {
                break;
            }
            swap(i, c);
            i = c;
            l = i*2;
            r = l+1;
        }
    }

    // k_th item in _arr[_key[k]]
    void insert(int k, const T &item) {
        if (isFull()) {
            return;
        }
        ++_size;
        _qp[k] = _size;
        _pq[_size] = k;
        _keys[k] = item;
        swim(_size);
    }

    void change(int k, const T &item) {
    }

    bool contains(int k) const {
        return _qp[k] != -1;
    }

    void del(int k) {
    }

    T min() const {
        if (isEmpty()) {
            return T();
        }
        return _keys[_pq[1]];
    }

    int delMin() {
        if (isEmpty()) {
            return -1;
        }
        int min = _pq[1];
        swap(1, _size--);
        sink(1);
        _keys[_pq[_size + 1]] = T();
        _qp[_pq[_size + 1]] = -1;
        return min;
    }

    bool isFull() const { return _size + 1 == _len; }
    bool isEmpty() const { return _size == 0; }
    int size() const { return _size; }

    int _len;
    T *_keys;
    int *_pq;
    int *_qp;
    int _size;
};

#endif
