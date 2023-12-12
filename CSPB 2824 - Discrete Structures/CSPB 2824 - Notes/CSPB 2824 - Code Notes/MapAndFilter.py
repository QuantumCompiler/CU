# Part (a) MAP
#Python tutor links:
#  https://goo.gl/bbsdG2
#  https://goo.gl/kMNF9Q
#  https://goo.gl/S5pZBb

# How do we compute the square of every element of the list?
l1 = [1, 2, 3, 4]

def square(x):
    return x**2

# One way is to write a for loop
l2 = []
for elts in l1:
    l2.append( square(elts) )

# When the loop is done, l2 holds the square of all elements in l1
print(l2)

# Functional programming achieves the same using the "map" operation
# map (function, list) --> applies the function to every element in the list
m3 = map(square, l1) # Apply square to every element in the list.
# The result is not converted back into a list but you can do so as follows
l3 = list(m3)
print(l3)

# Let us do another example.
# Can you figure out what the code below does?

s1 = ['World', 'Tomatoes', 'Potatoes', 'Crocodiles', 'Eggplants', 'Mice']

fun = lambda x: 'Hello' + x # What does this lambda do?
m1 = map(fun, s1) # What is the meaning of this line?
s2 = list(m1) # Why do we need to say list(m1)?
print(s2) # Can you predict what will be printed?


# Another example to drive the point home

fun2 = lambda x: x + ' ' + x # what does this lambda do?
m2 = map(fun2, s1) # What does this line do?
s3 = list(m2) # What does this line do?
print(list(m3)) # Can you predict what will be printed by this line?


# A final example using map

# what do the functions below do?
def square(x):
    return x * x

def double(x):
    return 2 * x

def addOne(x):
    return x + 1


# What is this a list of ?
lfuns = [ square, double, addOne, double, square, addOne, addOne]
n = 20
# What does this line do?
m =  map( lambda x: x(n), lfuns)
l4 = list(m)
print(l4) # Can you predict what l4 will be?


# PART (B): filter
# Python tutor links:
#  https://goo.gl/7UtM49
#  https://goo.gl/AVeqrv


# Another common pattern that we use is to filter elements from a list.

l1 = ['Andrew', 'Arlen', 'Alicia', 'Axel', 'Alexa', 'Bella', 'Beatrice']

# I would like to select all elements of the list that begin with an A
# Here is how I dould do with a for loop
def beginsWithA(s): # String -> Bool
    return s[0] == 'A'

l2 = []
for s in l1:
    if beginsWithA(s):
        l2.append(s)

print(l2)


# Python offers a function called filter

m = filter(beginsWithA, l1)
# SELECT all elements in l1 that return True if beginsWithA is called
# The function "beginsWithA" serves the role of a predicate
# filter returns all elements in the list l1, that satisfy the predicate

# filter(predicate, list) : return all elements in list that satisfy predicate
# predicate must be of type that inputs elements of the list and
#                                returns True/False

l3 = list(m)

print(l3)


# Let us do another example
# I would like to find out all factors of a number n = 71

rng = range(2, 71) # Includes all numbers from 2 to 70
pred = lambda k: 71 % k == 0 # Returns true if k divides 71
filter_obj = filter(pred, rng) # Select all elements in range rng, that satisfy the predicate pred
l = list(filter_obj)
print(l)



rng2 = range(2, 87) # Includes all numbers from 2 to 87
pred2 = lambda k: 87 % k == 0 # Returns true if k divides 87
filter_obj2 = filter(pred2, rng2) # Select all elements in range rng, that satisfy the predicate pred
l2 = list(filter_obj2)
print(l2)


# PART (C) Reduce
# PythonTutor Link: https://goo.gl/2zomVM
#                   https://goo.gl/ZX18rx

l = [15, 25, 30, 54, 71, 89, 231 ]

# I wish to sum up the elements of the list l

n = 0
for elts in l:
    n = n  + elts
print(n)


# There is a function called reduce that can replace the for loop

from functools import reduce # reduce is not yet a core part of python, we import it from a library

def sum2(x, y):
    return x + y

s = reduce( sum2, l, 0)
print(list(s))

# REDUCE takes a list and repeatedly keeps applying a function on it, reducing it to a single value


# If l were the list l[0], l[1], ..., l[n-1],

# reduce(sum2, l, 0) is simply
#  sum2(sum2(... sum2(sum2(sum2(0, l[0]), l[1]), l[2]), .... ), l[n-1])
# It is easier to understand reduce step by step

# Step 1: calculate sum2(0, l[0]) -- call this s1
# Step 2: sum2(s1, l[1]) -- call this s2
# Step 3: sum2(s2, l[2]) -- call this s3
#...
# Step n: sum2(sn-1, l[n-1]) -- This is the final answer
# Eg., reduce(f, [1, 2], 0) will be
#  f( f(0, 1), 2)
# Eg., reduce(f, [1, 2, 3], 0) will be
#  f( f( f(0, 1), 2), 3)

p = reduce( lambda x, y: x * y, l, 1) # What does this do?
print(list(p))


def factorial(n):
    rng = range(1, n+1) # this includes n
    fun = lambda x, y: x * y
    f = reduce(fun, rng, 1)
    return f


n0 = factorial(1)
n1 = factorial(10)
n2= factorial(0)
