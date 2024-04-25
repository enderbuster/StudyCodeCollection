import numpy as np
import pickle
from keras.datasets import mnist
from tensorflow.keras.utils import to_categorical
from two_layer_net_with_BP import two_layer_net_with_BP

with open('two_layer_net_with_BP.pickle','rb') as file:
    network:two_layer_net_with_BP=pickle.load(file)

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
print(accuracy) #0.9591