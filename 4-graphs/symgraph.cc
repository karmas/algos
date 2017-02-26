#include "graph.h"
using namespace std;

int main(int argc, const char *argv[])
{
  if (argc < 3) {
    printf("usage: %s symgraphfile delimiter\n", argv[0]);
    return 1;
  }

  SymbolGraph sg(argv[1], argv[2]);
  Graph g = sg.G();

  string line;
  while (getline(cin, line)) {
    if (!sg.contains(line)) {
      cout << "--not found" << endl;
      continue;
    }
    int v = sg.index(line);
    for (int w : g.adj(v)) {
      cout << "   " << sg.name(w) << endl;
    }
  }

  return 0;
}
