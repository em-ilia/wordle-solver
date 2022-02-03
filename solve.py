from stats import WordStats
from WORDS import words

class GameState:
    def __init__(self, initialList, *, state='?????',
                 disallowed=set(), required=set(),
                 print_on_recalc=False,
                 num_to_print=10,
                 recalc_on_enter=False):
        self.state = state
        self.ws = wordstats
        self.disallowed = disallowed
        self.required = required
        self.anti = {}

        self.list = ws.maximizeWordProb()

        #Options
        self.print_on_recalc = print_on_recalc
        self.num_to_print = num_to_print
        self.recalc_on_enter = recalc_on_enter

    def setState(self, state, sideEffect=False):
        if not len(state) == 5: pass

        self.state = state
        if sideEffect: self.recalculate()

    # res = 0 if gray, 1 if yellow, 2 if green
    def enter(self, letters, res, /,):
        # Inefficient way to do this, pls change:
        # Iterate over a range
        # Build a list of actions to minimize func calls
        # (essentially trade space for time)
        z = zip(letters, res)
        for i,(l,r) in enumerate(z):
            if   r == 0:
                self.addDisallowed(l)
            elif r == 1:
                self.addRequired(l)
                self.addAnti(i,l)
            elif r == 2:
                self.addState(i,l)
                self.addRequired(l)
        self.disallowed.difference_update(self.required)

        if self.recalc_on_enter:
            self.recalculate()

    def addDisallowed(self, letters=''):
        if not letters: pass # Minor optimization, should not happen
        self.disallowed.update(letters)

    def addRequired(self, letters=''):
        if not letters: pass # Minor optimization, should not happen
        self.required.update(letters)

    def addAnti(self, pos, letter):
        if not 0 <= pos <= 4: pass
        if not (l := self.anti.get(letter)):
            self.anti[letter] = {pos}
        else:
            l.add(pos)

    def addState(self, pos, letter):
        if not 0 <= pos <= 4: pass
        self.state = self.state[0:pos] + letter + self.state[pos+1:]

    def recalculate(self):
        self._f_disallowed()
        self._f_required()
        self._f_positional()
        self._f_anti()

        if self.list:
            self.ws.update([x[1] for x in self.list])
            self.list = ws.maximizeWordProb()

        if self.print_on_recalc:
            print(self.list[-(self.num_to_print):])

    def _f_disallowed(self, *, disallowed=''):
        if disallowed:
            self.addDisallowed(disallowed)
        self.list = list(filter(
            lambda y: not any([x in y[1] for x in self.disallowed]),
            self.list))

    def _f_required(self, *, required=''):
        if required:
            self.addRequired(required)
        self.list = list(filter(
            lambda y: all([x in y[1] for x in self.required]),
            self.list
        ))

    def _f_positional(self, *, state=''):
        if state:
            self.setState(state)
        # Filtering for known positions
        self.list = list(filter(
            lambda y: all([x == '?' or x == y[1][n]
                           for n,x in enumerate(self.state)]),
            self.list
        ))

    def _f_anti(self, *, anti={}):
        if anti:
            pass
        self.list = list(filter(
            lambda y: not any([n in self.anti.get(x, {})
                               for n,x in enumerate(y[1]) ]),
            self.list
        ))

if __name__ == '__main__':
    ws = WordStats(words)
    G = GameState(ws,
                  print_on_recalc=True,
                  recalc_on_enter=True)
    G.enter('slate', [1,0,0,1,2])
