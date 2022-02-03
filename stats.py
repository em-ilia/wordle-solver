from string import ascii_lowercase
_swap = lambda i: (i[1],i[0])
class _LetterDict:
    def __init__(self):
        self.dict = {}
        self.wordcount = 0
        for x in ascii_lowercase:
            self.dict[x] = 0

    def inc(self, letter):
        self.wordcount += 1
        self.dict[letter] += 1

    def __str__(self):
        return str(self.dict)
    __repr__ = __str__

    def from_words(words, index):
        assert (0 <= index < 5)

        ld = _LetterDict()
        for word in words:
            ld.inc(word[index])
        return ld

class _TotalLetterDict(_LetterDict):
    def from_words(words):
        tld = _TotalLetterDict()
        for word in words:
            for l in word:
                tld.inc(l)
        return tld

class _LetterProbDict:
    def __init__(self, ld):
        self.dict = {}
        for x in ascii_lowercase:
            self.dict[x] = ld.dict[x]/ld.wordcount
    def __str__(self):
        return str(self.dict)
    __repr__ = __str__

    def max(self):
        #itms = (self.dict.items())
        #s = map(, itms)
        #m = max(_swap)
        #return m
        return _swap(max(map(_swap, self.dict.items())))

    # Returns sorted DESCENDING
    def sorted(self):
        return list(map(_swap, sorted(map(_swap, self.dict.items()))))[::-1]

class WordStats:
    def __init__(self, wl=[]):
        self.wordlist = wl

        self.letterdicts = []
        self.letterprobdicts = []
        self.total_letterdict = None

        if self.wordlist:
            self.calculate()

    def calculate(self):
        self._calc_letterdicts()
        self._calc_letterprobdicts()
        self._calc_total_letterdict()

    def _calc_letterdicts(self):
        for index in range(0,5):
            self.letterdicts.append(
                _LetterDict.from_words(self.wordlist, index))

    def _calc_letterprobdicts(self):
        for ld in self.letterdicts:
            self.letterprobdicts.append(
                _LetterProbDict(ld))

    def _calc_total_letterdict(self):
        self.total_letterdict = _TotalLetterDict.from_words(self.wordlist)

    def maximizeWordProb(self):
        augmented_wl = []
        t_list = []
        for w in self.wordlist:
            for i,l in enumerate(w):
                t_list.append(self.letterprobdicts[i].dict[l])
            augmented_wl.append((w, sum(t_list)))
            t_list.clear()
        return sorted(map(_swap, augmented_wl))
