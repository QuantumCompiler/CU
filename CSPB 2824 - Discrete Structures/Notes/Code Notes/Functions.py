# Let us start with a simple function to square a number
# SHORT LINK to Python Tutor: https://goo.gl/zcBtfn
def square(x): # Type is int -> int
    return x * x


#Here is a function with two arguments
#SHORT LINK to Python Tutor: https://goo.gl/NkdkQG
def multiply(x, y): # Type is int * int -> int
    return x * y
# Here is a function with five arguments
def multiply5(x, y, z, a, b):
    # Type is int * int * int * int * int -> int
    return x * y * z * a * b

#Functions need not return anything
def dummy_function(x): # Type is int -> None
    return

# Functions need not have arguments:
def do_not_argue(): # Type is None -> String
    return 'Silence is Golden'


#Functions can return Booleans
def is_prime(n): # Type is int -> bool
    if (n < 0):
        n = - n
    for k in range(2, n):
        if n % k == 0:
            return False # definitely not prime
    return True # No divisors, hence prime


#SHORTENED LINK TO PYHON TUTOR https://goo.gl/78nTdk
#Function to Add One
def add_one(x): # Type is int -> int
    return x + 1

#Functions can call other functions
def square_and_add_one(x): # Type is int -> int
    return square(add_one(x))

def add_one_and_square(x): # Type is int -> int
    return add_one(square(x))


def is_prime_add_one(x): # Type is int -> bool
    y = add_one(x)
    z = is_prime(y)
    return z # SAME AS is_prime(add_one(x))


#Functions can call themselves: recursion
#Pythontutor Link: https://goo.gl/bkEpPJ
def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n - 1)

def fibonacci(n):
    if n <= 1:
        return 1
    return fibonacci(n-1) + fibonacci(n-2)


# Pythontutor Link: https://goo.gl/awQ8SN
# Pure versus impure functions: Side Effects
# First let us understand what is a "side effect"

n = 0 # Let us define a variable n in the global frame

def side_effect_fun(k):
    # This allows us to reference the n in the global frame
    global n
    n = n + 1
    return k + n

# Is side_effect_fun a function in the mathematical sense?
print('1', side_effect_fun(20))
print('2', side_effect_fun(20))
print('3', side_effect_fun(20))
print('4', side_effect_fun(20))
print('5', side_effect_fun(20))



# Pythontutor Link: https://goo.gl/DHUfJb
# Side effects can be very subtle.
# You can have them without a global variable.
from random import randint

def side_effect_fun2(k):
    # generate a random integer between 0 and 10
    rnum = randint(0,10)
    return k + rnum


print('1', side_effect_fun2(20))
print('2', side_effect_fun2(20))
print('3', side_effect_fun2(20))
print('4', side_effect_fun2(20))

# Side effects can include stuff like print statements

def side_effect_fun3(k):
    print('You called side_effect_fun3 with:', k)
    # print is considered a side effect since it
    # changes the state of the screen.
    return k


# Polymorphic Functions
# Python Tutor Link: https://goo.gl/jadGKD
def add_two(x, y):
    return x + y

def add_two_mul(x, y, z):
    return (x + y) * z

def multiply(x, y):
    return x * y

print(add_two(1, 2))
print(add_two(1.35, 2.122))
print(add_two('hello',' world'))

print(add_two_mul(1, 2.5, 3.2))
print(add_two_mul('hello', 'world', 3))

print(multiply(20, 30))
print(multiply(200.2, -301.3))
print(multiply('Walla ', 5))
