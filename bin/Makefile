CXX := g++
CXXFLAGS := -g -Wall -O3 -std=c++11
INSPIREINCLUDE := -I ../../Inspire2BibTeX/

all: html.o reslog tipslog gitupdate diarylog

html.o:	html.cpp
	$(CXX) $(CXXFLAGS) -o html.o -c html.cpp

reslog.o:	reslog.cpp
	$(CXX) $(CXXFLAGS) $(INSPIREINCLUDE) -o reslog.o -c reslog.cpp

reslog: reslog.o html.o
	$(CXX) $(CXXFLAGS) -o reslog reslog.o html.o

tipslog.o:	tipslog.cpp
	$(CXX) $(CXXFLAGS) -o tipslog.o -c tipslog.cpp

tipslog:	tipslog.o html.o
	$(CXX) $(CXXFLAGS) -o tipslog tipslog.o html.o

gitupdate.o:	gitupdate.cpp
	$(CXX) $(CXXFLAGS) -o gitupdate.o -c gitupdate.cpp

gitupdate:	gitupdate.o html.o
	$(CXX) $(CXXFLAGS) -o gitupdate gitupdate.o html.o

diarylog.o:	diarylog.cpp
	$(CXX) $(CXXFLAGS) -o diarylog.o -c diarylog.cpp

diarylog:	diarylog.o html.o
	$(CXX) $(CXXFLAGS) -o diarylog diarylog.o html.o

clean:
	$(RM) *.o reslog tipslog gitupdate diarylog
