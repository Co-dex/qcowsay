# qcowsay
a little game make by qt5  inspired by xcowsay

> 说明

Qt 弄得类似xcowsay的小程序 可以绘制一张背景透明的图像在桌面上，默认显示3秒
图像透明部分是穿透的（异形窗口），鼠标左键可以拖拽，右键直接关闭程序

> 参数

-i, --image <filepath> 设置自己的图片（背景是透明的）<br>
-hi， --height <height> 设置图片的高度默认500px 宽度会自适应<br>
-t, --time <seconds> 设置显示时间默认3秒
eg
qcowsay.exe -i C:/a.png -hi 500 -t 5
  
> 其他说明

可以在程序相同的文件夹建立一个bat批处理文件达到保存参数的效果。
默认图片自己随意画的比较难看，您可以自己更换或者拉取代码自行替换编译

> 待完善

目前还没办法显示一个气泡的文本框，没找到好的实现方案
距离真的xcowsay 就差一个文本框了 QwQ

> 版权

Free
