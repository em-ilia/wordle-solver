
_swap = lambda i: (i[1],i[0])
class LetterDict:
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

        ld = LetterDict()
        for word in words:
            ld.inc(word[index])
        return ld

class LetterProbDict:
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

def maximizeWordProb(lpds, wl):
    augmented_wl = []
    t_list = []
    for w in wl:
        for i,l in enumerate(w):
            t_list.append(lpds[i].dict[l])
        augmented_wl.append((w, sum(t_list)))
        t_list.clear()
    return sorted(map(_swap, augmented_wl))
