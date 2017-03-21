CXX=		g++
CXXFLAGS=	-g -Wall

all: site-tester

site-tester: test_read.cc *.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean: 
	rm -rf *.o *.dSYM site-tester