#include "GameState.hpp"


GameState::GameState(std::vector<AugmentedWord> initialList) {
	this -> initialList = initialList;
	this -> recalculate();
}

void GameState::enter(std::string word, std::array<int, 5> res) {
	for (int i = 0; i < 5; i++) {
		if (res[i] == 0) {
			addDisallowed(word[i]);
		} else if (res[i] == 1) {
			addRequired(word[i]);
			addAnti(i, word[i]);
		} else if (res[i] == 2) {
			addState(i, word[i]);
			addRequired(word[i]);
		}
	}

	std::unordered_set<char> diff;
	std::set_difference(disallowed.begin(), disallowed.end(),
											required.begin(), required.end(),
											std::inserter(diff, diff.end()));
	disallowed = diff;
}

void GameState::recalculate() {
	filter_disallowed();
	filter_required();
	filter_positional();
	filter_anti();
}

void GameState::addDisallowed(char letter) {
	disallowed.insert(letter);
}

void GameState::addRequired(char letter) {
	required.insert(letter);
}

void GameState::addAnti(int pos, char letter) {
	if (anti.find(letter) != anti.end()) {
		anti[letter].insert(pos);
	} else {
		anti.insert( std::pair<char, std::unordered_set<int>>(letter, {pos}) );
	}
}

void GameState::addState(int pos, char letter) {
	state[pos] = letter;
}
