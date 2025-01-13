import unittest
from ToRomanNumber import ToRomanNumber

class TestMathFunctions(unittest.TestCase):

    def test_add(self):
        self.assertEqual(ToRomanNumber(1), "I")
        self.assertEqual(ToRomanNumber(22), "XXII")
        self.assertEqual(ToRomanNumber(50), "L")
        self.assertEqual(ToRomanNumber(1994), "MCMXCIV")

suite = unittest.TestLoader().loadTestsFromTestCase(TestMathFunctions)
runner = unittest.TextTestRunner()
runner.run(suite)

"""
----------------------------------------------------------------------
Ran 1 test in 0.000s

OK
test_add (main.TestMathFunctions.test_add) ... ok

----------------------------------------------------------------------
Ran 1 test in 0.000s

OK
"""