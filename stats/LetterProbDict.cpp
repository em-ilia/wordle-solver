#include "LetterProbDict.hpp"

LetterProbDict::LetterProbDict(LetterDict ld) {
		for (char c : ASCII_LOWERCASE) {
			this -> dict.insert(std::pair<int, float> (c,
						static_cast<float>(ld.getDict()[c])/ld.getWordcount()));
		}
	}

int main(int, char**) {
	LetterDict ld = LetterDict::from_words(WORDS,0);
	LetterProbDict lpd = LetterProbDict(ld);
	std::cout << lpd.getDict()['a'] << "\n";
}
