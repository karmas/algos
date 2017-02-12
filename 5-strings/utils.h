#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

// return number in range [s, e)
int randomNum(int s, int e)
{
  double d = rand() / (double)RAND_MAX;
  int r = e - s;
  return (s + r * d);
}

char randomChar()
{
  int r = rand() % 26;
  return 'a' + r;
}

void randomString(std::string &s, int maxLen)
{
  s.clear();
  const int len = randomNum(1, maxLen);
  for (int i = 0; i < len; i++) {
    s.append(std::string(1, randomChar()));
  }
}

void genSubStrings(const std::string &s, std::vector<std::string> &list)
{
  for (size_t i = 0; i < s.size(); i++) {
    for (size_t j = i + 1; j <= s.size(); j++) {
      list.push_back(s.substr(i, j));
    }
  }
}


#endif
