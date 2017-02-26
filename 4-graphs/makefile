CXXFLAGS = -g -Wall -std=c++11
LDLIBS = -lgtest

.DEFAULT_GOAL = dos

apps = testgraph paths conn symgraph dos

testgraph: testgraph.cc graph.h

paths: paths.cc graph.h

conn: conn.cc graph.h

symgraph: symgraph.cc graph.h

dos: dos.cc graph.h

clean:
	rm -f *.o $(apps)
