#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include "st.h"

using namespace std;

void init(vector<string> &items)
{
  string val;
  while (cin >> val) {
    if (!cin) {
      break;
    }
    items.push_back(val);
    //cout << " -> " << val << endl;
  }
}

template<typename st_t>
void trace(const vector<string> &items, st_t &st)
{
  for (int i = 0; i < items.size(); ++i) {
    st.put(i, items[i]);
  }
  st.print();
}

int main(int argc, char **argv)
{
  vector<string> items;
  init(items);
  UnorderedListST<int, string> ulst;
  trace(items, ulst);
}
