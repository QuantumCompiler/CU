from __future__ import print_function


def fib(n):
    if n <= 1:
        return 1
    return fib(n-1)+fib(n-2)

print('n', 'Fib(n)', sep='\t')
for i in range(0, 500):
    print(i, fib(i), sep='\t')
