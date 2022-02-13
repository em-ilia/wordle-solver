#include "GameState.hpp"
#include <iostream>


GameState::GameState(std::vector<AugmentedWord> initialList) {
	this -> wl = initialList;
	state = "?????";
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
	for (char c : required) {
		disallowed.erase(c);
	}
}

void GameState::recalculate() {
	filter_disallowed();
	filter_required();
	filter_positional();
	filter_anti();
}

std::vector<AugmentedWord> GameState::getWordList() {
	return wl;
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
		wl.erase(std::remove_if(wl.begin(), wl.end(),
				[letter](auto aug_word) {
					return aug_word.word.find(letter) != std::string::npos;
				}), wl.end());
	}
}

void GameState::filter_required() {
	for (char letter : required) {
		wl.erase(std::remove_if(wl.begin(), wl.end(),
				[letter](auto aug_word) {
					return aug_word.word.find(letter) == std::string::npos;
				}), wl.end());
	}
}

void GameState::filter_positional() {
	for (int i = 0; i < 5; i++) {
		if (state[i] == '?') continue;
		wl.erase(std::remove_if(wl.begin(),wl.end(),
				[this, i](auto aug_word) {
					return aug_word.word[i] != this -> state[i];
				}), wl.end());
	}
}

void GameState::filter_anti() {
	for (auto antiPair : anti) {
		for (auto pos: antiPair.second) {
			wl.erase(std::remove_if(wl.begin(),wl.end(),
					[antiPair, pos](auto aug_word) {
						return aug_word.word[pos] == antiPair.first;
					}), wl.end());
		}
	}
}

void GameState::DEBUG_PRINT_STATE() {
	// PRINT STATE

	std::cout << "STATE: " << state << "\n";

	// PRINT DISALLOWED

	std::cout << "DISALLOWED: \n";
	for (char c : disallowed) {
		std::cout << c << " ";
	}
	std::cout << "\n";

	// PRINT REQUIRED
	std::cout << "REQUIRED: \n";
	for (char c : required) {
		std::cout << c << " ";
	}
	std::cout << "\n";

	// PRINT ANTI
	// not implemented

}
