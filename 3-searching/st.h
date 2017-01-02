#ifndef ST_H
#define ST_H

#include <cassert>
#include <iostream>

//#define DEBUG

template <typename key_t, typename val_t>
class UnorderedListST {
public:
  struct Node {
    Node(const key_t &k, const val_t &v, Node *n)
      : _key(k), _val(v), _next(n)
    { }

    void print() {
      std::cout << _key << "->" << _val;
    }

    key_t _key;
    val_t _val;
    Node *_next;
  };

  typedef Node* iterator;
  iterator begin() { return _head; }
  iterator end() { return 0; }

  UnorderedListST()
    : _head(0)
  { }

  ~UnorderedListST()
  {
    Node *node = _head;
#ifdef DEBUG
    std::cout << "delete: ";
#endif
    while (node) {
      Node *prev = node;
      node = node->_next;
#ifdef DEBUG
      prev->print();
      std::cout << ", ";
#endif
      delete prev;
    }
#ifdef DEBUG
    std::cout << std::endl;
#endif
  }

  bool contains(const key_t &key) {
    Node *node = find(key);
    return node != 0;
  }

  Node *find(const key_t &key) {
    Node *node = _head;
    while (node && node->_key != key) {
      node = node->_next;
    }
    return node;
  }

  void put(const key_t &key, const val_t &val) {
    Node *found = find(key);
    if (found) {
      found->_val = val;
    }
    else {
      _head = new Node(key, val, _head);
    }
  }
  val_t get(const key_t &key) {
    Node *found = find(key);
    if (found) return found->_val;
    return val_t();
  }
  void print() {
    for (Node *node = _head; node; node = node->_next) {
      node->print();
      std::cout << ", ";
    }
  }

  size_t size(Node *node) const {
    if (!node) return 0;
    return 1 + size(node->_next);
  }
  size_t size() const { return size(_head); }

  void del(const key_t &key) {
    Node *pred = 0;
    Node *found = _head;
    while (found && found->_key != key) {
      pred = found;
      found = found->_next;
    }
    if (!found) return;

    if (pred) pred->_next = found->_next;
    else _head = 0;

    delete found;
  }

private:
  Node *_head;
};


template <typename key_t, typename val_t>
class OrderedArrayST {
public:
  OrderedArrayST()
    : _len(1),
    _keys(new key_t[_len]()),
    _vals(new val_t[_len]()),
    _size(0)
  {
  }
  ~OrderedArrayST() {
    delete[] _keys;
    delete[] _vals;
  }

  // how many less than k
  int rank(const key_t &k) const {
    int s = 0;
    int e = _size;
    while (e - s > 0) {
      int mid = (e - s)/2 + s;
      if (k < _keys[mid]) {
        e = mid;
      }
      else if (k > _keys[mid]) {
        s = mid + 1;
      }
      else
        return mid;
    }
    return s;
  }

  void put(const key_t &k, const val_t &v) {
    if (isFull()) {
      realloc(_len * 2);
    }
    int r = rank(k);
    // duplicate key
    if (r < _size) {
      if (_keys[r] == k) {
        _vals[r] = v;
        return;
      }
      // shift
      shift(_keys, r, _size - 1, 1);
      shift(_vals, r, _size - 1, 1);
    }
    _keys[r] = k;
    _vals[r] = v;
    ++_size;
  }

  val_t get(const key_t &k) const {
    int r = rank(k);
    if (r < _size && _keys[r] == k) {
      return _vals[r];
    }
    return val_t();
  }

  bool contains(const key_t &k) const {
    int r = rank(k);
    return r < _size && _keys[r] == k;
  }

  size_t size() const { return _size; }
  bool isFull() const { return _size == _len; }
  void print() const {
    std::cout << "keys: ";
    for (int i = 0; i < _size; i++) {
      std::cout << i << "->" << _keys[i] << ", ";
    }
    std::cout << " size = " << _size;
    std::cout << std::endl;
  }

  void realloc(int len) {
    assert(len >= _size);
    key_t *new_keys = new key_t[len]();
    val_t *new_vals = new val_t[len]();
    for (int i = 0; i < _size; ++i) {
      new_keys[i] = _keys[i];
      new_vals[i] = _vals[i];
    }
    delete[] _keys;
    delete[] _vals;
    _keys = new_keys;
    _vals = new_vals;
    _len = len;
  }

  template <typename T>
  void shift(T *arr, int start, int end, int amount) {
    assert(start >= 0);
    assert(start <= end);
    assert(end < _size);
    if (amount > 0) {
      assert(end + amount < _len);
      for (int i = end; i >= start; --i) {
        arr[i+amount] = arr[i];
      }
    }
    else {
      assert(start - amount >= 0);
      for (int i = start; i <= end; ++i) {
        arr[i-amount] = arr[i];
      }
    }
  }

  int _len;
  key_t *_keys;
  val_t *_vals;
  int _size;
};

#endif
