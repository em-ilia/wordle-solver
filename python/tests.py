from WORDS import words
import stats
import unittest

class TestStatsCalculations(unittest.TestCase):

    def setUp(self):
        self.ws = stats.WordStats(words)

    def testLetterDict(self):
        self.assertEqual(self.ws.letterdicts[0].dict['n'], 37)
        self.assertEqual(self.ws.letterdicts[1].dict['q'], 5)
        self.assertEqual(self.ws.letterdicts[2].dict['z'], 11)

    def testLetterProbDictValues(self):
        self.assertEqual(self.ws.letterprobdicts[0].dict['d'],
                         0.04794816414686825)
        self.assertEqual(self.ws.letterprobdicts[1].dict['q'],
                         0.0021598272138228943)
        self.assertEqual(self.ws.letterprobdicts[2].dict['z'],
                         0.004751619870410367)

    def testLetterProbDictSums(self):
        for n, lpd in enumerate(self.ws.letterprobdicts):
            with self.subTest(i=n):
                self.assertTrue(abs(sum(lpd.dict.values())-1) < 2e-15)

    def testTotalLetterDictSum(self):
        self.assertEqual(sum(self.ws.total_letterdict.dict.values())/5,
                         len(self.ws.wordlist))

    def testTotalLetterProbDictSums(self):
        self.assertTrue(abs(sum(self.ws.total_letterprobdict.dict.values())-1)
                        < 2e-15)

    # Just to track if the algorithm changes even with constant scaling
    def testMWP_consistency(self):
        self.assertEqual(self.ws.
                         maximizeWordProb(POS_SCALING=0.5,
                                          TOTAL_SCALING=0.5)[-1][1], 'slate')

if __name__ == '__main__':
    unittest.main()
