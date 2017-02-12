#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <iostream>

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

#endif
