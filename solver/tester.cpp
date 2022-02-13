#include "GameState.hpp"
#include "WordStats.hpp"
#include "WORDS.hpp"
#include <iostream>

int main() {
	WordStats ws = WordStats(WORDS);
	GameState game = GameState(ws.maximizeWordProb());
	auto best = formatAugmentedWord(game.getWordList().back());
	std::cout << best << "\n";

	game.enter("slate", {0,2,1,1,0});
	game.recalculate();
	best = formatAugmentedWord(game.getWordList().back());
	std::cout << std::to_string(game.getWordList().size()) << "\n";
	std::cout << best << "\n";
}
