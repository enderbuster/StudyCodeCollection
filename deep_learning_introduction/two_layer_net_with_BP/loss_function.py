import numpy as np

#label是onehot形式,result是vector
def cross_entropy_error(result,label):
    delta=1e-7#防止log0导致-inf
    #这个if函数应该没有什么意义，输入都是ndim=2
    if result.ndim==1:
        result=result.reshape((1,result.size))
        label=label.reshape((1,label.size))
    batch_size=result.shape[0]
    return -np.sum(label*np.log(result+delta))/batch_size

