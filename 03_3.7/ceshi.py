from matplotlib import pyplot as plt
import random
from matplotlib import font_manager

my_font1 = font_manager.FontProperties(fname="/usr/share/fonts/opentype/noto/NotoSansCJK-Bold.ttc")
my_font2 = font_manager.FontProperties(fname="/usr/share/fonts/truetype/arphic/ukai.ttc")
x = range(11, 31)
# y = [random.randint(20, 35) for i in range(120)]
y = [1, 0, 1, 1, 2, 4, 3, 2, 3, 4, 4, 5, 6, 5, 4, 3, 3, 1, 1, 1]
y1 = [1, 0, 3, 1, 2, 2, 3, 3, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1]
# 控制表格大小以及清晰度
plt.figure(figsize=(20, 10), dpi=80)
# 支持各种颜色，可以百度色号，以及风格
plt.plot(x, y, label="自己", color='r', linestyle='--')
plt.plot(x, y1, label="舍友")
# _xtick_labels = ["10点{}分".format(i) for i in range(60)]
# _xtick_labels += ["11点{}分".format(i-60) for i in range(60, 120)]

_xtick_labels = ["{}岁".format(i) for i in range(11, 31)]
# 调整x轴，rotation旋转，fontproperties是设置字体
plt.xticks(x, _xtick_labels, rotation=45, fontproperties=my_font2)
plt.grid()
# x,y轴 title标签名称
plt.xlabel("年龄", fontproperties=my_font1, size=16)
plt.ylabel("数量", fontproperties=my_font1, size=16)
plt.title("11到30交女朋友数量", fontproperties=my_font1, size=16)
# 设置图例，第一个参数字体，第二位置
plt.legend(prop=my_font1, loc='best')

plt.show()

