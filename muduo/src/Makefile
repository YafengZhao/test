CXX = g++
CXXFLAGS = -Wall -g -g3 -std=c++11

CXXFLAGS += -I ../include

LDFLAGS = -L ../lib/ \
		  -l muduo_net \
		  -l muduo_base \
		  -l pthread

PROJ = eventloop_test

CPPS = $(wildcard *.cpp)
OBJS = $(CPPS:.cpp=.o)

all:$(PROJ)

$(PROJ): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	@rm *.o server
