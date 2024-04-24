import numpy as np
#loss_func(x),x:tensor.ndim=2
def numeric_diff(loss_func,x):
    delta=1e-4
    grad=np.zeros_like(x)
    #如果是1维的,b1,b2
    if x.ndim==1:
        for index in range(0,x.size):
            temp=x[index]
            x[index]=x[index]+delta
            f1=loss_func(x)
            x[index]=x[index]-delta
            f2=loss_func(x)
            grad[index]=(f1-f2)/(2*delta)
            x[index]=temp #还原原本值
        return grad
    #如果是2维，W1,W2
    if x.ndim==2:
        for row_index in range(0,x.shape[0]):
            for col_index in range(0,x.shape[1]):
                temp=x[row_index][col_index]
                x[row_index][col_index]=temp+delta
                f1=loss_func(x)
                x[row_index][col_index] = temp - delta
                f2=loss_func(x)
                grad[row_index][col_index]=(f1-f2)/(2*delta)
                x[row_index][col_index] = temp #还原原本的值
        return grad
#f:loss_func(x),init_x:neural_networl parameters
#使用数值微分法
def gradient_descent(f,init_x,lr=0.01,step_num=100):
    x=init_x

    for i in range(step_num):
        grad=numeric_diff(f,x)
        x-=lr*grad

    return x
