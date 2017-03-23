CXX=		g++
CXXFLAGS=	-g -Wall -lcurl -std=gnu++11

all: site-tester

site-tester: main.cc *.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean: 
	rm -rf *.o *.dSYM *.csv site-tester