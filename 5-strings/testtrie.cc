#include "trie.h"
#include "utils.h"
#include <map>
#include <set>
#include <algorithm>
#include "gtest/gtest.h"

using namespace std;

bool debug = false;
const int calls = 1000;

TEST( trie, random_apis )
{
  const int defaultVal = 7;
  set<string> allKeys;
  map<string, int> refst;
  Trie<int> trie;

  for (int i = 0; i < calls; i++) {
    int randapi = rand() % 10;
    if (randapi < 5) {
      string key;
      randomString(key, 20);
      if (debug) {
        printf("putting key=%s\n", key.c_str());
      }
      refst.insert(make_pair(key, defaultVal));
      trie.put(key, defaultVal);
      ASSERT_TRUE(trie.contains(key));
    }
    else if (randapi < 8) {
      if (refst.size() != 0) {
        int randomEntry = rand() % refst.size();
        const string *key = 0;
        for (map<string, int>::iterator it = refst.begin();
            it != refst.end() && randomEntry >= 0; ++it, --randomEntry) {
          key = &it->first;
        }
        if (debug) {
          printf("getting key=%s\n", key->c_str());
        }
        int trieVal = trie.get(*key);
        ASSERT_EQ(defaultVal, trieVal);
      }
    }
    else {
      if (refst.size() == 0) continue;
      int randomEntry = rand() % refst.size();
      map<string, int>::iterator it = refst.begin();
      for ( ; it != refst.end() && randomEntry > 0; ++it, --randomEntry);
      const string key(it->first);
      if (debug) {
        printf("deleting key=%s\n", key.c_str());
      }
      refst.erase(key);
      trie.remove(key);
      int trieVal = trie.get(key);
      ASSERT_EQ(0, trieVal);
    }

    EXPECT_EQ(refst.size(), trie.sizeCalc());
    ASSERT_EQ(refst.size(), trie.size());
  }

  EXPECT_EQ(refst.size(), trie.sizeCalc());
  ASSERT_EQ(refst.size(), trie.size());

  vector<string> refKeys;
  for (map<string, int>::const_iterator it = refst.begin(); it != refst.end(); ++it) {
    refKeys.push_back(it->first);
  }
  sort(refKeys.begin(), refKeys.end());

  vector<string> trieKeys;
  trie.keys(trieKeys);
  sort(trieKeys.begin(), trieKeys.end());

  ASSERT_EQ(refKeys.size(), trieKeys.size());
  for (size_t i = 0; i < refKeys.size(); ++i) {
    ASSERT_EQ(refKeys[i], trieKeys[i]);
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
