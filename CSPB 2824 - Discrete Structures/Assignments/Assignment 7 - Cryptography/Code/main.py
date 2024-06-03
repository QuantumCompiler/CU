# EEA - Greatest Common Divisor or Euclidean algorithm for two numbers m and n
# Input:
#   m - Integer value that represents the larger of the two values in the EEA calculation
#   n - Integer value that represents the smaller of the two values in the EEA calculation
# Algorithm:
#   * Assign values to the initial of m and n with m_0 and n_0
#   * Assign values to the initial Bezout coefficients s_1,t_1 with 1 and 0
#   * Assign values to the updated Bezout coefficients s_2,t_2 with 0 and 1
#   * Execute the while loop until n is less than or equal to 0 (usually equal to 0)
#       * Calculate the modulo of m and n and assign it to k
#       * Calculate the integer division of m and n and assign it to q
#       * Update m to the current value of n and n to to the current value of k
#       * Calculate new values for the Bezout coefficients S_1,T_1 with s_2,t_2
#       * Calculate the new updated Bezout coefficients S_2,T_2 with s_1 - q * s_2, t_1 - q * t_2
#       * Update the Bezout coefficients (which will eventually be returned) s_1,t_1 with S_1,T_1
#       * Update the updated Bezout coefficients s_2,t_2 with S_2,T_2
#   * Return the GCD (m) and the Bezout coefficients (s_1,t_1) as an array after the loop
# Output:
#   This algorithm returns an array of values related to the Extended Euclidean Algorithm
#   m - This is the GCD of the two original numbers m and n
#   s_1 - This is the first Bezout coefficient (s) that is returned
#   t_1 - This is the second Bezout coefficient (t) that is returned
def EEA(m,n):
    m_0,n_0 = m,n
    s_1,t_1 = 1,0
    s_2,t_2 = 0,1
    while (n > 0):
        k = m % n
        q = m // n
        m = n
        n = k
        S_1,T_1 = s_2,t_2
        S_2,T_2 = s_1 - q * s_2, t_1 - q * t_2
        s_1,t_1 = S_1,T_1
        s_2,t_2 = S_2,T_2
    return [m,s_1,t_1]

# HW Helper
def HWHelper(m,n):
    m_0,n_0 = m,n
    print(f"We seek to the Bezout coefficients of {m_0} and {n_0}, namely, express gcd({m_0},{n_0}) as a linear combination of {m_0} and {n_0}.")
    print(f"The Extended Euclidean Algorithm by default is: gcd(m,n) = sm + tn.")
    result = EEA(m,n)
    print(f"The gcd(m,n) = {result[0]}, the Bezout coefficients are s = {result[1]}, t = {result[2]}.")
    print(f"Finally, we have: {result[0]} = ({result[1]}){m_0} + ({result[2]}){n_0} expressed as a linear combination.")

# HW problems 41 - 44
# HWHelper(26,91)
# HWHelper(252,356)
# HWHelper(144,89)
# HWHelper(1001,100001)