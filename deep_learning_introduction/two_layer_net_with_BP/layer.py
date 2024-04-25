import numpy as np
from activation_function import softmax
from loss_function import cross_entropy_error

class Affine:
    def __init__(self,W,b):
        self.W=W
        self.b=b
        self.x=None
        self.dW=None
        self.db=None

    def forward(self,x):
        self.x=x
        out=np.dot(x,self.W)+self.b

        return out

    def backward(self,dout):
        dx=np.dot(dout,self.W.T)
        self.dW=np.dot(self.x.T,dout)
        self.db=np.sum(dout,axis=0)

        return dx
class SoftmaxWithLoss:
    def __init__(self):
        self.loss=None
        self.result=None
        self.label=None

    def forward(self,x,lable):
        self.label=lable
        self.result=softmax(x)
        self.loss=cross_entropy_error(self.result,lable)

        return self.loss

    def backward(self,dout=1):
        batch_size=self.result.shape[0]
        dx=(self.result-self.label)/batch_size

        return dx

class Relu:
    def __init__(self):
        self.mask=None

    def forward(self,x):
        self.mask=(x<=0)
        out=x.copy()
        out[self.mask]=0

        return out

    def backward(self,dout):
        dout[self.mask]=0
        dx=dout

        return dx

