#include "substring.h"

#include <vector>
#include <algorithm>

#include "utils.h"
#include "gtest/gtest.h"

using namespace std;

bool debug = false;
const int calls = 1000;

TEST( substring, search )
{
  const int maxLen = 10;
  string str;
  vector<string> subStrings;

  for (int i = 0; i < calls; i++) {
    randomString(str, maxLen);
    if (debug) {
      printf("string '%s'\n", str.c_str());
    }
    genSubStrings(str, subStrings);
    for (size_t i = 0; i < subStrings.size(); i++) {
      if (debug) {
        printf("find '%s' in '%s'\n", subStrings[i].c_str(), str.c_str());
      }
      size_t pos = str.find(subStrings[i]);
      ASSERT_EQ(pos, findSubStringBruteAll(str, subStrings[i]));
      ASSERT_EQ(pos, findSubStringBrute(str, subStrings[i]));
      ASSERT_EQ(pos, findSubStringBrute2(str, subStrings[i]));
      ASSERT_EQ(pos, findSubStringBrute2alt(str, subStrings[i]));
      KMP kmp(subStrings[i]);
      ASSERT_EQ(pos, kmp.search(str));
      BM bm(subStrings[i]);
      ASSERT_EQ(pos, bm.search(str));
      RK rk(subStrings[i]);
      ASSERT_EQ(pos, rk.search(str));

      int j = rand() % maxLen;
      string junk = subStrings[i] + to_string(j);
      if (debug) {
        printf("don't find '%s'\n", junk.c_str());
      }
      pos = str.find(junk);
      ASSERT_EQ(pos, findSubStringBruteAll(str, junk));
      ASSERT_EQ(pos, findSubStringBrute(str, junk));
      ASSERT_EQ(pos, findSubStringBrute2(str, junk));
      ASSERT_EQ(pos, findSubStringBrute2alt(str, junk));
      KMP kmp2(junk);
      ASSERT_EQ(pos, kmp2.search(str));
      BM bm2(junk);
      ASSERT_EQ(pos, bm2.search(str));
      RK rk2(junk);
      ASSERT_EQ(pos, rk2.search(str));
    }
    subStrings.clear();
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
