import numpy as np

# 使用numpy生出数组 得到ndarray数组类型
# t2 = np.arange(1, 4,)
# print(t2)
# print(type(t2))

# 修改类型输出就会有一个点，得到数据类型
# t1 = np.array(range(1, 4), dtype="float32")
# print(t1)
# print(t1.dtype)

# 数组维度
# t1 = np.arange(24)
# print(t1.shape)

# 改变数组维度
# print(t1.reshape((4, 6)))


# 导入csv

t1_path1 = "冠心病.csv"
t3 = np.loadtxt(t1_path1, delimiter=",", dtype="float")
print(t3)
print("*"*100)
# 取单行
# print(t3[2])
# print("*"*100)
# print(t3[2:])
# print("*"*100)
# print(t3[[0, 2, 3]])
# 取列
# print("*"*100)
# print(t3[1, 1])
# print(t3[1, :])
# print(t3[[1, 3], :])
# print(t3[:, [1, 3]])

# 取多行和多列
# print(t3[2:5, 1:4])

# 取点
# print(t3[[0, 1], [0, 2]])

