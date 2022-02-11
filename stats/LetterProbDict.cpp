#include "LetterProbDict.hpp"

LetterProbDict::LetterProbDict(LetterDict ld) {
		for (char c : ASCII_LOWERCASE) {
			this -> dict.insert(std::pair<int, float> (c,
						static_cast<float>(ld.getDict()[c])/ld.getWordcount()));
		}
	}
