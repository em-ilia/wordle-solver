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
class GameManager():
    def __init__(self, parameters, *, count=0):
        self.count = count if count else len(words)
        self.parameters = parameters
        #(self.POS, self.TOTAL) = parameters

        #self.games = [GameInstance(w, parameters) for w in words[0:count]]
        self.games = []
        for w in words[0:count]:
            self.games.append(GameInstance(w, self.parameters))

        self.complete = False

    def run(self):
        for game in self.games:
            game.run()
        self.complete = True

    def compute_avgAttempts(self):
        assert self.complete
        return sum([g.attempts for g in self.games]) / self.count
