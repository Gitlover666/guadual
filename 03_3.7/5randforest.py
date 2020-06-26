"""from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.datasets import load_wine
import pandas as pd  # 导入数据分析库
wine = load_wine()
wine.data
wine.target
datafile = "./冠心病.csv"  # 数据名
data1 = pd.read_csv(datafile) * 1000  # 读取数据
data1 = data1.values  # 将表格转换为矩阵
# shuffle(data)  # 随机打乱数据

dat = data1[:, :10]
target = data1[:, 10]
from sklearn.model_selection import train_test_split
Xtrain, Xtest, Ytrain, Ytest = train_test_split(dat,target,test_size=0.3)
clf = DecisionTreeClassifier(random_state=0)
rfc = RandomForestClassifier(random_state=0)
clf = clf.fit(Xtrain,Ytrain)
rfc = rfc.fit(Xtrain,Ytrain)
score_c = clf.score(Xtest,Ytest)
score_r = rfc.score(Xtest,Ytest)
print(rfc.feature_importances_)
print(rfc.apply(Xtest))
print(rfc.predict(Xtest))
print(rfc.predict_proba(Xtest))
print("Single Tree:{}".format(score_c)
,"Random Forest:{}".format(score_r)
)

from sklearn.model_selection import cross_val_score
import matplotlib.pyplot as plt
rfc = RandomForestClassifier(n_estimators=25)
rfc_s = cross_val_score(rfc,wine.data,wine.target,cv=10)
clf = DecisionTreeClassifier()
clf_s = cross_val_score(clf,wine.data,wine.target,cv=10)
plt.plot(range(1,11),rfc_s,label = "RandomForest")
plt.plot(range(1,11),clf_s,label = "Decision Tree")
plt.legend()
plt.show()


datafile = "./冠心病.csv"  # 数据名
data1 = pd.read_csv(datafile) * 1000  # 读取数据
data1 = data1.values  # 将表格转换为矩阵
# shuffle(data)  # 随机打乱数据

dat = data1[:, :10]
target = data1[:, 10]
rfc_l = []
clf_l = []
for i in range(10):
    rfc = RandomForestClassifier(n_estimators=25)
    rfc_s = cross_val_score(rfc,dat,target,cv=9).mean()
    rfc_l.append(rfc_s)
    clf = DecisionTreeClassifier()
    clf_s = cross_val_score(clf,dat,target,cv=9).mean()
    clf_l.append(clf_s)
plt.plot(range(1,11),rfc_l,label = "Random Forest")
plt.plot(range(1,11),clf_l,label = "Decision Tree")
plt.legend()
plt.show()


superpa = []

rfc = RandomForestClassifier(n_estimators=1,n_jobs=-1,random_state=20)
rfc_s = cross_val_score(rfc,dat,target,cv=9).mean()
superpa.append(rfc_s)
print(max(superpa),(superpa.index(max(superpa)))+1)



from sklearn.linear_model import LogisticRegression as LR
from sklearn.datasets import load_breast_cancer
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
data = load_breast_cancer()
X = data.data
y = data.target
lrl1 = LR(penalty="l1",solver="liblinear",C=0.5,max_iter=1000)
lrl2 = LR(penalty="l2",solver="liblinear",C=0.5,max_iter=1000)
#逻辑回归的重要属性coef_，查看每个特征所对应的参数
lrl1 = lrl1.fit(X,y)
print('l1', lrl1.coef_)
(lrl1.coef_ != 0).sum(axis=1)
lrl2 = lrl2.fit(X,y)
print('l2', lrl2.coef_)

l1 = []
l2 = []
l1test = []
l2test = []
Xtrain, Xtest, Ytrain, Ytest = train_test_split(X,y,test_size=0.3,random_state=420)
for i in np.linspace(0.05,1,19):
    lrl1 = LR(penalty="l1",solver="liblinear",C=i,max_iter=1000)
    lrl2 = LR(penalty="l2",solver="liblinear",C=i,max_iter=1000)
    lrl1 = lrl1.fit(Xtrain,Ytrain)
    l1.append(accuracy_score(lrl1.predict(Xtrain),Ytrain))
    l1test.append(accuracy_score(lrl1.predict(Xtest),Ytest))
    lrl2 = lrl2.fit(Xtrain,Ytrain)
    l2.append(accuracy_score(lrl2.predict(Xtrain),Ytrain))
    l2test.append(accuracy_score(lrl2.predict(Xtest),Ytest))
graph = [l1,l2,l1test,l2test]
color = ["green","black","lightgreen","gray"]
label = ["L1","L2","L1test","L2test"]
plt.figure(figsize=(6,6))
for i in range(len(graph)):
    plt.plot(np.linspace(0.05,1,19),graph[i],color[i],label=label[i])
plt.legend(loc=4) #图例的位置在哪里?4表示，右下角
plt.show()


from sklearn.linear_model import LogisticRegression as LR
import numpy as np
import matplotlib.pyplot as plt

from sklearn.model_selection import cross_val_score
from sklearn.feature_selection import SelectFromModel

LR_ = LR(solver="liblinear",C=0.9,random_state=420)
a = cross_val_score(LR_,dat,target,cv=9).mean()
print(a)
X_embedded = SelectFromModel(LR_,norm_order=1).fit_transform(dat,target)

b = cross_val_score(LR_,X_embedded,target,cv=9).mean()
print(b)
print(X_embedded)



fullx = []
fsx = []
C=np.arange(0.01,10.01,0.5)
for i in C:
    LR_ = LR(solver="liblinear",C=i,random_state=10)
    fullx.append(cross_val_score(LR_,dat,target,cv=9).mean())
    X_embedded = SelectFromModel(LR_,norm_order=1).fit_transform(dat,target)
    fsx.append(cross_val_score(LR_,X_embedded,target,cv=9).mean())
print(max(fsx),C[fsx.index(max(fsx))])
plt.figure(figsize=(20,5))
plt.plot(C,fullx,label="full")
plt.plot(C,fsx,label="feature selection")
plt.xticks(C)
plt.legend()
plt.show()"""
