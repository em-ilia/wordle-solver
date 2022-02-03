from solve import GameState
from stats import WordStats
from WORDS import words

class GameInstance():
    def __init__(self, word, parameters):
        self.word = word
        (self.POS, self.TOTAL) = parameters
        self.game = GameState(WordStats(words)
                              .maximizeWordProb(self.POS, self.TOTAL),
                              recalc_on_enter=True)
        self.status = 0
        self.attempts = 1

    def cycle(self):
        if not self.game.list:
            self.status = -1
        attempt = self.game.list[-1][1]
        if attempt == self.word:
            self.status = 1
        else:
            self.attempts += 1
            res = []
            for i, l in enumerate(attempt):
                if self.word[i] == l:
                    res.append(2)
                elif l in self.word:
                    res.append(1)
                else:
                    res.append(0)
            self.game.enter(attempt, res)

    def run(self):
        while not self.status:
            if self.attempts > 10: break
            self.cycle()
