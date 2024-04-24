import pickle
import numpy as np
from two_layer_net import TwoLayerNet
from keras.datasets import mnist
from tensorflow.keras.utils import to_categorical

#load neural_network
with open('two_layer_net.pickle','rb') as file:
    network:TwoLayerNet=pickle.load(file)
from keras.datasets import mnist
from tensorflow.keras.utils import to_categorical

#the data set is downloaded into C:\Users\My_User_Name\.keras\datasets
(train_images,train_labels),(test_images,test_labels)=mnist.load_data()
#现在还有3个步骤可以做：1.flatten,把二维的图像转化为1为array
train_images=train_images.reshape((60000,28*28))
test_images=test_images.reshape((10000,28*28))
#2.normolization，把0~255(int)的图像变为0~1(float)之间的数值
train_images=train_images.astype('float32')/255
test_images=test_images.astype('float32')/255
#3.把标签变成one-hot形式
train_labels=to_categorical(train_labels)
test_labels=to_categorical(test_labels)

accuracy=network.accuracy(test_images,test_labels)
print(f"accrracy:{accuracy}") #accrracy:0.8902
