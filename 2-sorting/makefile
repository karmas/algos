CXXFLAGS = -g -Wall -std=c++11
LDLIBS = -lgtest

.DEFAULT_GOAL = test

apps = test pqtest multimerge

multimerge: multimerge.cc pq.h

multimerge: LDLIBS =

pqtest: pq.h

test: sort.h

clean:
	rm -f *.o $(apps)
