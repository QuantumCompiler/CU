import BasicToolSet as BTS
import FirstToolSet as FTS


# Find_Public_Key_e - This function finds a public key e such that it is relatively prime to (p-1)(q-1)
# Input:
#   p - First prime number
#   q - Second prime number
# Algorithm:
#   * Calculate both (p-1) and (q-1) and store them as P and Q
#   * Calculate the product of p and q and store it as n
#   * Initialize e to be 2
#   * While the gcd(e,P*Q) is not 1 and e is not equal to both p and q
#       * Increment e by 1
#   * Return e and n in an array
# Output:
#   This function returns the public key e and n
def Find_Public_Key_e(p, q):
    P = p - 1
    Q = q - 1
    n = p * q
    e = 2
    while (FTS.Euclidean_Alg(e,P*Q)[0] != 1 and e != p and e != q):
        e += 1
    return [e,n]

# Find_Private_Key_d - This function returns the private key d from a public key e and two prime numbers p and q
# Input:
#   e - Public key that is calculated with Find_Public_Key_e
#   p - First prime number
#   q - Second prime number
# Algorithm:
#   * Calculate (p-1) and (q-1) and store them as P and Q respectively
#   * Calculate the modular inverse (the Bezout coefficient) of e and P*Q and store it as d
#   * If d is negative, add the modulo to it until it is positive
#   * Return d
# Output:
#   This function returns the public key d
def Find_Private_Key_d(e, p, q):
    P = p - 1
    Q = q - 1
    d = FTS.Euclidean_Alg(e,P*Q)[1]
    if (d < 0):
        while(d < 0):
            d += P*Q
    return d