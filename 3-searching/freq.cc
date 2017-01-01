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

  string word;
  while (cin >> word) {
    if (!cin) break;
    if (word.size() < minWordLen)
      continue;

    map<string, int>::iterator refFound = refMap.find(word);
    if (refFound != refMap.end()) {
      ASSERT_TRUE(ulst.contains(word));
      int refVal = refFound->second++;
      int ulstVal = ulst.get(word);
      ASSERT_EQ(refVal, ulstVal);
      ulst.put(word, ulstVal + 1);
    }
    else {
      ASSERT_FALSE(ulst.contains(word));
      refMap.insert(make_pair(word, 1));
      ulst.put(word, 1);
    }
    ASSERT_EQ(refMap.size(), ulst.size());
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

  ASSERT_EQ(refMax->second, ulstMax->_val);
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
