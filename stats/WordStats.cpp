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

	std::sort(augmented_wl.begin(), augmented_wl.end(),
						compareAugmentedWord);

	return augmented_wl;
}

int main() {
	// Must switch func declaration to public for this to run,
	// but it does work when tested at this commit!
	WordStats ws = WordStats(WORDS);
	std::cout << ws.maximizeWordProb_pos().back().word << "\n";
}
