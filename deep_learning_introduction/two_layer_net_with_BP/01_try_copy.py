import numpy as np

A=np.array([[1,2,3],
            [4,5,6]])
B=A.copy()
mask=(A>3)
A[mask]=0
print(A)
print(B)
#只要copy（浅拷贝）之后，numpy里的array就指向不同的内存空间