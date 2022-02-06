CXX = g++
CXXFLAGS = -std=c++17 -Iconst
VPATH=stats:const

srcs = LetterDict.cpp LetterProbDict.cpp TotalLetterDict.cpp

main.o: $(srcs:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o
