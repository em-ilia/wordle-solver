#ifndef LETTERPROBDICT_H
#define LETTERPROBDICT_H

#include "LetterDict.hpp"
#include <map>

class LetterProbDict {
	private:
		std::map<char, float> dict;
	public:
		LetterProbDict(LetterDict ld);
		LetterProbDict() = default;
		std::map<char, float> getDict(){return this -> dict;}
};

#endif
