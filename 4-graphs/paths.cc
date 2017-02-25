#include "graph.h"
#include <fstream>
using namespace std;

int main(int argc, const char *argv[])
{
  if (argc < 3) {
    puts("usage: graphfile source_vertex");
    return 1;
  }

  ifstream infile(argv[1]);
  int s = atoi(argv[2]);
  Graph g(infile);
  DepthFirstPaths paths(g, s);
  BreadthFirstPaths bfPaths(g, s);

  std::list<int> currPath;
  for (int v = 0; v < g.V(); v++) {
    printf("%d to %d: ", s, v);
    if (!paths.hasPathTo(v)) {
      printf("none\n");
      continue;
    }
    paths.pathTo(v, currPath);
    bool notFirst = false;
    for (int w : currPath) {
      if (notFirst) printf("-");
      printf("%d", w);
      notFirst = true;
    }
    puts("");
    currPath.clear();
  }

  printf("shortest paths\n");
  for (int v = 0; v < g.V(); v++) {
    printf("%d to %d: ", s, v);
    if (!bfPaths.hasPathTo(v)) {
      printf("none\n");
      continue;
    }
    bfPaths.pathTo(v, currPath);
    bool notFirst = false;
    for (int w : currPath) {
      if (notFirst) printf("-");
      printf("%d", w);
      notFirst = true;
    }
    puts("");
    currPath.clear();
  }
  
  return 0;
}
