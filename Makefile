CXX = g++
CXXFLAGS = -std=c++17 -Iconst
VPATH=stats:const

LetterDict.o:
TotalLetterDict.o:

.PHONY: clean

clean:
	rm -f *.o
