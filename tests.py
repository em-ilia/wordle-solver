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
                self.assertTrue(sum(lpd.dict.values())-1 < 2e-15)

if __name__ == '__main__':
    unittest.main()
