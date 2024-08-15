# CSPB-3308  Lab 5 :  Automated Unit Testing
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right">
</figure>
<hr>


### I know that some of you have struggled to use the testing framework.

Here I will try to explain a little bit about how the testing works and how to use the `assert` statements to test a method.

<hr>
    
### Python Class and Object Oriented Design
The first thing to understand is that we are testing an object called `Processor` that is defined in the `testproc.py` python file.  The object is a **class** that defines the constructor, the object's data, and the methods that can perform actions on the object's data.

In our lab, the object is a text processing object.  It is given a text string when it is created,  which it stores for later use.  When you define a method in Python, you always use the keyword `self` to indicate the object that the method is being applied to.  If additional parameters are required in the method, they are listed after the `self` parameter.

Methods with `__somename__` format are built in Python functions that can be specified for a class.  The `__init__` function defines the constructor for the class objects and the `__len__` is the method that is called when using `len(obj)` where the `obj` is a `Processor` object.  The `self` is an *implicit* parameter, meaning you do not specify it in the call.  When we have constructed a `Processor` object and want to call the `count` method, we just use the `.` notation.  `p.count()` will call the `count()` method and implicitly place the `p` object as the first parameter.   

In our lab there are a number of methods being defined:
*  __init__(self, text): the constructor that takes a single additional parameter 
* __len__(self): determine the number of characters in the string.  
*  count(self): Count number of characters in text
* count_alpha(self): Count number of alphabetic characters in text
* count_numeric(self): Count number of numeric characters in text
* count_vowels(self): Count number of vowels in text

You will notice that none of the methods besides the constructor take additional parameters.  This is because the methods are designed to use the string stored in the object.  That string was passed in  when the object was created.  You see an example of the `Processor` object's use in the `testproc_test.py` file.

```
1   import testproc 
2
3   def test_init(self):
4        text = "tesing123"
5        p = testproc.Processor(text)
6        self.assertEqual(p.text, text, "'text' does not match input")
```
The test function is creating an object and passing a string to the constructor in line 5.   We included the `testproc` module in line 1.  This loads the `testproc.py` file into an object called `testproc`.   The reason you need `testproc.Processor` is that we need to tell Python that we want an object of class `Processor` that is defined in the module `textproc`.  The module is just like any other object and you can access its methods and classes by listing the module name and the method to access.  

Line 5 is creating a new `Processor` object that we store in the variable named `p`.  Then we can use that new object in line 6 to call verify that the text stored in the object is the same as the text in the constructor.

We have split out the static text, the call to the constructor (lines 4 and 5).  We could have just as easily combined the lines and created the new object with :
```
5        p = testproc.Processor("testing123")
```
The constructor just wants a string to be passed in as a parameter.  Notice that we would need to enter the static string again in the testing on line 6.  By placing the text in a variable we eliminate the chance of a typo in one of the strings.

<hr>
    
### Assert Statements

The `assert` is a mechanism found in most languages that will stop the execution of the program if the assertion is not correct.   In this case, the assertion being used is `assertEqual`, which will compare two values to see if they are equal.  In line 6 we are comparing the text that we used in the constructor to the text stored in the object (p.text) to see if they are the same string.

An assert statement will never return if the two values are not the same.  The program will only continue if the assertion is TRUE.   That means you can have a series of assert statements and as soon as one of them finds the assertion to be FALSE, none of the code following that assertion will be performed.

There are a number of different assertion statements available.  You can check that a value is equal, not equal, less, greater, ... or that the value is True or that the value is False.   There are also assertions that specify that a call will cause an exception to be raised.  Exceptions can be things like divide by zero, accessing invalid memory, or opening a non existent file.  You can also write your Python code to explicitly raise a user defined exception.  There are lots of exceptions and the `try: except: ` construct is used to capture these in normal Python code.  

When writing the unit tests, we may want to test that an exception will occur.  In our case, there is a specification that the constructor will raise an exception when the parameter for the text is not a string value.   This means that if the constructor is given an integer value, the constructor must cause an exception to occur.   Our testing needs to capture that exception.  We could place a `try: except:` to catch the exception or we can use the `assertException` statement.  This statement will capture the exception raised when we pass an integer to the constructor.  The following code will catch the exception that the constructor is supposed to raise when passing the 123 integer value.  If the exception DOES NOT occur within the body of the statement, then the assert will judge the assertion to be false, stop the processing, and fail the test.

```
        with self.assertRaises(Exception):
            p = textproc.Processor(123)
```

Your code will create individual tests for each of the functions in the class being tested.  Each of the individual tests will have multiple test cases that make sure the function is behaving correctly in all circumstances.  The `assert` statements are used to verify that a function is behaving correctly.  If any of the test cases does not behave as specified, the `assert` will fail and the test will fail. 
<hr>

### Testing Framework

Now that we have briefly explained how a Python class is used, lets discuss how the testing environment is used to test our class methods.

In a large project we may have many unit tests.  Each unit test will  test a single "unit" of code.  Usually a set of related functions or a class.  Each unit test is usually named the same as the unit it is testing with a `test_` prefix or a `_test` suffix added.  In our lab ample, the testing code is placed in `textproc_test.py` file to test the code in the `textproc.py` file.

The testing environment is also a Class that is defined in the `unittest` module.  It has a number of defined methods to initialize  and setup the testing environment.  It also has a number of defined methods for cleaning up after the test is complete.  These are the `setup` and `teardown` methods.  The `setUpClass` and `tearDownClass` methods are only called once when the class is defined.  The `setUp` and `tearDown` methods are called for each test that is performed in the unit testing.

Because we do not need to create a database or temporary files for testing this class object, we do not need any setup or teardown code.

The code at the end of the unit test:
```
# Main: Run Test Cases
if __name__ == '__main__':
    unittest.main()
```
This code tests to see if the file is being run or just loaded into another file (using import).   If this Python file is being run then the Python system variable `__name__` will be set to the string `__main__`.  If this is true, we want to run the `unittest.main()` function (`main` function in the `unittest` module).

The `unittest.main()`function will examine the definition of the classes in our python file.  The `unittest` module can find all the methods of our class that has the prefix `test_` and will run those test methods.  Therefore to add a test to the framework, all we need is to place a new method into the class and the unit test module will find it and run that test.

The following code will create a new test that will always fail:
```
  def test_testFailure(self):
        self.assertTrue(False, "this is printed when the assertion fails")
```
If we add the code above to the template provided in the lab and run the test, the unit test will run the two tests `test_init` and `test_testFailure`. It will pass one test and fail one test.

```
python textproc_test.py
```
Results:
```
$ python test_test.py 
.F
======================================================================
FAIL: test_testFailure (__main__.TextprocTestCase)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "/home/jovyan/CS-3308/Summer-22/Lab-5/_TESTING/test_test.py", line 35, in test_testFailure
    self.assertTrue(False, "this is printed when the assertion fails")
AssertionError: False is not true : this is printed when the assertion fails

----------------------------------------------------------------------
Ran 2 tests in 0.001s

FAILED (failures=1)
```

<hr>
<hr>
