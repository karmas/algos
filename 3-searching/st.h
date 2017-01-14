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
    else _head = found->_next;

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
    for (int i = 0; i < _size; i++) {
      std::cout << _keys[i] << "->" << _vals[i] << ", ";
    }
    std::cout << " size = " << _size;
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
        arr[i+amount] = arr[i];
      }
    }
  }

  void del(const key_t &k) {
    int r = rank(k);
    if (r == _size) {
      return;
    }
    else if (_keys[r] != k) {
      return;
    }
    if (r < _size - 1) {
      shift(_keys, r + 1, _size - 1, -1);
      shift(_vals, r + 1, _size - 1, -1);
    }
    --_size;
  }

  int _len;
  key_t *_keys;
  val_t *_vals;
  int _size;
};

template <typename key_t, typename val_t>
class BST {
public:
  struct Node {
    Node(const key_t &k, const val_t &v, Node *l, Node *r)
      : _key(k), _val(v), _left(l), _right(r), _size(1)
    { }
    void print() const {
      std::cout << _key << "->" << _val << "(" << _size << ")";
    }

    key_t _key;
    val_t _val;
    Node *_left;
    Node *_right;
    int _size;
  };

  BST()
    : _root(0)
  { }

  Node *find(Node *node, const key_t &k) const {
    if (!node) return 0;
    if (k < node->_key) return find(node->_left, k);
    else if (k > node->_key) return find(node->_right, k);
    else { return node; }
  }

  int size(Node *node) {
    return node ? node->_size : 0;
  }

  Node *put(Node *node, const key_t &k, const val_t &v) {
    if (!node) {
      Node *newNode = new Node(k, v, 0, 0);
      return newNode;
    }

    if (k < node->_key) {
      node->_left = put(node->_left, k, v);
    }
    else if (k > node->_key) {
      node->_right = put(node->_right, k, v);
    }
    else {
      node->_val = v;
    }
    node->_size = size(node->_left) + size(node->_right) + 1;
    return node;
  }

  void put(const key_t &k, const val_t &v) {
    _root = put(_root, k, v);
  }

  val_t get(const key_t &k) const {
    Node *found = find(_root, k);
    if (found) {
      return found->_val;
    }
    else {
      return val_t();
    }
  }

  bool contains(const key_t &k) const {
    return find(_root, k) != 0;
  }

  int size() const { return _root ? _root->_size : 0; }

  Node *min(Node *node) {
    Node *min = node;
    while (min->_left) min = min->_left;
    return min;
  }

  Node *del(Node *node, const key_t &k) {
    if (!node) return 0;
    if (k < node->_key) {
      node->_left = del(node->_left, k);
    }
    else if (k > node->_key) {
      node->_right = del(node->_right, k);
    }
    else {
      Node *ret = 0;
      if (!node->_left) {
        ret = node->_right;
      }
      else if (!node->_right) {
        ret = node->_left;
      }
      else {
        Node *m = min(node->_right);
        Node *succ = new Node(m->_key, m->_val, 0, 0);
        node->_right = del(node->_right, m->_key);
        succ->_left = node->_left;
        succ->_right = node->_right;
        succ->_size = size(succ->_left) + size(succ->_right) + 1;
        ret = succ;
      }
      delete node;
      return ret;
    }
    node->_size = size(node->_left) + size(node->_right) + 1;
    return node;
  }

  void del(const key_t &k) {
    _root = del(_root, k);
  }

  void print(Node *node) const {
    if (!node)
      return;
    print(node->_left);
    node->print();
    std::cout << ", ";
    print(node->_right);
  }
  void print() const {
    print(_root);
  }

  Node *_root;
};

#endif
