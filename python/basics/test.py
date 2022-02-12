import os
import numpy as np

def zero_matrix(m,n):
    return np.zeros((m,n),dtype=int)

#Types in python

# 1. numpy N dimensional arrays - can be converted to and from python lists
A = zero_matrix(3, 4)
print(A)

#tuple
T = (1, 3.2, "tuples are static, and so faster than lists")
print(type(T))

#list
L = [1, 2, 4, 7]
print (type(L))
subL = [x for x in L if x % 2 == 0]
print(subL)

#list of lists
LL = [L, L]
print (type(LL))
#convert to numpy array
LLA = np.asarray(LL)
print (LLA.shape)

#dictionary
D = {'a' : 97, 'b' : 98, 'd' : 100}
print (type(D))
for k in D.keys():
    print (k)

#sets
S = {"No", "duplicates", "allowed"}
print(type(S))
L1 = [1,2,3,1,2,5,8,1]
#remove duplicates from L1
L2 = list(set(L1)) #create a set from L1 and then a list
print(L2)

#formatting in python
# I got marks: M => 97, S => 96, E = 89.50
M = 97
S = 96
E = 89.50
print(type(M))
print(type(E))
print("I got marks: M = {1:8d}, E = {0:3.5f}\n".format(E,M))

