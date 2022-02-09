#include "WordStats.hpp"

WordStats::WordStats(std::vector<std::string> words) {
	this -> wordlist = words;
	this -> calculate();
}

void WordStats::calculate() {
	this -> calc_letterdicts();
	this -> calc_letterprobdicts();
	this -> calc_total_letterdict();
	this -> calc_total_letterprobdict();
}

void WordStats::calc_letterdicts() {
	for (int i = 0; i<5; i++) {
		this -> letterdicts.push_back(LetterDict::from_words(this -> wordlist, i));
	}
}

void WordStats::calc_letterprobdicts() {
	for (auto ld : this -> letterdicts) {
		this -> letterprobdicts.push_back(LetterProbDict(ld));
	}
}

void WordStats::calc_total_letterdict() {
	this -> total_letterdict = TotalLetterDict::from_words(this -> wordlist);
}

void WordStats::calc_total_letterprobdict() {
	this -> total_letterprobdict = LetterProbDict(static_cast<LetterDict>(this -> total_letterdict));
}
