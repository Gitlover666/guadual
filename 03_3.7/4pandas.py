from pymongo import MongoClient

import pandas as pd
import numpy as np
import random

T = pd.DataFrame(np.arange(12).reshape(3, 4))
data = pd.read_csv("冠心病.csv")
da1 = data.head()
da2 = data.info()
print(da2)

a = [1, 2, 3]
b = a
a = a.append(4)

a = 5
b = a
c = a is b
print(c)
c = a is not b
print(c)
print(a == b)

a_list = ['foo', 2, [4, 5]]
a_list[2] = (3, 4)
a_list[1] = '呵呵'
a_list[0] = 11
print(a_list)
a = '22222'

print(a)
c = 5 if 5 < 6 else 6
print(c)

a = {1, 2, 3, 10, 4}

print(list(a))

data = pd.DataFrame({'k1': ['one', 'two'] * 3 + ['two'], 'k2': [1, 1, 2, 3, 3, 4, 4]})
print(data)

aaa = [1, 5, 6, 8, 3, 3, 5, 1, 9, 0]
c = aaa[::-1]
print(aaa[::2])
all_data = [['Maria', 'Juan', 'Javier', 'Natalia', 'Pilar'], ['John', 'Emily', 'Steven', 'Michael', 'Mary']]
names_of_interest = []
for names in all_data:
    print(names)
    enough_es = [name for name in names if name.count('e') >= 2]
    print(enough_es)
    names_of_interest.extend(enough_es)
a = []


def func():
    for i in range(5):
        a.append(i)
    return a


print(func())


def f():
    a = 5
    b = 6
    c = 7
    return {'a': a, 'b': b, 'c': c}


return_value = f()


print(return_value)
data = np.random.randn(2, 3)
print(data)

price = float(input("请输入价格："))

dd = float(input("请输入多少斤："))
money = price * dd
# 这两个功能类似

print('the money is that:',money)
print("the money is that: %s" % money)

dat = input("请输入合格或者不合格：")

if "合格" == dat:
    print("合格了")
elif "不合格" == dat:
    print("不合格")
else:
    print("错误")

computer = random.randint(1,3)
print(computer)
computer = list(range(10))
print(computer)


i = 0
re = 0
while i <= 5:
    if i % 2 == 0:
        re = re + i
    i = i + 1
print("结果是：%d" % re)
print('re', re)

