import BasicToolSet as BTS

# FME - A function to calculate Fast Modular Exponentiation (b^n mod m)
# Input:
#   b - Integer value that represents the base of of the FME (b) in (b^n mod m)
#   n - Integer value that represents the exponent value in FME (n) in (b^n mod m)
#   m - Integer value that represents the value that is being modulo'd against in FME (m) in (b^n mod m)
# Algorithm:
#   * Calculate the binary representation of n with Convert_Binary_String
#   * Reverse the binary number so that the last digit appears first in the array
#   * Set the return value (x) to 1
#   * Calculate power by taking the modulo of b and m
#   * Traverse the string of binary digits up to the length of the binary number
#       * Convert the string to an integer and store it in binVal
#       * If the current digit is a one, calculate x with (x * power) % m
#       * Update the power variable with (power * power) % m
#   * Return x after the for loop finishes completion
# Output:
#   x - Integer value that is returned from the expression of (b^n mod m)
def FME(b,n,m):
    DecInBin = BTS.Convert_Binary_String(n)
    DecInBin = DecInBin[::-1]
    x = 1
    power = b % m
    for i in DecInBin:
        binVal = int(i)
        if (binVal == 1):
            x = (x * power) % m
        power = (power * power) % m
    return x

# Euclidean_Alg - Greatest Common Divisor or Euclidean algorithm for two numbers a and b
# Input:
#   a - Integer value that represents the larger of the two values in the EEA calculation
#   b - Integer value that represents the smaller of the two values in the EEA calculation
# Algorithm:
#   * Assign values to the initial of a and b with m_0 and b_0
#   * Assign values to the initial Bezout coefficients s_1,t_1 with 1 and 0
#   * Assign values to the updated Bezout coefficients s_2,t_2 with 0 and 1
#   * Execute the while loop until b is less than or equal to 0 (usually equal to 0)
#       * Calculate the modulo of a and b and assign it to k
#       * Calculate the integer division of a and b and assign it to q
#       * Update a to the current value of b and b to to the current value of k
#       * Calculate new values for the Bezout coefficients S_1,T_1 with s_2,t_2
#       * Calculate the new updated Bezout coefficients S_2,T_2 with s_1 - q * s_2, t_1 - q * t_2
#       * Update the Bezout coefficients (which will eventually be returned) s_1,t_1 with S_1,T_1
#       * Update the updated Bezout coefficients s_2,t_2 with S_2,T_2
#   * Return the GCD (a) and the Bezout coefficients (s_1,t_1) as an array after the loop
# Output:
#   This algorithm returns an array of values related to the Extended Euclidean Algorithm
#   a - This is the GCD of the two original numbers a and b
#   s_1 - This is the first Bezout coefficient (s) that is returned
#   t_1 - This is the second Bezout coefficient (t) that is returned
def Euclidean_Alg(a,b):
    a_0,b_0 = a,b
    s_1,t_1 = 1,0
    s_2,t_2 = 0,1
    while (b > 0):
        k = a % b
        q = a // b
        a = b
        b = k
        S_1,T_1 = s_2,t_2
        S_2,T_2 = s_1 - q * s_2, t_1 - q * t_2
        s_1,t_1 = S_1,T_1
        s_2,t_2 = S_2,T_2
    return [a,s_1,t_1]