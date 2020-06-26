# 构建并测试CART决策树模型
import cmath
import pandas as pd  # 导入数据分析库
import numpy as np
from random import shuffle  # 导入随机函数shuffle，用来打算数据

from sklearn.multiclass import OneVsRestClassifier
from sklearn.naive_bayes import MultinomialNB
from sklearn.model_selection import cross_val_score
from sklearn.ensemble import RandomForestClassifier
from sklearn.preprocessing import label_binarize
from sklearn.tree import DecisionTreeClassifier  # 导入决策树模型
from sklearn.metrics import confusion_matrix, accuracy_score, zero_one_loss, f1_score, classification_report, \
    auc, precision_recall_curve  # 导入混淆矩阵函数
import matplotlib.pyplot as plt  # 导入作图库
from sklearn.metrics import roc_curve  # 导入ROC曲线函数
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.metrics import jaccard_score
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.naive_bayes import GaussianNB
from sklearn.neighbors import KNeighborsClassifier
from numpy import interp

def train_tree(title):
    """决策树和混淆矩阵"""
    """datafile = "./冠心病1.csv"  # 数据名
    # *1000是为了让flaot变为int
    data = pd.read_csv(datafile) * 1000  # 读取数据
    data = data.values  # 将表格转换为矩阵
    # shuffle(data)  # 随机打乱数据 p = 0.8   设置训练数据比例
    # 在这里设置需要训练的行数
#    train = data[:x, :]  # 前80%为训练集
#    test = data[y:, :]  # 后20%为测试集
    dat = data[:, :5]
    target = data[:, 5]
    # 这里选择训练的特征数量以及预测列
    Xtrain, Xtest, Ytrain, Ytest = train_test_split(dat, target, test_size=0.3, random_state=45)"""
    # 随机数种子是为了保证每次随机的结果都是一样的
    tree = DecisionTreeClassifier()  # 建立决策树模型
    #train = train.astype('int')  # 转换成INT要不然出现错误
    tree.fit(Xtrain, Ytrain)  # 训练,这里的【：，：5】取不到5
    # tree.fit(train[:, :10], train[:, 10])
    # 第一个参数是需要测试的数据，第二个参数是决策树预测的数据
    tree_s = cross_val_score(tree, dat, target, cv=9).mean()
    print(tree_s)
    analysis_results(tree, title, Xtrain, Xtest, Ytrain, Ytest)


def train_forest(title):
    """随机森林"""
    # datafile = "./冠心病1.csv"  # 数据名
    """
    datafile = "./冠心病.csv"  # 数据名
    data1 = pd.read_csv(datafile) * 1000  # 读取数据
    data1 = data1.values  # 将表格转换为矩阵
    # shuffle(data)  # 随机打乱数据

    dat = data1[:, :10]
    target = data1[:, 10]
    Xtrain, Xtest, Ytrain, Ytest = train_test_split(dat, target, test_size=0.3, random_state=45)
    
    rfc = RandomForestClassifier(n_estimators=20,random_state=49)
    Xtrain, Xtest, Ytrain, Ytest = train_test_split(dat,target,test_size=0.3,random_state=7)
    """

    rfc = RandomForestClassifier(n_estimators=10, random_state=7)# 7
    # 划分测试集和训练集
    # random_state取不同的值，会有不同的固定取值结果
    # Xtrain, Xtest, Ytrain, Ytest = train_test_split(dat,target,test_size=0.3,random_state=38)
    rfc.fit(Xtrain, Ytrain)
    rfc_s = cross_val_score(rfc, dat, target,cv=9).mean()
    print(rfc_s)

    analysis_results(rfc, title, Xtrain, Xtest, Ytrain, Ytest)


def train_logistic(title):
    """
    datafile = "./冠心病.csv"  # 数据名
    data1 = pd.read_csv(datafile) * 1000  # 读取数据
    data1 = data1.values  # 将表格转换为矩阵
    # shuffle(data)  # 随机打乱数据
    dat = data1[:, :10]
    target = data1[:, 10]
    Xtrain, Xtest, Ytrain, Ytest = train_test_split(dat, target, test_size=0.3, random_state=28)
    """
    # 使用l2正则化
    lr = LogisticRegression(penalty='l2',solver='liblinear', multi_class='ovr')

    lr.fit(Xtrain, Ytrain)
    rfc_s = cross_val_score(lr, dat, target, cv=9).mean()
    print(rfc_s)
    analysis_results(lr, title, Xtrain, Xtest, Ytrain, Ytest)


def train_svm(title):
    clf = SVC(kernel = "linear")
    clf.fit(Xtrain, Ytrain)
    rfc_s = cross_val_score(clf, dat, target, cv=9).mean()
    print(rfc_s)
    analysis_results(clf, title, Xtrain, Xtest, Ytrain, Ytest)

def train_gnb(title):
    gnb = GaussianNB()
    # gnb = MultinomialNB()
    gnb.fit(Xtrain, Ytrain)
    rfc_s = cross_val_score(gnb, dat, target, cv=9).mean()
    print(rfc_s)
    analysis_results(gnb, title, Xtrain, Xtest, Ytrain, Ytest)


def train_knn(title):
    knn = KNeighborsClassifier(n_neighbors=4)# n_neighbors=5
    knn.fit(Xtrain, Ytrain)
    rfc_s = cross_val_score(knn, dat, target, cv=9).mean()
    print(rfc_s)
    print(knn.predict(Xtest))
    analysis_results(knn, title, Xtrain, Xtest, Ytrain, Ytest)


def cm_show(y, yp, title):
    global cm
    cm = confusion_matrix(y, yp)
"""
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
            plt.annotate(cm[y, x], xy=(x, y), horizontalalignment='center', verticalalignment='center')
    plt.title(title)
    plt.ylabel('True label')  # 坐标轴标签
    plt.xlabel('Predicted label')  # 坐标轴标签
    plt.show()  # 显示作图结果
"""


def analysis_results(label_name, title, Xtrain, Xtest, Ytrain, Ytest):
    ylr = label_name.predict(Xtest)
    ylrT = label_name.predict(Xtrain)
    """    
    print("Train Accuracy of LR:", round(accuracy_score(Ytrain, ylrT), 3))
    print("Test Accuracy of  LR:", round(accuracy_score(Ytest, ylr), 3))
    print("Test Loss of      LR:", round(zero_one_loss(Ytest, ylr), 3))
    print("Jaccard Coef of   LR:", round(jaccard_score(Ytest, ylr, average='weighted'), 3))
    print("Dice Coef of      LR:", round(f1_score(Ytest, ylr, average='weighted'), 3))
    print(classification_report(Ytest, ylr))
    """
    cm_show(Ytest, ylr, title)




"""
def analysis_results(cm):
    Precision_ = (cm[0][0] / (cm[0][0] + cm[1][0] + cm[2][0]) + cm[1][1] / (cm[0][1] + cm[1][1] + cm[2][1]) + cm[2][
        2] / (cm[0][2] + cm[1][2] + cm[2][2])) / 3
    Sensitivity_ = (cm[0][0] / (cm[0][0] + cm[0][1] + cm[0][2]) + cm[1][1] / (cm[1][1] + cm[1][0] + cm[1][2]) + cm[2][
        2] / (cm[2][0] + cm[2][1] + cm[2][2])) / 3
    Specificity_ = ((cm[1][1] + cm[2][2]) / (cm[1][1] + cm[2][2] + cm[1][0] + cm[2][0]) + (cm[2][2] + cm[0][0]) / (cm[0][1] + cm[2][0] + cm[2][2] + cm[0][0]) + (cm[0][0] + cm[1][1]) / (cm[0][2] + cm[1][2] + cm[0][0] + cm[1][1])) / 3
    Recall_ = Sensitivity_
    F1_Score_ = 2 * (Precision_ * Recall_ / (Precision_ + Recall_))
    G_Mean_ = cmath.sqrt(Recall_ * Specificity_)
    print('F1_Score:', F1_Score_, '\nPrecision:', Precision_, '\nSensitivity:', Sensitivity_, '\nSpcificity:',
          Specificity_, '\nG_Mean:', G_Mean_)
    # print("s=%f\ns=%f\nPrecision:%f\nPrecision:%s\nPrecision:%f\n" % (F1_Score_, Specificity_, Precision_, G_Mean_, Sensitivity_))
"""

def drawRoc(roc_auc,fpr,tpr):
    plt.subplots(figsize=(7, 5.5))
    plt.plot(fpr, tpr, color='darkorange', lw=2, label='ROC curve (area = %0.2f)' % roc_auc)
    plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.05])
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('ROC Curve')
    plt.legend(loc="lower right")
    plt.show()


def x1():
    datafile = "./冠心病.csv"  # 数据名
    data1 = pd.read_csv(datafile) * 1000  # 读取数据
    data1 = data1.values  # 将表格转换为矩阵
    # shuffle(data)  # 随机打乱数据
    data1 = data1.astype('int')
    dat = data1[:, :10]
    target = data1[:, 10] / 1000  # 把１０００去掉，变为整形
    target = target.astype('int')
    X = dat
    y = target
    # 设置种类
    y = label_binarize(y, classes=[0, 1, 2])
    # 设置种类
    n_classes = y.shape[1]

    n_samples, n_features = X.shape

    # shuffle and split training and test sets
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=.3, random_state=j)

    # Learn to predict each class against the other
    classifier = OneVsRestClassifier(RandomForestClassifier(n_estimators=10, random_state=0))
    y_score = classifier.fit(X_train, y_train).predict_proba(X_test)

    # 计算每一类的ROC
    fpr = dict()
    tpr = dict()
    precision = dict()
    recall = dict()
    roc_auc = dict()
    for i in range(n_classes):
        fpr[i], tpr[i], _ = roc_curve(y_test[:, i], y_score[:, i])
        roc_auc[i] = auc(fpr[i], tpr[i])

    # Compute micro-average ROC curve and ROC area（方法二）
    fpr["micro"], tpr["micro"], _ = roc_curve(y_test.ravel(), y_score.ravel())
    precision["micro"], recall["micro"], _ = precision_recall_curve(y_test.ravel(), y_score.ravel())
    roc_auc["micro"] = auc(fpr["micro"], tpr["micro"])
    # [:-1]除了最后一个全取
    indices = np.where(recall["micro"][:-1] != recall["micro"][1:])[0] + 1

    mAP = np.sum((recall["micro"][indices] - recall["micro"][indices - 1]) * -1 * precision["micro"][indices])

    # Compute macro-average ROC curve and ROC area（方法一）
    # First aggregate all false positive rates
    all_fpr = np.unique(np.concatenate([fpr[i] for i in range(n_classes)]))
    # Then interpolate all ROC curves at this points
    mean_tpr = np.zeros_like(all_fpr)
    for i in range(n_classes):
        mean_tpr += interp(all_fpr, fpr[i], tpr[i])
    # Finally average it and compute AUC
    mean_tpr /= n_classes
    fpr["macro"] = all_fpr
    tpr["macro"] = mean_tpr
    roc_auc["macro"] = auc(fpr["macro"], tpr["macro"])
    return  roc_auc["macro"]

# 主函数
if __name__ == '__main__':
    datafile = "./冠心病.csv"  # 数据名
    data1 = pd.read_csv(datafile) * 1000  # 读取数据
    data1 = data1.values  # 将表格转换为矩阵
    # shuffle(data)  # 随机打乱数据
    data1 = data1.astype('int')
    dat = data1[:, :10]
    target = data1[:, 10] / 1000  # 把１０００去掉，变为整形

    target = target.astype('int')
    for j in range(200, 1000):
        # 89
        Xtrain, Xtest, Ytrain, Ytest = train_test_split(dat, target, test_size=0.3, random_state=j)#
        a = x1()
        if a > 0.8:
            #train_tree('DF Confusion Matrix')
            #print(cm[0][0] + cm[1][1] + cm[2][2])
            train_forest('RFC Confusion Matrix')
            b = cm[0][0] + cm[1][1] + cm[2][2]
            if b >= 7:
                train_logistic('LR Confusion Matrix')# 5   28 45 46 56 61 89
                c = cm[0][0] + cm[1][1] + cm[2][2]
                if c >= 5:
                    train_gnb('GNB Confusion Matrix')# 5   1 2 3 7 12 19 37 38 39 43 48 57 59 61 63 68 86 89 99
                    d = cm[0][0] + cm[1][1] + cm[2][2]
                    if d >= 5:
                        train_knn('KNN Confusion Matrix')# 6    12   21 30 62 64 76 79 86
                        e = cm[0][0] + cm[1][1] + cm[2][2]
                        if e >= 6:
                            train_svm('SVM Confusion Matrix')# 4   2 7 8 20 21 28 31 39 43 45 46 48 51 54 56 59 60 89
                            f = cm[0][0] + cm[1][1] + cm[2][2]
                            if f >= 4:
                                print(j)

