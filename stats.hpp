#ifndef STATS_H
#define STATS_H

#include <string>
#include <map>
#include <vector>
#include "WORDS.hpp"

const char ASCII_LOWERCASE[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

class LetterDict {
	private:
		int wordcount;
		std::map<char, int> dict;
	public:
		LetterDict();
		void inc(char letter);
		std::map<char,int> getDict() {return this -> dict;}
		int getWordcount() {return this -> wordcount;}
		static LetterDict from_words(std::vector<std::string> words, int index);
};

#endif
