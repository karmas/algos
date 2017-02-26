#ifndef GRAPH_H
#define GRAPH_H

#include <cassert>
#include <list>
#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include <fstream>
#include <cstring>

struct Graph {
  typedef std::list<int> adjList_t;
  typedef std::vector<adjList_t> adjLists_t;

  Graph(int V)
    : _V(V), _E(0)
  {
    _adjLists.assign(_V, adjList_t());
  }

  Graph(std::istream &in)
    : _V(0), _E(0)
  {
    in >> _V;
    _adjLists.assign(_V, adjList_t());
    int e = 0;
    in >> e;
    int v = 0, w = 0;
    for (int i = 0; i < e; ++i) {
      in >> v;
      in >> w;
      addEdge(v, w);
    }
    assert (e == _E);
  }

  int V() const { return _V; }
  int E() const { return _E; }

  void addEdge(int v, int w) {
    _adjLists[v].push_front(w);
    _adjLists[w].push_front(v);
    ++_E;
  }

  const adjList_t &adj(int v) const {
    return _adjLists[v];
  }

  int _V = 0;
  int _E = 0;
  adjLists_t _adjLists;
};

struct DepthFirstSearch {
  DepthFirstSearch(Graph g, int s) {
    _marked.assign(g.V(), false);
    dfs(g, s);
  }

  void dfs(Graph g, int v) {
    ++_count;
    _marked[v] = true;
    for(int u : g.adj(v)) {
      if (_marked[u]) continue;
      dfs(g, u);
    }
  }

  bool marked(int v) const { return _marked[v]; }
  int count() const { return _count; }

  std::vector<bool> _marked;
  int _count = 0;
};

struct Paths {
  virtual bool hasPathTo(int v) = 0;
  virtual void pathTo(int v, std::list<int> &l) = 0;
};

struct DepthFirstPaths : public Paths {
  DepthFirstPaths(Graph g, int s)
    : _s(s), _marked(g.V(), false), _edgeTo(g.V(), -1)
  {
    dfs(g, s);
  }

  void dfs(Graph g, int v) {
    _marked[v] = true;
    for (int w : g.adj(v)) {
      if (_marked[w]) continue;
      _edgeTo[w] = v;
      dfs(g, w);
    }
  }

  virtual bool hasPathTo(int v) {
    return _marked[v];
  }

  virtual void pathTo(int v, std::list<int> &l) {
    while (v != _s) {
      l.push_front(v);
      v = _edgeTo[v];
    }
    l.push_front(v);
  }

  const int _s;
  std::vector<bool> _marked;
  std::vector<int> _edgeTo; // most recent adjacent vertex
};

struct BreadthFirstPaths : public Paths {
  BreadthFirstPaths(Graph g, int s)
    : _s(s), _marked(g.V(), false), _edgeTo(g.V(), -1)
  {
    bfs(g, s);
  }

  void bfs(Graph g, int s) {
    std::queue<int> q;
    _marked[s] = true;
    q.push(s);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int w : g.adj(v)) {
        if (_marked[w]) continue;
        _marked[w] = true;
        _edgeTo[w] = v;
        q.push(w);
      }
    }
  }

  virtual bool hasPathTo(int v) {
    return _marked[v];
  }

  virtual void pathTo(int v, std::list<int> &l) {
    while (v != _s) {
      l.push_front(v);
      v = _edgeTo[v];
    }
    l.push_front(v);
  }

  const int _s;
  std::vector<bool> _marked;
  std::vector<int> _edgeTo; // most recent adjacent vertex
};

struct CC {
  CC(Graph g)
    : _id(g.V(), 0), _marked(g.V(), false)
  {
    for (int v = 0; v < g.V(); v++) {
      if (_marked[v]) continue;
      dfs(g, v);
      ++_count;
    }
  }

  void dfs(Graph g, int v) {
    _marked[v] = true;
    _id[v] = _count;
    for (int w : g.adj(v)) {
      if (_marked[w]) continue;
      dfs(g, w);
    }
  }

  bool connected(int v, int w) const { return _id[v] == _id[w]; }
  int count() const { return _count; }
  int id(int v) const { return _id[v]; }

  int _count = 0;
  std::vector<int> _id;
  std::vector<bool> _marked;
};

struct SymbolGraph {
  SymbolGraph(const std::string &fname, const std::string &delim)
    : _g(0)
  {
    addMappings(fname, delim);
    addEdges(fname, delim);
  }

  ~SymbolGraph() {
    delete _g;
  }

  void tokenize(const std::string record, std::vector<std::string> &tokens,
      const std::string &delim) {
    const int bufLen = record.size() + 1;
    char buf[bufLen];
    std::strncpy(buf, record.c_str(), bufLen);
    const char *token = std::strtok(buf, delim.c_str());
    while (token) {
      tokens.push_back(token);
      token = std::strtok(0, delim.c_str());
    }
    /*
    for (size_t i = 0; i < tokens.size(); i++) {
      printf("%s ", tokens[i].c_str());
    }
    puts("");
    */
  }

  void addMappings(const std::string &fname, const std::string &delim) {
    std::ifstream inf(fname);
    std::string line;
    std::vector<std::string> tokens;
    while (getline(inf, line)) {
      tokenize(line, tokens, delim);
      for (size_t i = 0; i < tokens.size(); i++) {
        addVertex(tokens[i]);
      }
      tokens.clear();
    }
    _g = new Graph(_st.size());
  }

  void addEdges(const std::string &fname, const std::string &delim) {
    std::ifstream inf(fname);
    std::string line;
    std::vector<std::string> tokens;
    while (getline(inf, line)) {
      tokenize(line, tokens, delim);
      int v = index(tokens[0]);
      for (size_t i = 1; i < tokens.size(); i++) {
        _g->addEdge(v, index(tokens[i]));
      }
      tokens.clear();
    }
  }

  void addVertex(const std::string &vs) {
    if (contains(vs)) return;
    int v = _st.size();
    _st.insert(make_pair(vs, v));
    _keys.push_back(vs);
  }

  bool contains(const std::string &key) const {
    return _st.count(key) == 1;
  }
  int index(const std::string &key) const {
    std::map<std::string, int>::const_iterator it = _st.find(key);
    if (it != _st.end()) {
      return it->second;
    }
    return -1;
  }
  std::string name(int v) const { return _keys[v]; }
  Graph &G() const { return *_g; }

  std::map<std::string, int> _st;
  std::vector<std::string> _keys;
  Graph *_g;
};

#endif
