#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "WordStats.hpp"
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <iterator>
#include <unordered_set>

class GameState{
	private:
		std::vector<AugmentedWord> wl;

		std::string state;
		std::unordered_set<char> disallowed;
		std::unordered_set<char> required;
		std::map<char, std::unordered_set<int>> anti;
	public:
		GameState(std::vector<AugmentedWord> initialList);
		void enter(std::string word, std::array<int, 5> res);
		void recalculate();
		std::vector<AugmentedWord> getWordList();
	private:
		void addDisallowed(char letter);
		void addRequired(char letter);
		void addAnti(int pos, char letter);
		void addState(int pos, char letter);

		void filter_disallowed();
		void filter_required();
		void filter_positional();
		void filter_anti();
};

#endif
