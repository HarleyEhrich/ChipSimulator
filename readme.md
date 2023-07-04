Hi，欢迎你来看我这个写的一团糟的仓库，我将对本项目进行基本介绍，帮助你了解、二次开发本项目。

## 1. 项目初衷

本质上是为了完成一个能够快速编写扩展、效率还不错的芯片、电路门等不同层次混合仿真模拟的框架。


## 2. 项目结构

项目主要分为4个结构：

1. BasicSDK
2. AbstractConInterface
3. Simulator
4. ReleasedComponent

按照顺序分别介绍

### BasicSDK

作为项目的基础库，包含了项目所需要的基本函数，以及定义了数据连接点（UniConnectionPoint）以及数据连接线（UniLinkLine)。该子项目文件在编译后将被自动安装到SDK文件夹下对应的目录。


### AbstractConInterface

该子项目定义并实现了一个通用的组件(芯片等仿真对象在本项目中的名称)，也确定了一系列的虚函数供后续组件的自定义的实现。该子项目文件在编译后将被自动安装到SDK文件夹下对应的目录。


### Simulator

该子项目为测试软件主体项目，在该子项目实现了一个基本测试环境，以及一个自定义的GraphicsView&Scene。但是不推荐使用该子项目进行二次开发，该子项目存在不少的严重的对象析构问题会导致程序在关闭时产生异常（主要原因为智能指针的滥用）。


### ReleasedComponent

该子项目实现了一些简单组件作为测试用例，如果你想要自己实现一个组件可以参考Qt Plugin的实现过程。该子项目文件在编译后将被自动安装到ComponentPlugin文件夹下对应的目录。


## 3. 三方库

[ThePBone/FlatTabWidget: Animated minimalist tab widget for Qt (github.com)](https://github.com/ThePBone/FlatTabWidget)

[dimkanovikov/WidgetAnimationFramework: Library for animate Qt widgets (github.com)](https://github.com/dimkanovikov/WidgetAnimationFramework/)
