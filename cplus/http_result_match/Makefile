CXX = g++

CPPFLAGS = -Wall -g3 -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0 -fpermissive -fPIC

INC = -I . \
	  -I /usr/include/x86_64-linux-gnu/qt5/

LDFLAGS = -L . \
		  -l curlpp \
		  -l curl \
		  -l ssl \
		  -l crypto \
		  -L /usr/lib/x86_64-linux-gnu/ \
		  -l Qt5Xml \
		  -l Qt5Core \
		  -l boost_system \
		  -l boost_filesystem

PROJ = request

CPPS = $(wildcard *.cpp)

OBJS = $(CPPS:.cpp=.o)

all: $(PROJ)

%.o:%.cpp 
	$(CXX) $(CPPFLAGS) $(INC) -o $@ -c $<

$(PROJ):$(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

clean:
	rm *.o $(PROJ) -rf

