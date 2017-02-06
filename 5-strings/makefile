CXXFLAGS = -g -Wall -std=c++11
LDLIBS = -lgtest

.DEFAULT_GOAL = testtrie

apps = testsort testtrie

testsort: testsort.cc sort.h

testtrie: testtrie.cc trie.h utils.h

clean:
	rm -f *.o $(apps)
