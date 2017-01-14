CXXFLAGS = -g -Wall -std=c++11
LDLIBS = -lgtest

.DEFAULT_GOAL = testapi

apps = freq tracer testapi

testapi: testapi.cc st.h

freq: freq.cc st.h

tracer: tracer.cc st.h

clean:
	rm -f *.o $(apps)
