CXX = g++
CXXFLAGS = -std=c++17 -Iconst -Istats -Isolver
VPATH=stats:const:solver

srcs = LetterDict.cpp LetterProbDict.cpp TotalLetterDict.cpp WordStats.cpp GameState.cpp \
			 tester.cpp

main.o: $(srcs:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o
