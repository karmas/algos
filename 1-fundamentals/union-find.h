#include <cassert>
#include <iostream>
using namespace std;

// quick find
struct UF {
	UF(int comps)
		: _comp_alloc(comps), _comp(new int[_comp_alloc]), _ncomps(comps)
	{
		for (int i = 0; i < _comp_alloc; i++) {
			_comp[i] = i;
		}
	}

	void unite(int p, int q) {
		int u = find(p);
		int v = find(q);
		if (u == v) return;

		for (int i = 0; i < _comp_alloc; i++) {
			if (_comp[i] == u)
				_comp[i] = v;
		}
		--_ncomps;
	}

	int find(int p) {
		assert(p >= 0 && p < _comp_alloc);
		return _comp[p];
	}
	bool connected(int p, int q) { return find(p) == find(q); }
	int count() { return _ncomps; }

	int _comp_alloc = 0;
	int *_comp = 0;
	int _ncomps = 0;
};

// quick union
struct UFunion {
	UFunion(int comps)
		: _comp_alloc(comps), _comp(new int[_comp_alloc]), _ncomps(comps)
	{
		for (int i = 0; i < _comp_alloc; i++) {
			_comp[i] = i;
		}
	}

	void unite(int p, int q) {
		int u = find(p);
		int v = find(q);
		if (u == v) return;

		_comp[u] = v;
		--_ncomps;
	}

	int find(int p) {
		assert(p >= 0 && p < _comp_alloc);
		int c = p;
		while (c != _comp[c]) c = _comp[c];
		return c;
	}
	bool connected(int p, int q) { return find(p) == find(q); }
	int count() { return _ncomps; }

	int _comp_alloc = 0;
	int *_comp = 0;
	int _ncomps = 0;
};

// weighted quick union
struct UFweighted {
	UFweighted(int comps)
		: _comp_alloc(comps), _comp(new int[_comp_alloc]), _ncomps(comps),
		_size(new int[_comp_alloc])
	{
		for (int i = 0; i < _comp_alloc; i++) {
			_comp[i] = i;
			_size[i] = 1;
		}
	}

	void unite(int p, int q) {
		int u = find(p);
		int v = find(q);
		if (u == v) return;

		if (_size[u] < _size[v]) {
			_comp[u] = v;
			_size[v] += _size[u];
		}
		else {
			_comp[v] = u;
			_size[u] += _size[v];
		}

		--_ncomps;
	}

	int find(int p) {
		assert(p >= 0 && p < _comp_alloc);
		int c = p;
		while (c != _comp[c]) c = _comp[c];
		return c;
	}
	bool connected(int p, int q) { return find(p) == find(q); }
	int count() { return _ncomps; }

	int _comp_alloc = 0;
	int *_comp = 0;
	int _ncomps = 0;
	int *_size = 0;
};
