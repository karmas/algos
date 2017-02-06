#ifndef TRIE_H
#define TRIE_H

#include <iostream>

template <typename val_t>
struct Trie {
  struct Node {
    Node()
      : _val(), _links{}
    { }
    val_t _val;
    Node *_links[26];
  };

  Trie()
  : _size(0), _root(0)
  { }

  Node *find(Node *node, const std::string &key, int kc) const {
    if (!node) return 0;
    if (kc == key.size()) return node;
    int linkIndex = key[kc] - 'a';
    return find(node->_links[linkIndex], key, kc + 1);
  }

  Node *put(Node *node, const std::string &key, const val_t &val, int kc) {
    if (!node) {
      node = new Node();
    }
    if (kc == key.size()) {
      if (!node->_val)
        ++_size;
      node->_val = val;
    }
    else {
      int linkIndex = key[kc] - 'a';
      node->_links[linkIndex] = put(node->_links[linkIndex], key, val, kc + 1);
    }
    return node;
  }

  void put(const std::string &key, const val_t &val) {
    _root = put(_root, key, val, 0);
  }

  val_t get(const std::string &key) const {
    Node *found = find(_root, key, 0);
    if (!found) return 0;
    return found->_val;
  }

  bool contains(const std::string &key) const {
    return (find(_root, key, 0) != 0);
  }

  int size() const { return _size; }

  int _size;
  Node *_root;
};

#endif
