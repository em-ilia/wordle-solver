#ifndef WORDSTATS_H
#define WORDSTATS_H

#include "LetterDict.hpp"
#include "LetterProbDict.hpp"
#include "TotalLetterDict.hpp"

#include <string>
#include <array>
#include <vector>
#include <algorithm>

struct AugmentedWord {
	float prob;
	std::string word;
};
bool compareAugmentedWord(AugmentedWord x, AugmentedWord y) {
	return x.prob < y.prob;
}

class WordStats {
	private:
		std::vector<std::string> wordlist;
		std::vector<LetterDict> letterdicts;
		std::vector<LetterProbDict> letterprobdicts;
		TotalLetterDict total_letterdict;
		// This has to be a pointer because there is no default constructor smh
		LetterProbDict total_letterprobdict; // No need to make a different class this time

		void calc_letterdicts();
		void calc_letterprobdicts();
		void calc_total_letterdict();
		void calc_total_letterprobdict();

		std::vector<AugmentedWord> maximizeWordProb_pos();
		std::vector<AugmentedWord> maximizeWordProb_tot();
	public:
		WordStats(std::vector<std::string> words);
		void calculate();
		std::vector<AugmentedWord> maximizeWordProb(float POS, float TOT);
};

#endif
