#include "trie.h"
#include "utils.h"
#include <map>
#include <set>
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
    int randapi = rand() % 5;
    if (randapi < 3) {
      string key;
      randomString(key, 20);
      if (debug) {
        printf("putting key=%s\n", key.c_str());
      }
      refst.insert(make_pair(key, defaultVal));
      trie.put(key, defaultVal);
      ASSERT_TRUE(trie.contains(key));
    }
    else {
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
        ASSERT_TRUE(trieVal != 0);
      }
    }
  }

  ASSERT_EQ(refst.size(), trie.size());
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
