#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "WordStats.hpp"
#include <string>
#include <vector>
#include <array>
#include <map>
#include <set>

class GameState{
	private:
		std::vector<AugmentedWord> initialList;

		std::string state;
		std::set<std::string> disallowed;
		std::set<std::string> required;
		std::map<std::string, std::set<int>> anti;
	public:
		GameState(std::vector<AugmentedWord> initialList);
		void enter(std::string word, std::array<int, 5> res);
		void recalculate();
	private:
		void addDisallowed(std::string letters);
		void addRequired(std::string letters);
		void addAnti(int pos, char letter);
		void addState(int pos, char letter);

		void filter_disallowed();
		void filter_required();
		void filter_positional();
		void filter_anti();
};

#endif
