
from sklearn.svm import SVC
import matplotlib.pyplot as plt
import numpy as np
from sklearn.model_selection import cross_val_score
import pandas as pd  # 导入数据分析库
from sklearn.model_selection import train_test_split
import cmath
from random import shuffle  # 导入随机函数shuffle，用来打算数据
from sklearn.metrics import confusion_matrix, accuracy_score, zero_one_loss, f1_score, classification_report  # 导入混淆矩阵函数
from sklearn.metrics import roc_curve  # 导入ROC曲线函数
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.metrics import jaccard_score

def train_svm(title):
    datafile = "./冠心病.csv"  # 数据名
    data1 = pd.read_csv(datafile) * 1000  # 读取数据
    data1 = data1.values  # 将表格转换为矩阵
    # shuffle(data)  # 随机打乱数据
    dat = data1[:, :10]
    target = data1[:, 10]
    # 使用l2正则化


    Xtrain, Xtest, Ytrain, Ytest = train_test_split(dat, target, test_size=0.3, random_state=45)
    clf = SVC(kernel = "linear")
    clf.fit(Xtrain, Ytrain)
    rfc_s = cross_val_score(clf, dat, target, cv=9).mean()
    print(rfc_s)
    analysis_results(clf, title, Xtrain, Xtest, Ytrain, Ytest)


def cm_show(y, yp, title):
    cm = confusion_matrix(y, yp)
    plt.imshow(cm, interpolation='nearest')  # 热图显示
    #    plt.matshow(cm, cmap=plt.cm.Greens)  # 画混淆矩阵图，配色风格使用cm.Greens，更多风格请参考官网。
    plt.colorbar()  # 颜色标签
    # 控制坐标的数字和长度
    # num_local = np.array(range(len('123')))
    num_local = np.array(range(3))
    plt.xticks(num_local, '012')
    plt.yticks(num_local, '012')
    for x in range(len(cm)):  # 数据标签
        for y in range(len(cm)):
            plt.annotate(cm[x, y], xy=(x, y), horizontalalignment='center', verticalalignment='center')
    plt.title(title)
    plt.ylabel('Predicted label')  # 坐标轴标签
    plt.xlabel('True label')  # 坐标轴标签
    plt.show()  # 显示作图结果


def analysis_results(label_name, title, Xtrain, Xtest, Ytrain, Ytest):
    ylr = label_name.predict(Xtest)
    ylrT = label_name.predict(Xtrain)
    print("Train Accuracy of LR:", round(accuracy_score(Ytrain, ylrT), 3))
    print("Test Accuracy of  LR:", round(accuracy_score(Ytest, ylr), 3))
    print("Test Loss of      LR:", round(zero_one_loss(Ytest, ylr), 3))
    print("Jaccard Coef of   LR:", round(jaccard_score(Ytest, ylr, average='weighted'), 3))
    print("Dice Coef of      LR:", round(f1_score(Ytest, ylr, average='weighted'), 3))
    print(classification_report(Ytest, ylr))
    cm_show(Ytest, ylr, title)

if __name__ == '__main__':
    train_svm('title')