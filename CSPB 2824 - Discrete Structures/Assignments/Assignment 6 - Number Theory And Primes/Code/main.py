import numpy as np
import math as math
import time as time

# RFME - A function to calculate Fast Modular Exponentiation Recursively (a^n mod b)
# Input:
#   a - Integer value that represents the number being raised to some power in (a^n mod b)
#   n - Integer value that represents the exponent value in (a^n mod b)
#   b - Integer value that represents the number that a quantity is being modulo'd with in (a^n mod b)
# Algorithm:
#   * If n is zero, then return 1 as the quantity
#   * If n is even, make a recursive call to the function
#   * If n is odd, make a recursive call to the function
# Output:
#   This function returns an integer value that is calculated from (a^n mod b)
def RFME(a,n,b):
    if (n == 0):
        return 1
    elif (n % 2 == 0):
        return FME(a, math.floor(n // 2), b)**2 % b
    else:
        return (FME(a, math.floor(n // 2), b)**2 % b * (a % b)) % b
    
# DecToBin - Converts a decimal number to binary
# Input:
#   n - Integer value that is to represent a number in decimal that is to be converted to binary
# Algorithm:
#   * Create an empty array for the digits of the binary number to be stored in
#   * While n is greater than 0, append the value of n mod 2 to the array
#       * Update the value of n by taking the floor of n divided by 2
#   * Reverse the array so that the digits are in correct order of the binary number
#   * Return the array
# Output:
#   This function returns an array of digits that represents a binary number
def DecToBin(n):
    array = []
    while(n > 0):
        array.append(n % 2)
        n = math.floor(n // 2)
    array.reverse()
    return array
    
# FME - A function to calculate Fast Modular Exponentiation (b^n mod m)
# Input:
#   b - Integer value that represents the base of of the FME (b) in (b^n mod m)
#   n - Integer value that represents the exponent value in FME (n) in (b^n mod m)
#   m - Integer value that represents the value that is being modulod against in FME (m) in (b^n mod m)
# Algorithm:
#   * Calculate the binary representation of n with DecToBin
#   * Reverse the binary number so that the last digit appears first in the array
#   * Set the return value (x) to 1
#   * Calculate power by taking the modulo of b and m
#   * Traverse the array of binary digits up to the length of the binary number
#       * If the current digit is a one, calculate x with (x * power) % m
#       * Update the power variable with (power * power) % m
#   * Return x after the for loop finishes completion
# Output:
#   x - Integer value that is returned from the expression of (b^n mod m)
def FME(b,n,m):
    DecInBin = DecToBin(n)
    DecInBin.reverse()
    x = 1
    power = b % m
    for i in range(0, len(DecInBin)):
        if (DecInBin[i] == 1):
            x = (x * power) % m
        power = (power * power) % m
    return x

# print(result)

# end_of_loop_val = 100000

# def NOT_FME1(a, n, m):
#     return a ** n % m

# def NOT_FME2(a, n, m):
#     return math.pow(a, n) % m

# start_time1 = time.time()

# for i in range(0, end_of_loop_val):
#     result = NOT_FME1(i, 8, 17)

# end_time1 = time.time()

# elapsed_time1 = end_time1 - start_time1

# start_time2 = time.time()

# for i in range(0, end_of_loop_val):
#     result = NOT_FME2(i, 8, 17)

# end_time2 = time.time()

# elapsed_time2 = end_time2 - start_time2

# start_time3 = time.time()

# for i in range(0, end_of_loop_val):
#     result = FME(i, 8, 17)

# end_time3 = time.time()

# elapsed_time3 = end_time3 - start_time3

# print(f"Elapsed time for NOT_FME1: {elapsed_time1} seconds")
# print(f"Elapsed time for NOT_FME2: {elapsed_time2} seconds")
# print(f"Elapsed time for FME: {elapsed_time3} seconds")
