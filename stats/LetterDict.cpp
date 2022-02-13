#include "LetterDict.hpp"

LetterDict::LetterDict() {
	this -> wordcount = 0;
	this -> dict = std::map<char, int>();
	for (char c : ASCII_LOWERCASE) {
		this -> dict.insert(std::pair<char, int>(c, 0));
	}
}

void LetterDict::inc(char letter) {
	this -> dict[letter] += 1;
	this -> wordcount += 1;
}

LetterDict LetterDict::from_words(std::vector<std::string> words, int index) {
	LetterDict ld = LetterDict();
	for (auto & word : words) {
		ld.inc(word[index]);
	}
	return ld;
}
