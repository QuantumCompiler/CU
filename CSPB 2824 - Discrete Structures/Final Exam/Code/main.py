# Problem 1
def compute_squared_distance(x1, y1, z1, x2, y2, z2):
    X = pow((x2 - x1),2)
    Y = pow((y2 - y1),2)
    Z = pow((z2 - z1),2)
    return X + Y + Z

# Problem 2
def count_all_factors(n):
    factors = 0
    for i in range(1, n + 1):
        if (n % i == 0):
            factors += 1
    return factors

# Problem 3
def my_little_function(a, b, c):
    x = c
    for i in range(0, a + b):
        x = x + c
    return x

# Problem 4
def fun1(a, b): 
    if a >= 0: 
        return b + ':' + str(a)
    else:   
        return b
def fun2(a):
    return a * a

# Problem 5
square = lambda x: x**2
multiply = lambda x, y: x*y
def to_the_power_seven(n):
    return int(pow(square(multiply(n,1)),3.5))

# Problem 6
add_and_multiply2 = lambda x, y, z: x + y * z
is_divisible_by2 = lambda n, k: n % k == 0
is_empty_list2 = lambda l: len(l) == 0

def add_and_multiply(x, y, z):
    return x + y * z

def is_divisible_by(n, k):
    if (n % k == 0):
        return True
    else:
        return False
    
def is_empty_list(l):
    if (len(l) == 0):
        return True
    else:
        return False;

# Problem 7
def concat(x, y):
    return x + ' ' + y

def concat_with_sep(x, y, sep):
    return x + sep + y

def concat_friendly(x):
    return 'Hello: '+ x

# Problem 8
square = lambda x: x**2
add_two = lambda x : x + 2
decr = lambda x : x - 1
incr = lambda x : x + 1
doub = lambda x: 2 * x

def compose_and_subtract(f, g, x):
    return f(g(x)) - g(f(x))

# Problem 9
multiply = lambda x, y: x * y
divide = lambda x, y: x // y
help_fun = lambda x, y: 'Help' + str(x) + str(y)
lst_ref = lambda x , y: x[y]

def apply_three_times(f, x, y):
    return f(x,f(x,f(x,y)))

# Problem 10
def make_friendly_list(l):
    if (len(l) == 0):
        return l
    else:
        ret = []
        for i in range(len(l)):
            stringVal = str(l[i])
            ret.append('hello: ' + stringVal)
        return ret

# Problem 11
def sum_max_and_min(l):
    if (len(l) == 0):
        return 0
    else:
        minVal = 1000
        maxVal = -1000
        for i in range(len(l)):
            if (l[i] < minVal):
                minVal = l[i]
            if (l[i] > maxVal):
                maxVal = l[i]
        return minVal + maxVal
    
# Problem 12
def echo_every_string(l, n):
    copy = n
    if (len(l) == 0):
        empty_list = []
        return empty_list
    else:
        def multString(n):
            return n * copy
        mapped = map(multString, l)
        ret = list(mapped)
        return ret

# Problem 13
number_to_string = lambda n: str(n)
string_to_number = lambda s: int(s)
reverse_string = lambda s: s[::-1]

def reverse_numbers_in_list(l):
    map1 = map(number_to_string,l)
    ret1 = list(map1)
    map2 = map(reverse_string, ret1)
    ret2 = list(map2)
    map3 = map(string_to_number, ret2)
    ret3 = list(map3)
    return ret3

# Problem 14
reverse_str = lambda s: s[::-1]

def find_all_palindromes(l):
    def IsPalindrome(string):
        return reverse_str(string) == string
    fltr = filter(IsPalindrome, l)
    ret = list(fltr)
    return ret