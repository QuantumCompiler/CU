# PythonTutor Link:https://goo.gl/izf6Ta
# OK, let us explore some interesting tips for everything we learned
# using lists and enumerations in Python
# What are lists?


# A list is like an array in python
l1 = [0, 1, 2, 3, 4, 5, 6] # list[int]

l2 = ['Hello', 'I', 'Am', 'Not','Part', 'Of', 'A list'] # list[string]

# It represents a sequence of values

l3 = ['Pasta Sauce', 'Fettucine', 'Mozzarella'] # list[string]

# There is a special list with nothing in it

emp_list = []

# Python lists can include different types of objects

l4 = ['Pasta', 25, 'Pizza', 45, 'Health', 30] # list[{string, int}]

# Lists can have lists in them

matrix= [ [ 1.0, 2.3, 1.2], [1.1, 1.3, 0.0], [0.0, 0.1, 0.2] ] # list[list[float]]

# We will now explore basic list operations.
# (a) find the length of a list

n1 = len(l1)
print(n1)

n4 = len(l4)
print(n4)

m = len(matrix)
print(m)

n0 = len(emp_list)
print(n0)


# PythonTutor Link:https://goo.gl/hvXqyK

l1 = [0, 1, 2, 3, 4, 5, 6] # list[int]
l2 = ['Hello', 'I', 'Am', 'Not','Part', 'Of', 'A list'] # list[string]
l3 = ['Pasta Sauce', 'Fettucine', 'Mozzarella'] # list[string]
emp_list = []
l4 = ['Pasta', 25, 'Pizza', 45, 'Health', 30] # list[{string, int}]
matrix= [ [ 1.0, 2.3, 1.2], [1.1, 1.3, 0.0], [0.0, 0.1, 0.2] ] # list[list[float]]

# (b) You can access elements of a list of length n from l[0], l[1], ... l[n-1]
i1 = l1[0]

i2 = l1[1]

i3 = l1[3]

i6 = l1[6]

i7 = l1[7] # Out of bounds access --- ERROR


# (c) You can append an element to the end of a list


l1.append(7)
print(l1)

l1.append(8)
print(l1)

matrix.append([1.0, 0.0, 0.0])
print(matrix)

emp_list.append('NonEmpty')
print(emp_list)

# (d) You can delete an element from a list

# 1. Delete the very first element from l1

l1.pop(0)
print(l1)

l1.pop(5)
print(l1)

emp_list.pop(0)
print(emp_list)

l1.pop(7) # ERROR
print(l1)

# Python Tutor Link: https://goo.gl/Qd7sX5
# Now we will look at manipulating lists


l1 = [0, 1, 2, 3, 4, 5, 6] # list[int]
l2 = ['Hello', 'I', 'Am', 'Not','Part', 'Of', 'A list'] # list[string]
l3 = ['Pasta Sauce', 'Fettucine', 'Mozzarella'] # list[string]
emp_list = []
l4 = ['Pasta', 25, 'Pizza', 45, 'Health', 30] # list[{string, int}]
matrix= [ [ 1.0, 2.3, 1.2], [1.1, 1.3, 0.0], [0.0, 0.1, 0.2] ] # list[list[float]]


# Iterate through a list
for elts in l1:
    print(elts)

# Iterate through a list by indices
n = len(l2)
for j in range(0, n):
    print(l2[j]) # Print the jth element of l2




def add_one_to_elements(l): # List[int] -> List[int]
    return_list = []
    for elts in l: # This for loop iterates through all elements of a list
        return_list.append(elts + 1)
    return return_list

def reverse_a_list(l):
    reversed_list = []
    for elts in l: # This for loop iterates through all elements of a list
        reversed_list.insert(0, elts) # Add the element to the beginning of reversed list
    return reversed_list





l5 = add_one_to_elements(l1)
l6 = reverse_a_list(l2)
l7 = add_one_to_elements(emp_list)
