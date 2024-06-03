# Part a
def PartA(j0,jn):
    result = 0
    for i in range(j0,jn + 1):
        result += i + 1
    return result

# Part b
def PartB(j0,jn):
    result = 0
    for i in range(j0,jn + 1):
        result += (-2)**i
    return result

# Part c
def PartC(j0,jn):
    result = 0
    for i in range(j0,jn + 1):
        result += 3
    return result

# Part d
def PartD(j0,jn):
    result = 0
    for i in range(j0,jn + 1):
        result += (2**(i + 1) - 2**i)
    return result

print(f"The result from part (d) of problem 29 is: {PartD(0,8)}")