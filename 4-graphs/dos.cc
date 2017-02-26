#include "graph.h"
using namespace std;

int main(int argc, const char *argv[])
{
  if (argc < 4) {
    printf("usage: symgraphfile delimiter sourcevertex\n");
    return 1;
  }

  SymbolGraph sg(argv[1], argv[2]);
  Graph &g = sg.G();
  if (!sg.contains(argv[3])) {
    cout << "--no source in graph" << endl;
    return 1;
  }
  int s = sg.index(argv[3]);
  BreadthFirstPaths paths(g, s);

  string line;
  list<int> found;
  while (getline(cin, line)) {
    if (!sg.contains(line)) {
      cout << "--no symbol" << endl;
      continue;
    }
    int v = sg.index(line);
    if (!paths.hasPathTo(v)) {
      cout << "--no path" << endl;
      continue;
    }
    paths.pathTo(v, found);
    for (int w : found) {
      cout << "   " << sg.name(w) << endl;
    }
    found.clear();
  }

  return 0;
}
