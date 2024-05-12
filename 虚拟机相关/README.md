# 虚拟机使用中遇到的问题及解决方案
## VBox
### 1. 图像化界面异常
**问题描述：**
虚拟机内部窗口无法拖动且窗口右上角三个功能按钮无法使用或消失，如火狐浏览器只有关闭窗口可以使用，终端窗口则完全看不到按钮，且GUI最上方正在运行的程序面板也消失
**解决方案：**
执行如下代码
 `  sudo apt install meatcity`
 ` metacity replace`
### 2.pip下载安装python库速度慢问题
 **问题描述：**
使用pip命令安装一些库时由于是国外源导致下载速度慢，耗时久
**解决方案：**
1. **临时手段**
使用清华或是阿里的源进行下载 ，在下载相关库的代码中添加如下结构的代码部分：
```
pip install XXX -i https://pypi.tuna.tsinghua.edu.cn/simple  清华源
pip install XXX -i http://mirrors.aliyun.com/pypi/simple --trusted-host mirrors.aliyun.com  阿里源
```
其中`XXX`为要安装的包
2. **全局手段**
|Linux 用户|Windows 用户|
|--|--|
|修改 ~/.pip/pip.conf 文件，没有就新建一个，写入以下内容：|修改 c:\Users\你的用户名\pip\pip.ini，没有就新建一个|
|```[global] index-url = http://mirrors.aliyun.com/pypi/simple/``` |```[global]index-url = http://mirrors.aliyun.com/pypi/simple/```|
|根据需要选清华源或者阿里源[global]和[install]要单独一行|根据需要选清华源或者阿里源[global]和[install]要单独一行|
| ```[install]trusted-host=mirrors.aliyun.com```|```[install]trusted-host=mirrors.aliyun.com```|