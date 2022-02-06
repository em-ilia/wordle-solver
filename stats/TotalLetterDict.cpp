#include "TotalLetterDict.hpp"

TotalLetterDict TotalLetterDict::from_words(std::vector<std::string> words) {
	TotalLetterDict tld = TotalLetterDict();
	for (auto & word : words) {
		for (auto letter : word) {
			tld.inc(letter);
		}
	}
	return tld;
}
