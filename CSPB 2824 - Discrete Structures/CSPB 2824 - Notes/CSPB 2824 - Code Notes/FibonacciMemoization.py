from __future__ import print_function

def fib_memo(n, tbl):
    if n <= 1:
        return 1
    if n in tbl:
        return tbl[n]
    res = fib_memo(n-1, tbl) + fib_memo(n-2, tbl)
    tbl[n] = res
    return res


def fib(n):
    mytbl = {}
    return fib_memo(n, mytbl)


print('n', 'Fib(n)', sep='\t')
for i in range(0, 500):
    print(i, fib(i), sep='\t')
