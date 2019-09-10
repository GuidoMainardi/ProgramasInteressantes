from collections import defaultdict

M = defaultdict(int)

def ackerman(m, n):
    if m == 0:
        res = n + 1
    elif n == 0:
        res = ackerman(m - 1, 1)
    else:
        res = ackerman(m - 1, ackerman(m, n - 1))
    M[(m, n)] = res
    return res
ackerman(4, 2)