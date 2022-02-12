#include "GameState.hpp"


GameState::GameState(std::vector<AugmentedWord> initialList) {
	this -> wl = initialList;
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

// ADD FUNCTIONS

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

// FILTER FUNCTIONS
// me when I set c++17 in my makefile so I can't use ranges
// smh

void GameState::filter_disallowed() {
	for (char letter : disallowed) {
		std::remove_if(wl.begin(), wl.end(),
				[letter](auto aug_word) {
					return aug_word.word.find(letter) == std::string::npos;
				});
	}
}

void GameState::filter_required() {
	for (char letter : required) {
		std::remove_if(wl.begin(), wl.end(),
				[letter](auto aug_word) {
					return aug_word.word.find(letter) != std::string::npos;
				});
	}
}

void GameState::filter_positional() {
	for (int i = 0; i < 5; i++) {
		if (state[i] == '?') continue;
		std::remove_if(wl.begin(),wl.end(),
				[this, i](auto aug_word) {
					return aug_word.word[i] != this -> state[i];
				});
	}
}

void GameState::filter_anti() {
	for (auto antiPair : anti) {
		for (auto pos: antiPair.second) {
			std::remove_if(wl.begin(),wl.end(),
					[antiPair, pos](auto aug_word) {
						return aug_word.word[pos] = antiPair.first;
					});
		}
	}
}
