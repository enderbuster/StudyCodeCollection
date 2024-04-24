import numpy as np

#label是onehot形式,result是vector
def cross_entropy_error(result,label):
    delta=1e-7#
    if result.ndim==1:
        result=result.reshape((1,result.size))
        label=label.reshape((1,label.size))
    batch_size=result.shape[0]
    return -np.sum(label*np.log(result+delta))/batch_size

