from keras.datasets import mnist
from tensorflow.keras.utils import to_categorical

#the data set is downloaded into C:\Users\My_User_Name\.keras\datasets
(train_images,train_labels),(test_images,test_labels)=mnist.load_data()
print(train_images.shape)#(60000, 28, 28)
print(train_labels.shape)#(60000,)

print(test_images.shape)#(10000, 28, 28)
print(test_labels.shape)#(10000,)
#现在还有3个步骤可以做：1.flatten,把二维的图像转化为1为array
train_images=train_images.reshape((60000,28*28))
test_images=test_images.reshape((10000,28*28))
#2.normolization，把0~255(int)的图像变为0~1(float)之间的数值
train_images=train_images.astype('float32')/255
test_images=test_images.astype('float32')/255
#3.把标签变成one-hot形式
train_labels=to_categorical(train_labels)
test_labels=to_categorical(test_labels)
