from two_layer_net_with_BP import two_layer_net_with_BP
import numpy as np
import pickle
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

#超参数
iters_num=100000
train_size=train_images.shape[0]
batch_size=100
learning_rate=0.1
iter_per_epoch=max(train_size/batch_size,1)
network=two_layer_net_with_BP(input_size=28*28,hidden_size=20,output_size=10)
#开始迭代
for i in range(0,iters_num):
    batch_mask=np.random.choice(train_size,batch_size)
    train_images_batch=train_images[batch_mask]
    train_labels_batch=train_labels[batch_mask]

    grad=network.gradient(train_images_batch,train_labels_batch)

    for key in grad.keys():
        network.parameters[key]-=learning_rate*grad[key]

    if i%iter_per_epoch==0:
        loss=network.loss(train_images_batch,train_labels_batch)
        print(loss)

with open('two_layer_net_with_BP.pickle','wb') as file:
    pickle.dump(network,file)

#at first,loss=2.3016156902476728
#finally,loss=0.00833368983317493
#train_size=60,000;batch_size=100
#iter_per_epoch=600
#iters_num=100,000,所以会打印100,000/600约等于166条输出然后结束
#运行的速度非常相比数值微分快多了
