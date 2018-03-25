CXX = g++
CXXFLAGS = -Wall -g -g3 -std=c++11

LDFLAGS = -l thrift

CPPS = $(wildcard *.cpp)
OBJS = $(CPPS:.cpp=.o)

all:server

server: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	@rm *.o server
