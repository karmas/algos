#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>

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

  int sizeCalc(Node *node) const {
    if (!node) {
      return 0;
    }

    int total = 0;
    if (node->_val != 0) total += 1;

    for (int i = 0; i < 26; i++) {
      total += sizeCalc(node->_links[i]);
    }

    return total;
  }
  int sizeCalc() const {
    return sizeCalc(_root);
  }

  void keys(std::vector<std::string> &list) const {
    keysWithPrefix("", list);
  }
  void keysWithPrefix(std::string prefix,
      std::vector<std::string> &list) const {
    Node *node = find(_root, prefix, 0);
    collect(node, prefix, list);
  }
  void collect(Node *node, std::string pre,
      std::vector<std::string> &list) const {
    if (!node) return;
    if (node->_val != 0) {
      list.push_back(pre);
    }
    for (int i = 0; i < 26; i++) {
      char keylink = 'a' + i;
      std::string newPre = pre + keylink;
      collect(node->_links[i], newPre, list);
    }
  }

  void keysThatMatch(std::string pattern,
      std::vector<std::string> &list) const {
    collect(_root, "", pattern, list);
  }
  void collect(Node *node, std::string pre, std::string pattern,
      std::vector<std::string> &list) const {
    if (!node) return;
    if (pre.size() == pattern.size()) {
      if (node->_val != 0) {
        list.push_back(pre);
      }
      return;
    }

    char next = pattern[pre.size()];
    for (int i = 0; i < 26; i++) {
      char keylink = 'a' + i;
      std::string newPre = pre + keylink;
      if (next == '.' || next == keylink)
        collect(node->_links[i], newPre, pattern, list);
    }
  }

  std::string longestPrefixOf(const std::string &s) const {
    std::string key;
    int len = search(_root, s, 0, 0);
    return key.substr(0, len);
  }
  int search(Node *node, const std::string &s, int sc, int len) const {
    if (!node) return len;
    if (node->_val != 0) {
      len = sc;
    }
    if (sc == s.size()) return len;

    char keylink = s[sc] - 'a';
    return search(node->_links[keylink], s, sc + 1, len);
  }

  void remove(const std::string &key) {
    _root = remove(_root, key, 0);
  }
  Node *remove(Node *node, const std::string &key, int kc) {
    if (!node) return node;
    // found key
    if (kc == key.size()) {
      if (node->_val) --_size;
      node->_val = 0;
    }
    else {
      int keyIndex = key[kc] - 'a';
      node->_links[keyIndex] = remove(node->_links[keyIndex], key, kc + 1);
    }

    if (node->_val != 0) return node;
    for (int i = 0; i < 26; i++)
      if (node->_links['a' + i]) return node;
    delete node;
    return 0;
  }

  int _size;
  Node *_root;
};

#endif
