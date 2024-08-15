#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Andy Sayler, David Knox
# Summer 2014, 2022
# CSCI 3308
# Univerity of Colorado
# Tests for Character Counting Module

import unittest
from CharacterCounter import *

class CharCounterTestCase(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        pass

    @classmethod
    def tearDownClass(cls):
        pass

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_init(self):
        text = "tesing123"
        
        # create an object that we will use in this testing
        p = CharacterCounter(text)
        
        # use the testing framework assertions to check results
        self.assertEqual(p.text, text, "'text' does not match input")
        
        # need to test that an exception is raised when given a bad parameter!
        # any other tests?

    # Add Your Test Cases Here...
    
    # here is an example way to write tests.  You can do it other ways as well.
    # THIS IS NOT A GOOD SET OF TESTS, JUST AN EXAMPLE
    #
    def test_alpha(self):
        # each element of the tests list is also a list which has [test string, expected value, message]
        tests = [
            ["aaaa",       4, "did not find all occurrences of single char"],
            ["a        b", 2, "did not find first and last character of string"],
            ["az",         2, "did not detect a and/or z"],
            ["(a1)",       1, "did not detect handle string with alpha, digit, paren" ],
            ["1239093",    0, "found alpha in digits only string"]
        ]
        
        for test in tests:
            # create a new object for each test
            my_obj = CharacterCounter(test[0])
            
            # check that the results are as expected
            self.assertEqual(my_obj.count_alpha(), test[1], test[2])
            
    # add methods for other functions that need to be tested ...
            
# Main: Run Test Cases
if __name__ == '__main__':
    unittest.main()
