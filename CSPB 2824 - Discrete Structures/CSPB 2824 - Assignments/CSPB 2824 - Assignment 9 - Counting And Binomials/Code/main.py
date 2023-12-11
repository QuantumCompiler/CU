from math import pow, factorial

def binom_coeff(a,b,n):
    coefficients = []
    for j in range(n + 1):
        result = (factorial(n) / (factorial(j) * factorial(n - j))) * (pow(a,(n - j))) * (pow(b,j))
        coefficients.append(result)
    return coefficients

def binom_product(a,b,n):
    coefficients = binom_coeff(a,b,n)
    result = 1
    for i in range(len(coefficients)):
        result *= coefficients[i]
    return result

def binom_sum(a,b,n):
    coefficients = binom_coeff(a,b,n)
    result = 0
    for i in range(len(coefficients)):
        result += coefficients[i]
    return result