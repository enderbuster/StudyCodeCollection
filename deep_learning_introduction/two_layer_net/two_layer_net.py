import numpy as np
from activation_function import sigmoid,softmax
from gradient_function import numeric_diff
from loss_function import cross_entropy_error
#只支持ndim=2的输入
class TwoLayerNet:
    def __init__(self,input_size,hidden_size,output_size,weight_init_std=0.01):
        self.params={}
        self.params['W1']=weight_init_std*np.random.randn(input_size,hidden_size)
        self.params['b1']=np.zeros(hidden_size)
        self.params['W2']=weight_init_std*np.random.randn(hidden_size,output_size)
        self.params['b2']=np.zeros(output_size)

    def predict(self,x):
        W1,W2=self.params['W1'],self.params['W2']
        b1,b2=self.params['b1'],self.params['b2']

        temp1=np.dot(x,W1)+b1
        temp2=sigmoid(temp1)
        temp3=np.dot(temp2,W2)+b2
        temp4=softmax(temp3)

        return temp4

    def loss(self,x,label):
        result=self.predict(x)

        return cross_entropy_error(result,label)

    def numeric_gradient(self,x,label):
        loss_W=lambda W:self.loss(x,label) #W是个伪参数

        grads={}
        grads['W1']=numeric_diff(loss_W,self.params['W1'])
        grads['b1'] = numeric_diff(loss_W, self.params['b1'])
        grads['W2'] = numeric_diff(loss_W, self.params['W2'])
        grads['b2'] = numeric_diff(loss_W, self.params['b2'])

        return grads

    def accuracy(self,test_images,test_labels):
        result=self.predict(test_images)
        result_index=np.argmax(result,axis=1)
        label_index=np.argmax(test_labels,axis=1)
        accuracy=np.sum(result_index==label_index)/float(test_images.shape[0])

        return accuracy
