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
	if (wl.size() == 0) return;
	std::cout << formatAugmentedWord(wl.back());
	std:: cout << "\n";
}

int main() {
	std::cout << "TEST CASE 1:\n";
	WordStats ws = WordStats(WORDS);
	GameState game = GameState(ws.maximizeWordProb());
	printFive(game.getWordList());

	game.enter("slate", {0,0,0,0,0});
	game.recalculate();
	printFive(game.getWordList());

	game.enter("crony", {0,0,0,0,0});
	game.recalculate();
	printFive(game.getWordList());

	game.enter("humid", {2,2,2,0,0});
	game.recalculate();
	printFive(game.getWordList());

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

	std::cout << "\n";
	std::cout << "TEST CASE 3:\n";

	game = GameState(ws.maximizeWordProb());
	printFive(game.getWordList());

	game.enter("slate", {1,2,0,0,0});
	game.recalculate();
	printFive(game.getWordList());

	std::cout << "\n";
	std::cout << "TEST CASE 4:\n";

	game = GameState(ws.maximizeWordProb());
	printFive(game.getWordList());

	game.enter("slate", {0,1,1,0,0});
	game.recalculate();
	printFive(game.getWordList());

	game.enter("gaily", {0,1,0,1,0});
	game.recalculate();
	printFive(game.getWordList());

	game.enter("coral", {1,2,0,2,2});
	game.recalculate();
	printFive(game.getWordList());

}
