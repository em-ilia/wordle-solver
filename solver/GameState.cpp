#include "GameState.hpp"
#include <iostream>


GameState::GameState(std::vector<AugmentedWord> initialList) {
	this -> wl = initialList;
	state = "?????";
	this -> recalculate();
}

void GameState::enter(std::string word, std::array<int, 5> res) {
	//std::cout << "BEGIN CALL TO ENTER" << "\n";
	for (int i = 0; i < 5; i++) {
		if (res[i] == 0) {
			//std::cout << "In enter, res is 0: disallowing " << word[i] << "\n";
			addDisallowed(word[i]);
		} else if (res[i] == 1) {
			//std::cout << "In enter, res is 1" << "\n";
			//std::cout << "Requiring " << word[i] << "\n";
			//std::cout << "Adding to anti " << word[i] << " at pos " << std::to_string(i) << "\n";
			addRequired(word[i]);
			addAnti(i, word[i]);
		} else if (res[i] == 2) {
			//std::cout << "In enter, res is 2" << "\n";
			addState(i, word[i]);
			addRequired(word[i]);
			//std::cout << "State is now: " << state << "\n";
			//std::cout << "Requiring " << word[i] << "\n";
		}
	}

	std::unordered_set<char> diff;
	std::set_difference(disallowed.begin(), disallowed.end(),
											required.begin(), required.end(),
											std::inserter(diff, diff.end()));
	disallowed = diff;
	//std::cout << "END CALL TO ENTER\n";
}

void GameState::recalculate() {
	std::cout.setstate(std::ios_base::failbit); // DISABLE DEBUG IN RECALCULATE
	std::cout << "\nBEGIN CALL TO RECALCULATE\n";
	filter_disallowed();
	filter_required();
	filter_positional();
	filter_anti();
	std::cout << "END CALL TO RECALCULATE\n";
	std::cout.clear();
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
	std::cout << "BEGIN CALL TO FILTER DISALLOWED\n";
	std::cout << "Initial size of wl is " << std::to_string(wl.size()) << "\n";
	for (char letter : disallowed) {
		std::cout << "Going to test " << letter << "\n";
		wl.erase(std::remove_if(wl.begin(), wl.end(),
				[letter](auto aug_word) {
					//std::cout << "Is " << letter << " in " << aug_word.word << ": " <<
					//std::to_string(aug_word.word.find(letter) != std::string::npos) << "\n";
					return aug_word.word.find(letter) != std::string::npos;
				}), wl.end());
	}
	std::cout << "Final size of wl is " << std::to_string(wl.size()) << "\n";
	std::cout << "END CALL TO FILTER DISALLOWED\n";
}

void GameState::filter_required() {
	std::cout << "BEGIN CALL TO FILTER REQUIRED\n";
	std::cout << "Initial size of wl is " << std::to_string(wl.size()) << "\n";
	for (char letter : required) {
		std::cout << "Going to test " << letter << "\n";
		wl.erase(std::remove_if(wl.begin(), wl.end(),
				[letter](auto aug_word) {
					//std::cout << "Is " << letter << " in " << aug_word.word << ": " <<
					//std::to_string(aug_word.word.find(letter) == std::string::npos) << "\n";
					return aug_word.word.find(letter) == std::string::npos;
				}), wl.end());
	}
	std::cout << "Final size of wl is " << std::to_string(wl.size()) << "\n";
	std::cout << "END CALL TO FILTER REQUIRED\n";
}

void GameState::filter_positional() {
	std::cout << "BEGIN CALL TO FILTER POSITIONAL\n";
	std::cout << "Initial size of wl is " << std::to_string(wl.size()) << "\n";
	std::cout << "Current state is " << state << "\n";
	for (int i = 0; i < 5; i++) {
		//std::cout << "About to test state pos " << std::to_string(i) << " which has value " <<
		//	state[i] << "\n";
		if (state[i] == '?') continue;
		wl.erase(std::remove_if(wl.begin(),wl.end(),
				[this, i](auto aug_word) {
					//std::cout << "Does " << aug_word.word[i] << " match " << state[i] << "?"
					//<< std::to_string(aug_word.word[i] != this -> state[i]) << "\n";
					return aug_word.word[i] != this -> state[i];
				}), wl.end());
	}
	std::cout << "Final size of wl is " << std::to_string(wl.size()) << "\n";
	std::cout << "END CALL TO FILTER POSITIONAL\n";
}

void GameState::filter_anti() {
	std::cout << "BEGIN CALL TO FILTER ANTI\n";
	std::cout << "Initial size of wl is " << std::to_string(wl.size()) << "\n";
	for (auto antiPair : anti) {
		//std::cout << "Going to test " << antiPair.first << " containing " <<
		//	std::to_string(antiPair.second.size()) << " elements" << "\n";
		for (auto pos: antiPair.second) {
			//std::cout << "Testing if " << antiPair.first << " at " << std::to_string(pos) << "\n";
			wl.erase(std::remove_if(wl.begin(),wl.end(),
					[antiPair, pos](auto aug_word) {
						//std::cout << "Is " << aug_word.word[pos] << " equal to " << antiPair.first
						//<< "?" << std::to_string(aug_word.word[pos] == antiPair.first) << "\n";
						return aug_word.word[pos] == antiPair.first;
					}), wl.end());
		}
	}
	std::cout << "Final size of wl is " << std::to_string(wl.size()) << "\n";
	std::cout << "END CALL TO FILTER ANTI\n";
}
