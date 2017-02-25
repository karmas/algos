CXXFLAGS = -g -Wall -std=c++11
LDLIBS = -lgtest

.DEFAULT_GOAL = conn

apps = testgraph paths conn

testgraph: testgraph.cc graph.h

paths: paths.cc graph.h

conn: conn.cc graph.h

clean:
	rm -f *.o $(apps)
