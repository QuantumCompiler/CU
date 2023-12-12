# Python tutor Link: https://goo.gl/r6EHpi
# Functions are values in Python.
# We will explore lambdas, closures, and currying

def plus_one(x):
    return x + 1

def square(x):
    return x * x

def cube(x):
    return x * x * x


# Functions are values in python. You can pass a function as an argument to another function.

def apply(fun, value): # fun is a function , value is an argument
    return fun(value)

print(apply(plus_one, 10))
print(apply(square, 25))
print(apply(cube, 23))

# Functions that take in other functions as arguments are called higher order functions.

def compose_and_apply(fun1, fun2, value):
    return fun1(fun2(value))

print(compose_and_apply(plus_one, plus_one, 11))
print(compose_and_apply(square, plus_one, 10))
print(compose_and_apply(plus_one, square, 14))
print(compose_and_apply(square, cube, 2))
print(compose_and_apply(cube, square, 2))


# Now tell me what does this function do?

def compose_thrice_and_apply(fun, value):
    return fun(fun(fun(value)))


# LAMBDAS
# Pythontutor link: https://goo.gl/WtSYjZ
# This is how we traditionally define functions in python
def square(x):
    return x * x

# This is another way of defining the same
square2 = lambda x: x * x
# The definition of square2 above is called a "lambda"
# Following Lambda Calculus defined by Alonzo Church in the 1930s


# Let us try one more example
def multiply(x, y):
    return x * y

# Another way of defining the same
multiply2 = lambda x, y: x * y


# Lambdas are meant to write simple functions that fit in one line.
def is_prime(n): # Type is int -> bool
    if (n < 0):
        n = - n
    for k in range(2, n):
        if n % k == 0:
            return False # definitely not prime
    return True # No divisors, hence prime

# The function above cannot be easily lamba-ed ;-)

def add_and_multiply(x, y, z):
    return (y + z) * x

# Can you define a lambda for the function above?


# CLOSURES
# Python Tutor Link: https://goo.gl/k7oyis
# Functions can return functions
# just like they can take functions as arguments.

def multiply_by_x(a):
    def multiply(y): # Inner Function
        return y * a # a is the argument to the outer function
    return multiply

multiply_by_20 = multiply_by_x(20) # What is multiply_by_20?


print(multiply_by_20(5))
print(multiply_by_20(-5))
print(multiply_by_20('Walla '))




def hello_whatever(a):
    def worker_fun(b):
        return 'Hello '+ a + ' '+ b
    return worker_fun

hello_world = hello_whatever('World')

hello_hello = hello_whatever('Hello')

print(hello_world('CSCI 2824'))
print(hello_world('Tomatoes'))
print(hello_hello('Potatoes'))

def repeatn(n):
    def worker_fun(b):
        return b * n
    return worker_fun

wfun = repeatn(20)
print(wfun(45))
print(wfun('hello'))
print(wfun(-2.512))

once_more = repeatn(34.3)
print(once_more(12))
print(once_more(-11.3))
