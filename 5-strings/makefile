CXXFLAGS = -g -Wall -std=c++11
LDLIBS = -lgtest

.DEFAULT_GOAL = testsubstring

apps = testsort testtrie testsubstring

testsort: testsort.cc sort.h

testtrie: testtrie.cc trie.h utils.h

testsubstring: testsubstring.cc substring.h utils.h

clean:
	rm -f *.o $(apps)
