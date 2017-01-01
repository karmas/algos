#ifndef ST_H
#define ST_H

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

#endif
