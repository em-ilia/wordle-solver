from string import ascii_lowercase
_swap = lambda i: (i[1],i[0])
class _LetterDict:
    def __init__(self):
        self.dict = {}
        self.wordcount = 0
        # Fill dict with blank entries—all letters start with a value of 0
        for x in ascii_lowercase:
            self.dict[x] = 0

    def inc(self, letter):
        """
        Increment the known number of occurrances of letter in the dict.
        As a side effect, the wordcount is increased as well.

        letter -- single character string
        """
        self.wordcount += 1
        self.dict[letter] += 1

    def __str__(self):
        return str(self.dict)
    __repr__ = __str__

    def from_words(words, index):
        """
        Initialize a _LetterDict from a list of words and an index
        This will count the number of times each letter is seen at the given
        index.

        words -- list of strings containing words
        index -- position to check, must be in range [0,4]
        """
        assert (0 <= index < 5)

        ld = _LetterDict()
        for word in words:
            ld.inc(word[index])
        return ld

class _TotalLetterDict(_LetterDict):
    # Non-positional equivalent of _LetterDict
    def from_words(words):
        """
        Count the number of times a letter is seen anywhere in a list of words.

        words -- list of strings containing words
        """
        tld = _TotalLetterDict()
        for word in words:
            for l in word:
                tld.inc(l)
        return tld

class _LetterProbDict:
    def __init__(self, ld):
        """
        Takes a _LetterDict and calculates the probability that a given letter
        will occur at a given position in a word. The position in the word is
        implicitly inherited from the _LetterDict passed to __init__.

        ld -- _LetterDict
        """
        self.dict = {}
        for x in ascii_lowercase:
            self.dict[x] = ld.dict[x]/ld.wordcount
    def __str__(self):
        return str(self.dict)
    __repr__ = __str__

    def max(self):
        """
        Unused.
        Gets the most likely letter from the list.
        """
        #itms = (self.dict.items())
        #s = map(, itms)
        #m = max(_swap)
        #return m
        return _swap(max(map(_swap, self.dict.items())))

    # Returns sorted DESCENDING
    def sorted(self):
        """
        Unused.
        Returns a list of letters in order of their calculated probabilities.
        """
        return list(map(_swap, sorted(map(_swap, self.dict.items()))))[::-1]

class _TotalLetterProbDict(_LetterProbDict):
    """
    Calculates the probability that a letter will occur anywhere in a word.
    Since this calculation is essentially the same, this class can inherit from
    _LetterProbDict with no modification.
    """
    def __init__(self, tld):
        super().__init__(tld)

class WordStats:
    def __init__(self, wl=[]):
        self.wordlist = wl

        self.letterdicts = []
        self.letterprobdicts = []
        self.total_letterdict = None
        self.total_letterprobdict = None

        if self.wordlist:
            self.calculate()

    def calculate(self):
        """
        Utility function to generate all attributes of WordStats instance
        """
        self._calc_letterdicts()
        self._calc_letterprobdicts()
        self._calc_total_letterdict()
        self._calc_total_letterprobdict()

    def _calc_letterdicts(self):
        """
        Uses self.wordlist to generate _LetterDict for each of the five
        possible letter positions.
        """
        for index in range(0,5):
            self.letterdicts.append(
                _LetterDict.from_words(self.wordlist, index))

    def _calc_letterprobdicts(self):
        """
        Generates five _LetterProbDict using self.letterdicts
        This function should always be called after _calc_letterdicts
        """
        for ld in self.letterdicts:
            self.letterprobdicts.append(
                _LetterProbDict(ld))

    def _calc_total_letterdict(self):
        self.total_letterdict = _TotalLetterDict.from_words(self.wordlist)

    def _calc_total_letterprobdict(self):
        self.total_letterprobdict = _TotalLetterProbDict(self.total_letterdict)

    def maximizeWordProb(self, POS_SCALING=0.5, TOTAL_SCALING=0.5):
        return sorted(map(_swap,
                          [(a[0], POS_SCALING*a[1]+TOTAL_SCALING*b[1])
                           for (a,b) in
                           zip(self._maximizeWordProb_positional(),
                               self._maximizeWordProb_total())]
                          ))

    def _maximizeWordProb_positional(self):
        # Wordlist augmented with probability values
        # (word, prob)
        augmented_wl = []

        # Temporary list, cleared once per word
        t_list = []

        # Iterate over all valid words
        for w in self.wordlist:

            # In each word, get each index and character
            for i,l in enumerate(w):
                # Search for the probability of having character l at index i
                # Put in temporary list
                t_list.append(self.letterprobdicts[i].dict[l])
            # Sum the probabilities in t_list
            augmented_wl.append((w, sum(t_list)))
            t_list.clear()
        return sorted(augmented_wl)

    def _maximizeWordProb_total(self):
        f = lambda w: (w,
                       sum([self.total_letterprobdict.dict[l]
                            for l in w]))
        return sorted(map(f, self.wordlist))

if __name__ == '__main__':
    from WORDS import words
    ws = WordStats(words)
