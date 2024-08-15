# -*- coding: utf-8 -*-

# Andy Sayler, David Knox
# Summer 2014, Summer 2022
# CSPB 3308
# University of Colorado
# Character Counting Module

"""
A module defining a simple Character Counter Object with several capabilities.
The class object will be given a string when constructed which will be stored 
in the object. All operations will use that stored string as source for the 
processing.  The various methods will count the number of characters in the 
source string that match specific criteria.
"""

# Imports
# The solutions for the operations can use the regular expreassion library 
import re

###############################################################################
# Exceptions
#    When there are errors in the processing, the operation will raise a 
#    specific type of exception that is define below.  When testing the 
#    solutions, you will want to force the Text Processing Object to raise
#    exceptions.  You can catch these exceptions in your tests.

class CharacterCounterError(Exception):
    """
    Base Class for CharacterCounter Exceptions

    """

    def __init__(self, msg):
        """
        CharacterCounterError Constructor

        :param msg: error message
        :return: CharacterCounterError instance
        """

        super().__init__(msg)

        
###############################################################################
# Public Classes
#   The CharacterCounter class will begiven a string during creation
#   and allow different types of characters to be counted.

class CharacterCounter:
    """
    Class for counting the number of occurrences in strings

    Attributes
    ----------
        text : str       - string on which all methods will operate
            
    Methods
    -------
        count()          - Count number of characters in text
        count_alpha()    - Count number of alphabetic characters in text
        count_numeric()  - Count number of numeric characters in text
        count_vowels()   - Count number of vowels in text
        is_phonenumber() - Check if text is a valid US phone number

    """

    ###############################################################################
    # Constructor
    #   The constructor for instances of this class require a string parameter.
    #   A typical creation of an instance of this class would look like:
    #         my_obj = CharacterCounter("some string")
    #   Notice that the creation only passes one parameter.  The `self` parameter
    #   is used to reference the object being constructed.  It is automaticly
    #   added as a parameter when Python knows it is creating an object.
    #   All the class methods (functions) will always have the `self` as the 
    #   first parameter.
    #
    def __init__(self, given_text):
        """
        CharacterCounter Constructor
        param: given_text: string to copy into instance
        return: CharacterCounter instance
        """

        # We check the type of the parameter to make sure it is a string
        # If it is not a string parameter, an exception is raised
        if type(given_text) is not str:
            raise CharacterCounterError("CharacterCounter requires string parameters")

        # Create a class member for the instance called `text` and initialize 
        # it to the `given_text` string.  
        self.text = given_text

    ###############################################################################
    # The __len__ function is a built-in function for Python. When a variable is
    # passed to the `len(a)` function, then the objects `__len__` function is called,
    # `a.__len__()` will return the length of the string stored in the object.
    #
    def __len__(self):
        """
        Length of string being stored in the object
        return: Length
        """
        # Information was stored in the class data variable.  We can access the 
        # the class data members by using the `self` reference to the current object.
        return len(self.text)

    ###############################################################################
    # The `count()`function will return the number of characters in the string.
    # Typical usage would be:
    #         my_obj = CharacterCounter("some string")
    #         printf("Count =", my_obj.count())
    # The given implmentation just calls the built-in function described above.
    #
    def count(self):
        """
        Count number of characters in text
        return: Length
        """

        return len(self)

    ###############################################################################
    # The `count_alpha()`function will return the number of characters in the string
    # that are alphabetic.
    # Typical usage would be:
    #         my_obj = CharacterCounter("some string")
    #         printf("Count Alpha =", my_obj.count_alpha())
    # The given solution uses the Regular Expression Library to search the data
    # for the specified pattern.
    #
    def count_alpha(self):
        """
        Count number of alphabetic characters in text
        return: Number of alphabetic characters
        """

        alpha = re.compile(r'[a-z]')
        return len(alpha.findall(self.text))

    ###############################################################################
    # The `count_numeric()`function will return the number of characters in the string
    # that are numeric.
    # Typical usage would be:
    #         my_obj = CharacterCounter("some string")
    #         printf("Count Numeric =", my_obj.count_numeric())
    # The given solution uses the Regular Expression Library to search the data
    # for the specified pattern.
    #
    def count_numeric(self):
        """
        Count number of numeric characters in text
        return: Number of numeric characters
        """

        numeric = re.compile(r'[1-9]')
        return len(numeric.findall(self.text))

    ###############################################################################
    # The `count_vowels()`function will return the number of characters in the string
    # that are vowels (we do not consider the character `y` to be a vowel).
    # Typical usage would be:
    #         my_obj = CharacterCounter("some string")
    #         printf("Count Vowels =", my_obj.count_vowels())
    # The given solution uses the Regular Expression Library to search the data
    # for the specified pattern.
    #
    def count_vowels(self):
        """
        Count number of vowels in text
        return: Number of vowels
        """

        vowels = re.compile(r'[aeou]', re.IGNORECASE)
        return len(vowels.findall(self.text))

    ###############################################################################
    # The `is_phonenumber()`function will return TRUE if the characters in the string
    # that represent a valid phone number.
    # Typical usage would be:
    #         my_obj = CharacterCounter("some string")
    #         printf("Is a phone number =", my_obj.is_phonenumber())
    # The given solution uses the Regular Expression Library to search the data
    # for the specified pattern.
    #
    # For this assignment, follow the following rules for phone number:
    #   * the only format allowed is ###-###-####
    #           <area_code> - <central_office_code> - <line_number>
    #   * <area_code> and <central_office_code> cannot have first digit as 0 or 1 
    #   * <area_code> cannot have middle digit as 9 
    #
    def is_phonenumber(self):
        """
        Check if text is a valid US phone number
        return: True or False
        """

        phonenum = re.compile(r'^[1-9]{3}([\-.])*[1-9]{3}\1*[1-9]{3}$')
        if phonenum.match(self.text) is None:
            return False
        else:
            return True
    ###############################################################################
    ###############################################################################


###############################################################################
#   This code will only run when running this file, 
#   but NOT when it is imported by another python script
#
#   The code will extract the docstrings from the python code
#   for the class and each of the methods.
#
#   In real support modules the developer would place you their own
#   testing code here that is independent of the automated unit tests.
if (__name__ == '__main__') :

    def print_docstrings(object_class):
        object_methods = [method_name for method_name in dir(object_class)
                              if (callable(getattr(object_class, method_name))) 
                                  and ( method_name[:2] != "__")]
        print ("Methods:", object_methods)

        for method_name in object_methods:
            print (80*"-")
            print ("Method:", method_name)
            print ((len(method_name)+8)*"-")
            print (getattr(object_class, method_name).__doc__)
            print()
 
    print (80*"-")
    print ("CharacterCounter:", CharacterCounter.__doc__)
    print (80*"-")
    print ()
    
    print_docstrings(CharacterCounter)
    print (80*"-")

    # would place tests here
    print ("Author tests running...")
    test_phrase = "testing 123."
    my_obj = CharacterCounter(test_phrase)
    assert my_obj.count() == len(test_phrase), "count() should be %d"%(len("testing 123."))
    assert my_obj.count_alpha() == 7, "count_alpha() should be 7"
    assert my_obj.count_numeric() == 3, "count_alpha() should be 3"
    
    try:
        my_bad_obj = CharacterCounter(100)
    except:
        # Expected it to raise an exception
        # print ("caught bad parameter passed") 
        pass
    else:
        print ("FAILED to raise exception on bad parameter!")
        
    print ("Author tests completed.")
    