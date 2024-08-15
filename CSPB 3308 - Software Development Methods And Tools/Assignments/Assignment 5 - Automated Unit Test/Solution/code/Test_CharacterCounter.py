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

        self.assertIsInstance(p.text, str, "Input is not a string.")

        # Non-string input (integer)
        with self.assertRaises(CharacterCounterError):
            CharacterCounter(123)

        # Non-string input (float)
        with self.assertRaises(CharacterCounterError):
            CharacterCounter(3.141592654)

        # Array input
        with self.assertRaises(CharacterCounterError):
            CharacterCounter([])  

        # None input
        with self.assertRaises(CharacterCounterError):
            CharacterCounter(None)  

    # Add Your Test Cases Here...

    def test_count(self):
        tests = [
            ("", 0, "Empty string, should have length 0"),
            ("a", 1, "Single character 'a', should have length 1"),
            ("abc", 3, "Three characters 'abc', should have length 3"),
            ("ABC", 3, "Three characters 'ABC', should have length 3"),
            ("Hello, World!", 13, "Thirteen characters 'Hello, World!', should have length 13"),
            ("!@#$%^&*()_+", 12, "Twelve characters '!@#$%^&*()_+', should have length 12"),
            ("Multiple white space count", 26, "Twenty six characters 'Multiple white space count', should have length 26"),
            ("123!@#{}\"'", 10, "Ten characters '123!@#{}\"'', should have length 10"),
            ("><.,? ?,.><", 11, "Eleven characters '><.,? ?,.><', should have length 11"),
            ("     ", 5, "Five characters '     ', should have length 5")
        ]
        for test in tests:
            my_obj = CharacterCounter(test[0])
            self.assertEqual(my_obj.count(), test[1], test[2])

    def test_alpha(self):
        tests = [
            ("", 0, "Empty string, no alpha characters present, '' should have length 0"),
            ("a", 1, "Single string, one alpha character present, 'a' should have length 1"),
            ("A", 1, "Single uppercase string, one alpha character present, 'A' should have length 1"),
            ("HeLlO wOrLd", 10, "10 uppercase and lower case characters, 10 alpha characters present, 'HeLlO wOrLd' one white space ignored, should have length 10"),
            ("m!X 0f cH@rAc+eR$", 10, "10 alpha characters present, mix of types of characters, should have length 10"),
            ("1234567890", 0, "Zero alpha characters present, all numeric characters, '1234567890' should have length 0"),
            ("MULTIPLE WHITE SPACES PRESENT", 26, "26 alpha characters present, three white spaces ignored, 'MULTIPLE WHITE SPACES PRESENT' should have length 26"),
            ("     leading", 7, "Seven alpha characters present, five white spaces ignored, '     leading' should have length 7"),
            ("TRAILING   ", 8, "Eight alpha characters present, three white spaces ignored, 'TRAILING   ' should have length 8"),
            (" l3Ad!nG @^D +Ra!lInG ", 12, "Twelve alpha characters present, four white spaces ignored, ' l3Ad!nG @^D +Ra!lInG '")
        ]
        for test in tests:
            my_obj = CharacterCounter(test[0])
            self.assertEqual(my_obj.count_alpha(), test[1], test[2])

    def test_numeric(self):
        tests = [
            ("", 0, "Empty string, no numeric characters present, '' should have length 0"),
            ("0", 1, "Single string, one numeric character present, '0' should have length 1"),
            ("!23", 2, "Three character string, two numeric characters present, '!23' should have length 2"),
            ("12345, World!", 5, "Thirteen character string, 5 numeric characters present, '12345, World!' should have length 5"),
            ("None", 0, "Four character string, 0 numeric characters present, 'None' should have length 0"),
            ("1,234,567,890", 10, "Eleven character string, 10 numeric characters present, '1,234,567,890' should have length 10"),
            ("2w0 and 3hr33", 5, "Thirteen character string, 5 numeric characters present, '2w0 and 3hr33' should have length 5"),
            ("3.141592654", 10, "Eleven character string, 10 numeric characters present, '3.141592654' should have length 10"),
            ("Thr33", 2, "Five character string, 2 numeric characters present, 'Thr33' should have length 2"),
            (" 40rty 51v3 ", 5, "Twelve character string, 5 numeric characters present, ' 40rty 51v3 ' should have length 5")
        ]
        for test in tests:
            my_obj = CharacterCounter(test[0])
            self.assertEqual(my_obj.count_numeric(), test[1], test[2])

    def test_vowels(self):
        tests = [
            ("", 0, "Empty string, no vowels present, '' should have length 0"),
            ("A", 1, "Single character string, one vowel present, 'A' should have length 1"),
            ("aeiou AEIOU", 10, "Eleven character string, 10 vowels present, 'aeiou AEIOU' should have length 10"),
            ("Hello, World!", 3, "Thirteen character string, 3 vowels present, 'Hello, World!' should have length 3"),
            ("Lndy", 0, "Four character string, 0 vowels present, 'Lndy' should have length 0"),
            ("12e45     ", 1, "Ten character string, 1 vowel present, '12e45     ' should have length 1"),
            ("The quick brown fox jumps over the lazy dog.", 11, "35 character string, 11 vowels present, 'The quick brown fox jumps over the lazy dog.' should have length 11"),
            ("Ko0l A!D!", 2, "Nine character string, 2 vowels present, 'Ko0l A!D!' should have length 2"),
            ("Tw3nti fou4", 3, "Eleven character string, 3 vowels present, 'Tw3nti fou4' should have length 3"),
            ("   U^n!t t3$+s a4e n3At!!!   ", 4, "35 character string, 4 vowels present, '   U^n!t t3$+s a4e n3At!!!   ' should have length 2")
        ]
        for test in tests:
            my_obj = CharacterCounter(test[0])
            self.assertEqual(my_obj.count_vowels(), test[1], test[2])

    def test_phone_num(self):
        tests = [
            ("", False, "Empty string, not a valid phone number, '' should return False"),
            ("023-456-7890", False, "Invalid phone number due leading 0 in area code, not a valid phone number, '023-456-7890' should return False"),
            ("123-456-7890", False, "Invalid phone number due leading 1 in area code, not a valid phone number, '123-456-7890' should return False"),
            ("223-456-7890", True, "Valid phone number, '223-456-7890' should return True"),
            ("(223)-(456)-(7890)", False, "Invalid phone number due to parenthesis, '(223)-(456)-(7890)' should return False"),
            ("291-222-3333", False, "Invalid phone number due to middle digit in area code as 9, '191-222-3333' should return False"),
            ("234-056-7890", False, "Invalid phone number due to first digit in central office being a 0, '234-156-7890' should return False"),
            ("234-156-7890", False, "Invalid phone number due to first digit in central office being a 1, '234-156-7890' should return False"),
            ("21-345-5678", False, "Invalid phone number due to area code format, '2-34-567' should return False"),
            ("234-34-5678", False, "Invalid phone number due to central office format, '234-34-5678' should return False"),
            ("223-456-789", False, "Invalid phone number due to line number format, '223-456-789' should return False"),
            ("800-867-5309", True, "867-5309 is ALWAYS a valid phone number :), should return True")
        ]
        for test in tests:
            my_obj = CharacterCounter(test[0])
            self.assertEqual(my_obj.is_phonenumber(), test[1], test[2])
            
    # add methods for other functions that need to be tested ...
            
# Main: Run Test Cases
if __name__ == '__main__':
    unittest.main()
