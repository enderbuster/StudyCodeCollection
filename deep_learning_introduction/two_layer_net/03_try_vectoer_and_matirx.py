import numpy as np
A=np.array([1,2,3])
print(A.shape)#(3,)
#A is [1,2,3] right now
print(A.size)#3

A=A.reshape((1,A.size))
print(A.shape)#(1, 3)
#A is [[1,2,3]] right now