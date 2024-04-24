import numpy as np
#x:tensor
def sigmoid(x):
    return 1/(1+np.exp(-x))
#x:tensor.ndim=2
def softmax(x):
    max=np.max(x)
    exp_x=np.exp(x-max)
    for row_index in range(0,exp_x.shape[0]):
        sum=np.sum(exp_x[row_index])
        exp_x[row_index]=exp_x[row_index]/sum
    return exp_x
