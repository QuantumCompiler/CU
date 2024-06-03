from __future__ import print_function


def binary_search(a, target):
    lo, hi = 0, (len(a) -1)
    while lo <= hi:
        mid = (lo + hi) // 2
        if a[mid] == target:
            return mid
        elif a[mid] < target:
            lo = mid + 1
        else:
            hi = mid - 1
    return None

if __name__ == '__main__':
    a1 = [1, 2, 5, 7, 8, 9, 10, 10, 12, 15, 18, 21, 23, 45]
    tgt1 = 12
    t1 = binary_search(a1, tgt1)
    print('Searching for', tgt1, 'in', a1)
    print('return found at postion: ', t1)
    tgt2 = 11
    t2 = binary_search(a1, tgt2)
    print('Searching for', tgt2, 'in', a1)
    print('return found at position: ', t2)
