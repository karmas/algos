#include <iostream>
#include <fstream>
#include <cassert>

#include "pq.h"

using namespace std;

int main(int argc, const char *argv[])
{
    if (argc < 3) {
        cout << "usage: enter at least 2 sorted files with space separated strings" << endl;
        return 1;
    }

    int streams = argc - 1;
    ifstream *ins = new ifstream[streams]();
    for (int i = 1; i < argc; ++i) {
        ins[i-1].open(argv[i]);
        assert(ins[i-1]);
    }

    IndexMinPQ<char> pq(streams);
    char val = 0;
    for (int i = 0; i < streams; ++i) {
        ins[i] >> val;
        pq.insert(i, val);
    }

    cout << "expect: A A B B B C D E F F G H I I J N P Q Q Z" << endl;
    cout << "actual:";

    while (!pq.isEmpty()) {
        cout << " " << pq.min();
        int minStream = pq.delMin();
        ins[minStream] >> val;
        if (ins[minStream]) {
            pq.insert(minStream, val);
        }
    }
    cout << endl;

    delete[] ins;
    return 0;
}
