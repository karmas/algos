CXXFLAGS = -g -Wall -std=c++11
LDLIBS = -lgtest

.DEFAULT_GOAL = freq

apps = freq tracer

freq: freq.cc st.h

tracer: tracer.cc st.h

clean:
	rm -f *.o $(apps)
