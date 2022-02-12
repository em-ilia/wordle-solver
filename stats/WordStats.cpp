#include "WordStats.hpp"

bool compareAugmentedWord_prob(AugmentedWord x, AugmentedWord y) {
	return x.prob < y.prob;
}
bool compareAugmentedWord_alpha(AugmentedWord x, AugmentedWord y) {
	return x.word < y.word;
}

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

std::vector<AugmentedWord> WordStats::maximizeWordProb_pos() {
	std::vector<AugmentedWord> augmented_wl;
	std::array<float, 5> t_array;
	float t_sum;

	for (auto word : this -> wordlist) {
		t_sum = 0;
		for (int i = 0; i < 5; i++) {
			t_array[i] = this -> letterprobdicts[i].getDict()[word[i]];
		}
		for (float f : t_array) {
			t_sum += f;
		}

		augmented_wl.push_back((AugmentedWord){t_sum, word});
	}

	return augmented_wl;
}

std::vector<AugmentedWord> WordStats::maximizeWordProb_tot() {
	std::vector<AugmentedWord> augmented_wl;
	float t_sum;

	for (auto word : wordlist) {
		t_sum = 0;
		for (auto letter : word) {
			t_sum += total_letterprobdict.getDict()[letter];
		}

		augmented_wl.push_back((AugmentedWord){t_sum, word});
	}

	return augmented_wl;
}

std::vector<AugmentedWord> WordStats::maximizeWordProb(float POS, float TOT) {
	// If TOT not to be considered (default case):
	if (TOT == 0.0) {
		auto v_pos = maximizeWordProb_pos();
		std::sort(v_pos.begin(), v_pos.end(), compareAugmentedWord_prob);
		return v_pos;
	}

	// Main branch
	std::vector<AugmentedWord> augmented_wl;
	auto v_pos = maximizeWordProb_pos();
	auto v_tot = maximizeWordProb_tot();

	for (int i = 0; i < v_pos.size(); i++) {
		augmented_wl.push_back( (AugmentedWord){POS * v_pos[i].prob + TOT * v_tot[i].prob,
													v_pos[i].word} );
	}

	std::sort(augmented_wl.begin(), augmented_wl.end(), compareAugmentedWord_prob);

	return augmented_wl;
}
