from __future__ import print_function

def g(n):
    if n <= 2:
        return n
    return g(n-2) * g(n-2) - g(n-1) * g(n-3)


def g_memo(n, tbl):
    if n <= 2:
        return n
    if n in tbl:
        return tbl[n]
    res = g_memo(n-2, tbl) * g_memo(n-2, tbl) - g_memo(n-1,tbl) * g_memo(n-3, tbl)
    tbl[n] = res
    return res

print('Without memoization')
print('n', 'g(n)', sep='\t')
for i in range(0,25):
    print(i, g(i), sep='\t')


print('With memoization')
print('n', 'g(n)', sep='\t')
for i in range(0,25):
    print(i, g_memo(i,{}), sep='\t')
