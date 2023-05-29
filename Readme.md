# Compiler

## 运行环境

```shell
Distributor ID: Ubuntu
Description:    Ubuntu 22.04.2 LTS
Release:        22.04
```

## 项目简介

jack是一种面向对象语言，常用于vm计算机系统开发。本项目使用C++编写jack编译器。

此编译器的实现包含了以下几个步骤：词法分析、语法分析、语义分析、vm中间代码的生成 和 虚拟机

## [词法分析器](https://github.com/Sweet196/Compiler-parser)

对应文件：`Scanner.cpp`

使用手工编码，识别源程序中的单词(token)；通过扫描之后在`output.txt`中写入程序中的所有token及其kind。其中kind表示token的词性或类型

<img src="https://raw.githubusercontent.com/Sweet196/Picgo-images/main/problems/202305181923217.png" style="zoom: 50%;" />

## 状态转移图
