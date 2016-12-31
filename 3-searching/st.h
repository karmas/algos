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

  void put(const key_t &key, const val_t &val) {
    _head = new Node(key, val, _head);
  }
  val_t get(const key_t &key) {
    for (Node *node = _head; node; node = node->_next) {
      if (node->_key == key) {
        return node->_val;
      }
    }
    return val_t();
  }
  void print() {
    for (Node *node = _head; node; node = node->_next) {
      node->print();
      std::cout << ", ";
    }
  }

private:
  Node *_head;
};

#endif
