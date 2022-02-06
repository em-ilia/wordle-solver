CXX = g++
CXXFLAGS = -std=c++17 -Iconst
VPATH=stats:const

#SOURCES = stats/LetterDict.cpp

LetterDict.o:

.PHONY: clean

clean:
	rm -f *.o
