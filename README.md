# 给文件夹添加备注

## 简介
在windows下，为你的文件夹添加备注，再也不用为了创建英文名的文件夹，却看不懂内容烦恼了

<img src="./REDME/s-1.png"/>

## 用法


### 将文件夹拖动到此程序
1. 将文件夹拖动到此程序，作为参数运行

<img src="./REDME/2.png"/>

2. 输入备注，完成！

### 直接运行

1. 双击打开这个程序

<img src="./REDME/1-1.png"/>

2. 输入你要备注的文件夹路径，回车

<img src="./REDME/1-2.png"/>

3. 输入备注，完成！

### 如何显示备注？

1. 在“详细信息”栏右键，选择其他

<img src="./REDME/a-1.png"/>

2. 找到“备注”勾选，并确定

<img src="./REDME/a-2.png"/>

## 原理

在Windows下，每个文件夹内都存在一个`desktop.ini`文件，他保存了此文件夹的个性化设置，基础结构如下，`InfoTip`键值就是文件夹的注释，详细解释<a href="https://blog.csdn.net/jiangqin115/article/details/50442138">请点击这儿</a>。

```ini
[.ShellClassInfo]

ConfirmFileOp = 0
; 在对该文件夹移动或删除时提示(1)或不提示(0)“你所删除的文件是系统文件”
NoSharing = 1
; 文件夹被(0)或不被(1)共享；
IconFile = %SystemRoot%\System32\SHELL32.dll
IconIndex = 4
; 文件夹图标路径，.ico .dll .exe等文件，相对路径也或绝对路径
; 图标索引，路径文件下的第几个图标(.ico固定为0)
InfoTip = 备注
; 文件夹的备注
```

用户是看不见`desktop.ini`文件的，因为文件被标记为“隐藏”和“系统文件”，所以正常情况无法查看，需要点击“工具”－“文件夹选项”－“查看”，把“隐藏受保护的操作系统文件(推荐)”和“隐藏已知文件类型的扩展名”前的小勾取消，并选择“显示所有文件和文件夹”

```cpp
SetFileAttributesA(iniFilePath.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
SetFileAttributesA(path.c_str(), FILE_ATTRIBUTE_SYSTEM);
```

这两句代码就是将文件设置为“隐藏”和“系统文件”。