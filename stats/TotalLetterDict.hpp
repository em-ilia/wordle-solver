#ifndef TOTALLETTERDICT_H
#define TOTALLETTERDICT_H

#include "LetterDict.hpp"
#include <vector>
#include <string>

class TotalLetterDict: public LetterDict {
	public:
		static TotalLetterDict from_words(std::vector<std::string> words);
};

#endif
