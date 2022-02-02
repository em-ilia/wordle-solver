import json
from string import ascii_lowercase

swap = lambda i: (i[1],i[0])
class LetterDict:
    def __init__(self):
        self.dict = {}
        for x in ascii_lowercase:
            self.dict[x] = 0

    def inc(self, letter):
        self.dict[letter] += 1

    def __str__(self):
        return str(self.dict)
    __repr__ = __str__

class LetterProbDict:
    def __init__(self, ld, wordcount):
        self.dict = {}
        for x in ascii_lowercase:
            self.dict[x] = ld.dict[x]/wordcount
    def __str__(self):
        return str(self.dict)
    __repr__ = __str__

    def max(self):
        #itms = (self.dict.items())
        #s = map(, itms)
        #m = max(swap)
        #return m
        return swap(max(map(swap, self.dict.items())))

    # Returns sorted DESCENDING
    def sorted(self):
        return list(map(swap, sorted(map(swap, self.dict.items()))))[::-1]

def maximizeWordProb(lpds, wl):
    augmented_wl = []
    t_list = []
    for w in wl:
        for i,l in enumerate(w):
            t_list.append(lpds[i].dict[l])
        augmented_wl.append((w, sum(t_list)))
        t_list.clear()
    return sorted(map(swap, augmented_wl))

class GameState:
    def __init__(self, initialList, *, state='?????',
                 disallowed='', required='',
                 print_on_recalc=False,
                 num_to_print=10,
                 recalc_on_enter=False):
        self.state = state
        self.list = initialList
        self.disallowed = disallowed
        self.required = required
        self.anti = {}

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

        if self.recalc_on_enter:
            self.recalculate()

    def addDisallowed(self, letters=''):
        if not letters: pass # Minor optimization, should not happen
        self.disallowed = ''.join(set(self.disallowed + letters))

    def addRequired(self, letters=''):
        if not letters: pass # Minor optimization, should not happen
        self.required = ''.join(set(self.required + letters))

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

lds = []
lpds = []
for i in range(0,5):
    ld = LetterDict()
    for word in words:
        ld.inc(word[i])
    lds.append(ld)
    lpds.append(LetterProbDict(ld, len(words)))

ldsj = json.dumps(lds, default=vars, indent=2)
with open('ld.json', 'w') as f:
    f.write(ldsj)
lpdsj = json.dumps(lpds, default=vars, indent=2)
with open('lpd.json', 'w') as f:
    f.write(lpdsj)

G = GameState(maximizeWordProb(lpds, words),
              print_on_recalc=True,
              recalc_on_enter=True)
