1. 相比于上一个的两层神经网络，这次使用了反向传播计算梯度
2. 为了使用反向传播，创建了layer类，用来保存正向传播的一些参数
3. Affine层的公式需要学习矩阵微积分，我只推了一部分
4. softmaxWithLoss也是没推公式，直接套用
5. 最后的精准度是0.9591
6. 02_training_two_layer.py训练模型，并保存在.pickle文件里
7. 03_print)accuracy.py加载模型，并计算和打印精准度