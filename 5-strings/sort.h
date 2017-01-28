#ifndef SORT_H
#define SORT_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

void print(int arr[], int n)
{
  for (int i = 0; i < n; i++) {
    if (i > 0) printf(", ");
    printf("%d", arr[i]);
  }
  printf("\n");
}

void print(const std::vector<std::string> &arr)
{
  for (size_t i = 0; i < arr.size(); i++) {
    if (i > 0) printf(", ");
    printf("%s", arr[i].c_str());
  }
  printf("\n");
}

// @return [0, hi)
int random(int hi)
{
  return rand() % hi;
}

void randomArray(int *arr, int n, int hi)
{
  for (int i = 0; i < n; i++) {
    arr[i] = random(hi);
  }
}

int intComp(const void *i, const void *j)
{
  const int *a = (const int *)i;
  const int *b = (const int *)j;
  return *a - *b;
}

const bool trace = false;
/**
 * @param r base for the keys such that each key is less than r
 */
void indexedSort(int arr[], int n, int r)
{
  // freq of key
  int counts[r + 1];
  memset(counts, 0, (r + 1) * 4);
  for (int i = 0; i < n; i++) {
    counts[arr[i] + 1]++;
  }
  if (trace) {
    print(counts, r + 1);
  }
  // freq of less than key
  for (int i = 0; i < r; i++) {
    counts[i+1] += counts[i];
  }
  if (trace) {
    print(counts, r + 1);
  }

  int aux[n];
  for (int i = 0; i < n; i++) {
    aux[counts[arr[i]]++] = arr[i];
  }
  memcpy(arr, aux, n * 4);
}

void randomFixedLengthString(std::string &s, int len)
{
  const int size = 20; char buf[size] = {};
  for (int i = 0; i < len; i++) {
    snprintf(buf + i, size - i, "%d", random(10));
  }
  s = buf;
}

void randomFixedLengthStrings(std::vector<std::string> &arr, int len)
{
  for (size_t i = 0; i < arr.size(); i++) {
    randomFixedLengthString(arr[i], len);
  }
}

/**
 * only works for base 10 digits
 */
void lsdSort(std::vector<std::string> &arr)
{
  int r = 10;
  int nCounts = r + 1;
  int n = arr.size();
  int w = arr[0].size();

  for (int d = w - 1; d >= 0; --d) {
    int counts[nCounts];
    memset(counts, 0, nCounts * 4);
    for (int i = 0; i < n; i++) {
      char key = arr[i][d];
      int keyInt = key - '0';
      counts[keyInt + 1]++;
    }
    for (int i = 0; i < r; i++) {
      counts[i + 1] += counts[i];
    }
    std::vector<std::string> aux(arr);
    for (int i = 0; i < n; i++) {
      char key = arr[i][d];
      int keyInt = key - '0';
      aux[counts[keyInt]++] = arr[i];
    }
    arr = aux;
  }
}

void randomLengthString(std::string &s, int maxLen)
{
  int len = random(maxLen);
  if (len == 0) len = maxLen;

  randomFixedLengthString(s, len);

  /*
  const int size = len + 1; char buf[size];
  memset(buf, 0, size);
  for (int i = 0; i < len; i++) {
    snprintf(buf + i, size - i, "%c", 'a');
  }
  s = buf;
  */
}

void randomLengthStrings(std::vector<std::string> &arr, int maxLen)
{
  for (size_t i = 0; i < arr.size(); i++) {
    randomLengthString(arr[i], maxLen);
  }
}

// @return 0 is digit is not in string else index
int keyIndex(std::string &s, size_t d)
{
  char key = '0' - 1;
  if (d < s.size()) key = s[d];
  return key - '0' + 1;;
}

/**
 * [s, e) key indexed sorting on dth digit
 */
void msdSort(std::vector<std::string> &arr, int s, int e, int d)
{
  int n = e - s;
  if (n <= 1) return;

  int r = 10;
  int nCounts = r + 2;
  int counts[nCounts];
  memset(counts, 0, nCounts * 4);

  for (int i = s; i < e; i++) {
    int keyInt = keyIndex(arr[i], d);
    counts[keyInt + 1]++;
  }
  for (int i = 0; i < nCounts - 1; i++) {
    counts[i+1] += counts[i];
  }

  std::vector<std::string> aux(n, "");
  for (int i = s; i < e; i++) {
    int keyInt = keyIndex(arr[i], d);
    aux[counts[keyInt]++] = arr[i];
  }

  for (int i = 0; i < n; i++) {
    arr[s + i] = aux[i];
  }

  for (int i = 1; i < nCounts; i++) {
    msdSort(arr, s + counts[i-1], s + counts[i], d+1);
  }
}

/**
 * only works for base 10 digits
 */
void msdSort(std::vector<std::string> &arr)
{
  msdSort(arr, 0, arr.size(), 0);
}

#endif
