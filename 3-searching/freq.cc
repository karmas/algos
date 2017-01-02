#include <map>
#include <iostream>
#include "gtest/gtest.h"
#include "st.h"

using namespace std;

namespace {
  unsigned minWordLen = 0;
}

TEST( freq_counter, validate )
{
  map<string, int> refMap;
  UnorderedListST<string, int> ulst;
  OrderedArrayST<string, int> oast;

  string word;
  while (cin >> word) {
    if (!cin) break;
    if (word.size() < minWordLen)
      continue;

    map<string, int>::iterator refFound = refMap.find(word);
    if (refFound != refMap.end()) {
      ASSERT_TRUE(ulst.contains(word));
      ASSERT_TRUE(oast.contains(word));
      int refVal = refFound->second++;
      int ulstVal = ulst.get(word);
      int oastVal = oast.get(word);
      ASSERT_EQ(refVal, ulstVal);
      ASSERT_EQ(refVal, oastVal);
      ulst.put(word, ulstVal + 1);
      oast.put(word, oastVal + 1);
    }
    else {
      ASSERT_FALSE(ulst.contains(word));
      ASSERT_FALSE(oast.contains(word));
      refMap.insert(make_pair(word, 1));
      ulst.put(word, 1);
      oast.put(word, 1);
    }
    ASSERT_EQ(refMap.size(), ulst.size());
    ASSERT_EQ(refMap.size(), oast.size());
  }

  map<string, int>::iterator refMax = refMap.begin();
  for (map<string, int>::iterator mit = refMax; mit != refMap.end(); ++mit) {
    if (mit->second > refMax->second)
      refMax = mit;
  }

  UnorderedListST<string, int>::iterator ulstMax = ulst.begin();
  for (UnorderedListST<string, int>::iterator it = ulstMax; it != ulst.end(); it = it->_next) {
    if (it->_val > ulstMax->_val)
      ulstMax = it;
  }

  int oastMax = oast._vals[0];
  for (int i = 1; i < oast._size; ++i) {
    if (oast._vals[i] > oastMax)
      oastMax = oast._vals[i];
  }

  ASSERT_EQ(refMax->second, ulstMax->_val);
  ASSERT_EQ(refMax->second, oastMax);
  cout << refMax->first << " " << refMax->second << endl;
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    cout << "give min word length" << endl;
    cout << "input file    | min | result" << endl;
    cout << "tinyTale.txt  | 1   | it 10" << endl;
    cout << "tale.txt      | 8   | business 122" << endl;
    cout << "leipzig1M.txt | 10  | government 24763" << endl;
    return 1;
  }
  minWordLen = atoi(argv[1]);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
