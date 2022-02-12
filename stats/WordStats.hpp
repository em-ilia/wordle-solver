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
bool compareAugmentedWord_prob(AugmentedWord x, AugmentedWord y);
bool compareAugmentedWord_alpha(AugmentedWord x, AugmentedWord y);

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
		std::vector<AugmentedWord> maximizeWordProb(float POS = 1.0, float TOT = 0.0);
};

#endif
