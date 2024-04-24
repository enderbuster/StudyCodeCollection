1. 由于numpy更新，keras不能用，所以需要指定numpy==1.23.5
2. 运行环境是windows不是linux
2. 需要安装keras库用来下载数据集,除了加载数据集以外的代码都是原生numpy
3. 用到的库：keras,pickle,numpy
4. 文件说明：带有try前缀的是测试代码
5. 04_training_two_layer_net.py会根据MNIST数据集训练，完成后用pickle保存训练模型
6. 05_test_accuracy.py会加载保存的训练模型，并在测试集上测试模型精准度
7. 由于计算梯度的方法是数值微分，所以该模型跑起来非常耗时间