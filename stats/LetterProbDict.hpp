#ifndef LETTERPROBDICT_H
#define LETTERPROBDICT_H

#include "LetterDict.hpp"
#include <map>
#include <iostream>

class LetterProbDict {
	private:
		std::map<char, float> dict;
	public:
		LetterProbDict(LetterDict ld);
		std::map<char, float> getDict(){return this -> dict;}
};

#endif
