#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include "gtest/gtest.h"
#include "st.h"

using namespace std;

static int calls = 100;
static bool debug = false;

TEST( random, apis )
{
  map<int, int> refst;
  vector<int> keysInst;
  UnorderedListST<int, int> ulst;
  OrderedArrayST<int, int> oast;
  BST<int, int> bst;

  for (int i = 0; i < calls; i++) {
    if (debug) {
      printf("after %d calls\n", i);
      printf("unordered list: ");
      ulst.print();
      printf("\n");
      printf("ordered array: ");
      oast.print();
      printf("\n");
      printf("bst: ");
      bst.print();
      printf("\n");
    }

    ASSERT_EQ(refst.size(), ulst.size());
    ASSERT_EQ(refst.size(), oast.size());
    ASSERT_EQ(refst.size(), bst.size());

    if (refst.size()) {
      int refMinKey = min_element(refst.begin(), refst.end())->first;
      int bstMinKey = bst.min();
      ASSERT_EQ(refMinKey, bstMinKey);
      int refMaxKey = max_element(refst.begin(), refst.end())->first;
      int bstMaxKey = bst.max();
      ASSERT_EQ(refMaxKey, bstMaxKey);
    }

    int api = rand() % 10;
    if (api < 4) {
      if (debug) printf("api = put\n");
      int key = rand() % calls;

      map<int, int>::const_iterator refCeilingIt = refst.lower_bound(key);
      int refCeiling = 0;
      int bstCeiling = bst.ceiling(key);
      if (refCeilingIt != refst.end()) {
        refCeiling = refCeilingIt->first;
      }
      if (debug) printf("ceiling = %d for %d\n", bstCeiling, key);
      ASSERT_EQ(refCeiling, bstCeiling);

      while (refst.count(key)) {
        if (debug) printf("key = %d already in\n", key);
        key = rand() % calls;
      }
      keysInst.push_back(key);

      if (debug) printf("putting key = %d\n", key);
      refst.insert(make_pair(key, key));
      ASSERT_EQ(refst.count(key), 1);
      ulst.put(key, key);
      ASSERT_TRUE(ulst.contains(key));
      oast.put(key, key);
      ASSERT_TRUE(oast.contains(key));
      bst.put(key, key);
      ASSERT_TRUE(bst.contains(key));
    }
    else if (api > 7) {
      if (debug) printf("api = remove\n");
      if (refst.size() == 0) {
        if (debug) printf("empty\n");
        continue;
      }

      int randomKeyIndex = rand() % keysInst.size();
      int key = keysInst[randomKeyIndex];
      if (debug) printf("removing key = %d\n", key);
      keysInst.erase(keysInst.begin() + randomKeyIndex);

      refst.erase(key);
      ASSERT_EQ(refst.count(key), 0);
      ulst.del(key);
      ASSERT_FALSE(ulst.contains(key));
      oast.del(key);
      ASSERT_FALSE(oast.contains(key));
      bst.del(key);
      ASSERT_FALSE(bst.contains(key));
    }
    else {
      if (debug) printf("api = get\n");
      if (refst.size() == 0) {
        if (debug) printf("empty\n");
        continue;
      }

      int randomKeyIndex = rand() % keysInst.size();
      int key = keysInst[randomKeyIndex];
      if (debug) printf("getting key = %d\n", key);

      ASSERT_EQ(refst.count(key), 1);
      ASSERT_TRUE(ulst.contains(key));
      ASSERT_TRUE(oast.contains(key));
      ASSERT_TRUE(bst.contains(key));

      int refCeiling = refst.lower_bound(key)->first;
      int bstCeiling = bst.ceiling(key);
      ASSERT_EQ(refCeiling, bstCeiling);
    }
  }
}

int main(int argc, char **argv)
{
  srand(time(0));
  if (argc > 1) {
    int a = atoi(argv[1]);
    if (a > 0) calls = a;
  }
  if (argc > 2) {
    debug = true;
  }
  printf("testing %d calls\n", calls);
  printf("debug mode = %d\n", debug);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
