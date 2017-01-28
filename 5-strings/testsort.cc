#include <algorithm>
#include "gtest/gtest.h"
#include "sort.h"

using namespace std;

bool debug = false;
const int numHi = 50;
const int arrLenHi = 100;
const int iters = 10;

TEST( sort, key_indexed )
{
  for (int i = 0; i < iters; i++) {
    int n = 1 + random(arrLenHi);
    int *refArr = new int[n]();
    int *samArr = new int[n]();
    randomArray(samArr, n, numHi);
    memcpy(refArr, samArr, n * 4);
    qsort(refArr, n, 4, intComp);

    if (debug) {
      printf("before: ");
      print(samArr, n);
    }
    indexedSort(samArr, n, numHi);
    if (debug) {
      printf(" after: ");
      print(samArr, n);
    }
    ASSERT_TRUE(equal(refArr, refArr + n, samArr));

    delete[] refArr;
    delete[] samArr;
  }
}

TEST( sort, lsd )
{
  const int lens[] = { 5, 8, 10 };
  const int strlen = lens[random(3)];
  for (int i = 0; i < iters; i++) {
    int n = 1 + random(arrLenHi);
    vector<string> ref(n, "");
    vector<string> sam(n, "");
    randomFixedLengthStrings(sam, strlen);
    ref = sam;
    sort(ref.begin(), ref.end());

    if (debug) {
      printf("before: ");
      print(sam);
    }
    lsdSort(sam);
    if (debug) {
      printf("after: ");
      print(sam);
    }
    for (size_t i = 0; i < ref.size(); i++) {
      ASSERT_EQ(ref[i], sam[i]);
    }

    ref.clear();
    sam.clear();
  }
}

TEST( sort, msd )
{
  const int maxLen = 5;
  for (int i = 0; i < iters; i++) {
    int n = 1 + random(arrLenHi);
    vector<string> ref(n, "");
    vector<string> sam(n, "");
    randomLengthStrings(sam, maxLen);
    ref = sam;
    sort(ref.begin(), ref.end());

    if (debug) {
      printf("before: ");
      print(sam);
    }
    msdSort(sam);
    if (debug) {
      printf("after: ");
      print(sam);
    }
    for (size_t i = 0; i < ref.size(); i++) {
      ASSERT_EQ(ref[i], sam[i]);
    }

    ref.clear();
    sam.clear();
  }
}

int main(int argc, char **argv)
{
  srand(time(0));
  if (argc > 1) {
    debug = true;
  }
  printf("debug mode = %d\n", debug);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
