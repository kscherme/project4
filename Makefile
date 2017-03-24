CXX=		/afs/nd.edu/user14/csesoft/new/bin/g++
CXXFLAGS=	-g -Wall -lcurl -std=gnu++11 -static-libstdc++

all: site-tester

site-tester: main.cc *.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean: 
	rm -rf *.o *.dSYM *.csv site-tester
