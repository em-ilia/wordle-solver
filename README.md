# Wordle Solver
## About
I hate using my own brain to think, that's why I'm going to spend hours thinking about how to make my computer do this for me.

## Status
I've currently only implemented very terrible word ranking—currently words are evaluated solely based on the sum of individual relative letter position probabilities
(i.e. how likely it is that a particular letter is at a given spot in the word).
I suspect that a better method would also evaluate the sum of total letter frequencies in a word (i.e. favoring words that use a lot of common letters instead of those that contain `z`)
and then finding an ideal weight for these two metrics. This of course assumes that Wordle words are not chosen based on their usage frequency.

Currently, the word ranking is only slightly helpful: when I play using the tool, I show the ten most highly ranked words and that seems to be enough to solve the puzzle in an average of four attempts.
I am mentally ruling out uncommon words when I play this way (which is antithetical to the goal of not thinking), but I have yet to play this way on the actual Wordle wordlist.
Instead, I've done my testing so far using [this version of the game](https://octokatherine.github.io/word-master/), which uses a much larger wordlist (seemingly closer to the full list of acceptable Wordle words than that from which solutions are drawn).

---
## TODO:
* Improve word ranking? Can it be done?
* Update README status section
* ✨User Experience✨
	* Manually calling `.enter()` is unpleasant
