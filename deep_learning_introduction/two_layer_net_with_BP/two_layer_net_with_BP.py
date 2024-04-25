from layer import Affine,SoftmaxWithLoss,Relu
from collections import OrderedDict
import numpy as np

class two_layer_net_with_BP:
    def __init__(self,input_size,hidden_size,output_size,weight_init_std=0.01):
        #初始化权重
        self.parameters={}
        self.parameters['W1']=weight_init_std*np.random.randn(input_size,hidden_size)
        self.parameters['b1'] = np.zeros(hidden_size)
        self.parameters['W2'] = weight_init_std * np.random.randn(hidden_size, output_size)
        self.parameters['b2'] = np.zeros(output_size)
        #初始化layer
        self.layer=OrderedDict()
        self.layer['Affine1']=Affine(self.parameters['W1'],self.parameters['b1'])
        self.layer['Relu1']=Relu()
        self.layer['Affine2']=Affine(self.parameters['W2'],self.parameters['b2'])

        self.lastLayer=SoftmaxWithLoss()
        #

    def predict(self,x):
        for layer in self.layer.values():
            x=layer.forward(x)
        return x

    def loss(self,x,label):
        result=self.predict(x)
        loss=self.lastLayer.forward(result,label)

        return loss

    def gradient(self,x,label):
        #forward
        self.loss(x,label)
        #backward
        dout=1
        dout=self.lastLayer.backward(dout)

        layers=list(self.layer.values())
        layers.reverse()
        for layer in layers:
            dout=layer.backward(dout)

        grads={}
        grads['W1']=self.layer['Affine1'].dW
        grads['b1'] = self.layer['Affine1'].db
        grads['W2'] = self.layer['Affine2'].dW
        grads['b2'] = self.layer['Affine2'].db

        return grads

    def accuracy(self,test_images,test_labels):
        result=self.predict(test_images)
        result_index=np.argmax(result,axis=1)
        label_index=np.argmax(test_labels,axis=1)
        accuracy=np.sum(result_index==label_index)/float(test_images.shape[0])
        return accuracy