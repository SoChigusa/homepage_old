CXX := icpc
CXXFLAGS := -g -Wall -Ofast -std=c++11

all: html.o reslog

html.o:	html.cpp
	$(CXX) $(CXXFLAGS) -o html.o -c html.cpp

reslog.o: reslog.cpp
	$(CXX) $(CXXFLAGS) -o reslog.o -c reslog.cpp

reslog: reslog.o html.o
	$(CXX) $(CXXFLAGS) -o reslog reslog.o html.o

clean:
	$(RM) *.o reslog
