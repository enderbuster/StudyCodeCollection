from two_layer_net import TwoLayerNet
import numpy as np
from keras.datasets import mnist
from tensorflow.keras.utils import to_categorical
import pickle

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

#超参数
iters_num=2000
train_size=train_images.shape[0]
batch_size=5
learning_rate=0.1

network=TwoLayerNet(input_size=784,hidden_size=50,output_size=10)

for i in range(iters_num):
    batch_mask=np.random.choice(train_size,batch_size)
    train_images_batch=train_images[batch_mask]
    train_labels_batch=train_labels[batch_mask]

    grad=network.numeric_gradient(train_images_batch,train_labels_batch)

    for key in ('W1','b1','W2','b2'):
        network.params[key]-=learning_rate*grad[key]

    loss=network.loss(train_images_batch,train_labels_batch)
    print(loss)

with open('two_layer_net.pickle','wb') as file:
    pickle.dump(network,file)

#batch_size=5,iters_num=2000，运行了快2个多小时，所以说还得赶快改进算法
#at first,loss=2.175155543519828
#after training,loss=0.12791936761808942