#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <iostream>
#include <cmath>

size_t findSubStringBruteAll(const std::string &s, const std::string &f)
{
  for (size_t i = 0; i < s.size(); i++) {
    for (size_t j = 1; j <= s.size(); j++) {
      std::string ss = s.substr(i, j);
      if (ss == f) return i;
    }
  }
  return std::string::npos;
}

size_t findSubStringBrute(const std::string &s, const std::string &f)
{
  size_t i = 0;
  size_t j = 0;
  // [0, j) found inside [0, i)
  while (i < s.size() && j < f.size()) {
    if (s[i] != f[j]) {
      i -= j - 1;
      j = 0;
      while (i < s.size() && s[i] != f[0]) ++i;
    }
    else {
      ++i; ++j;
    }
  }
  if (j == f.size()) return i - j;
  else return std::string::npos;
}

// i is index in s from which to start matching f
size_t findSubStringBrute2(const std::string &s, const std::string &f)
{
  int n = s.size();
  int m = f.size();
  for (int i = 0; i < n; i++) {
    int j = 0;
    for ( ; j < m; j++) {
      if (f[j] != s[j + i]) break;
    }
    if (j == m) return i;
  }
  return std::string::npos;
}

// i contains how many characters matched with pattern
size_t findSubStringBrute2alt(const std::string &s, const std::string &f)
{
  int n = s.size();
  int m = f.size();
  int i = 0;
  while (i < n) {
    int j = 0;
    for ( ; j < m; j++, ++i) {
      if (f[j] != s[i]) break;
    }
    if (j == m) return i - j;
    i -= j;
    ++i;
  }
  return std::string::npos;
}

// knuth morris pratt substring search
struct KMP {
  static const int R = 128;
  KMP(const std::string &p)
    : _p(p), _m(p.size()), _dfa(new int*[R]())
  {
    for (int i = 0; i < R; i++) {
      _dfa[i] = new int[_m]();
    }

    // when in state 0 and see first character of pattern
    // proceed to state 1
    _dfa[(int)_p[0]][0] = 1;
    // x is restart state for mismatch
    for (int x = 0, j = 1; j < _m; ++j) {
      // all next states are set to restart state
      for (int c = 0; c < R; c++) {
        _dfa[c][j] = _dfa[c][x];
      }
      // for matched case
      _dfa[(int)_p[j]][j] = j + 1;
      x = _dfa[(int)_p[j]][x];
    }
  }

  ~KMP() {
    for (int i = 0; i < R; i++) {
      delete[] _dfa[i];
    }
    delete[] _dfa;
  }

  size_t search(const std::string &s) const {
    const int n = s.size();
    int i = 0; int j = 0;
    for ( ; i < n && j < _m; ++i) {
      j = _dfa[(int)s[i]][j];
    }
    if (j == _m) return i - j;
    else return std::string::npos;
  }

  std::string _p;
  int _m;
  int **_dfa;
};

// boyer moore
struct BM {
  static const int R = 128;
  BM(const std::string &p)
    : _p(p), _m(_p.size()), _right(new int[R]())
  {
    for (int i = 0; i < R; i++) {
      _right[i] = -1;
    }
    // rightmost position of a pattern character
    for (int i = 0; i < _m; i++) {
      _right[(int)_p[i]] = i;
    }
  }

  size_t search(const std::string &s) const {
    const int n = s.size();
    int skip = 0;
    for (int i = 0; i <= n - _m; i += skip) {
      int j = _m - 1;
      for ( ; j >= 0; --j) {
        if (_p[j] != s[i + j]) break;
      }
      if (j == -1) return i;
      skip = j - _right[(int)s[i + j]];
      if (skip < 1) skip = 1;
    }
    return std::string::npos;
  }

  std::string _p;
  int _m;
  int *_right;
};

struct RK {
  static const long R = 128;
  static const long Q = 11307023;
  RK(const std::string &p)
    : _p(p), _m(p.size()), _patHash(hash(_p, _m)),
    _rm(1)
  {
    for (int i = 1; i < _m; i++) {
      _rm = (R * _rm) % Q;
    }
  }

  long hash(const std::string &s, int m) const {
    long h = 0;
    for (int i = 0; i < m; i++) {
      h = (R * h + s[i]) % Q;
    }
    return h;
  }

  size_t search(const std::string &s) const {
    const int n = s.size();
    long txtHash = hash(s, _m);
    if (txtHash == _patHash) return 0;
    for (int i = _m; i < n; i++) {
      txtHash = (txtHash + Q - _rm * s[i - _m] % Q) % Q;
      txtHash = (txtHash * R + s[i]) % Q;
      if (txtHash == _patHash) return i - _m + 1;
    }
    return std::string::npos;
  }

  std::string _p;
  int _m;
  long _patHash;
  long _rm;
};

#endif
