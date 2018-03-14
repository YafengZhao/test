CXX = g++
CXXFLAGS = -Wall -g -g3
LDCONFIG = -l QtXml \
		   -l QtCore

PRJ = testxml

CPPS = $(wildcard *.cpp)
OBJS = $(CPPS:.cpp=.o)

all: $(PRJ)

$(PRJ) : $(OBJS)
	$(CXX) -o $@ $< $(LDCONFIG)

clean:
	@rm *.o $(PRJ)
