#include <fstream>
#include "union-find.h"

using namespace std;

int main(int argc, char **argv)
{
	assert(argc > 1);

	ifstream in(argv[1]);
	int nsites = 0;
	in >> nsites;
	//UF uf(nsites);
	//UFunion uf(nsites);
	UFweighted uf(nsites);

	while (in) {
		int p = 0;
		int q = 0;
		in >> p;
		in >> q;
		if (!in) break;

		if (!uf.connected(p, q)) {
			uf.unite(p, q);
			cout << p << " " << q << endl;
		}
	}

	printf("%d components\n", uf.count());
}
