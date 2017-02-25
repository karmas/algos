#ifndef GRAPH_H
#define GRAPH_H

#include <cassert>
#include <list>
#include <vector>
#include <iostream>
#include <queue>

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

#endif
