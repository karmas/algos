#ifndef UTILS_H
#define UTILS_H

#include <iostream>

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

#endif
