#include "graph.h"
#include <fstream>

using namespace std;

int main(int argc, const char *argv[])
{
  if (argc < 2) {
    puts("usage: graphfile");
    return 1;
  }

  ifstream infile(argv[1]);
  Graph g(infile);
  CC cc(g);

  vector<list<int>> components(cc.count());
  for (int v = 0; v < g.V(); v++) {
    int currId = cc.id(v);
    components[currId].push_front(v);
  }

  printf("%d components\n", cc.count());
  for (int id = 0; id < cc.count(); id++) {
    bool notFirst = false;
    for (int v: components[id]) {
      if (notFirst) printf(" ");
      printf("%d", v);
      notFirst = true;
    }
    notFirst = false;
    puts("");
  }

  return 0;
}
