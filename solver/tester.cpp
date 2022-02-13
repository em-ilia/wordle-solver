#include "GameState.hpp"
#include "WordStats.hpp"
#include "WORDS.hpp"
#include <iostream>

void printFive(std::vector<AugmentedWord> wl) {
	/*
	for (auto i = wl.end() - 5; i != wl.end(); i++) {
		std::cout << formatAugmentedWord(*i) << " ";
	}
	*/
	std::cout << std::to_string(wl.size());
	if (wl.size() == 0) return;
	std::cout << formatAugmentedWord(wl.back()) << "\n";
	std:: cout << "\n";
}

int main() {
	WordStats ws = WordStats(WORDS);
	GameState game = GameState(ws.maximizeWordProb());
	std::cout << "\n";
	std::cout << "TEST CASE 2:\n";

	game = GameState(ws.maximizeWordProb());
	printFive(game.getWordList());

	game.enter("slate", {0,0,2,0,2});
	game.recalculate();
	printFive(game.getWordList());

	game.enter("crane", {0,0,2,0,2});
	game.recalculate();
	printFive(game.getWordList());

	game.enter("weave", {1,0,2,0,2});
	game.recalculate();
	printFive(game.getWordList());

	return 0;
}
