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

## 词法分析

对应文件：`Scanner`

识别源程序中的单词(token)；通过扫描之后在`output.txt`中写入程序中的所有token及其kind。其中kind表示token的词性或类型。    

### 状态转移图

词法规则使用了正则表达式来定义，可以画出状态转移图(FA)。状态机转移图中的状态定义如下：

| States definition | Meaning                |
| :---------------- | ---------------------- |
| START_STATE       | 开始状态               |
| ID_STATE          | 标识符状态             |
| INT_STATE         | 整型数状态             |
| CHAR_STATE        | 字符状态               |
| FLOAT_STATE       | 浮点数状态             |
| D_FLOAT_STATE     | 带小数点的浮点数状态   |
| E_FLOAT_STATE     | 科学技术法的浮点数状态 |
| STRING_STATE      | 字符串状态             |
| S_STRING_STATE    | 含有转移字符的字符串   |
| SYMBOL_STATE      | 符号状态               |
| INCOMMENT_STATE   | 注释状态               |
| P_INCOMMENT_STATE | 快要结束注释状态       |
| DONE_STATE        | 结束状态               |
| ERROR_STATE       | 错误状态               |

### TokenType

在`Scanner::Token`结构体中，`kind`表示标记（Token）的类型。它是`Scanner::TokenType`枚举类型的一个成员，用于区分不同类型的标记。

`Scanner::TokenType`枚举类型定义了不同的标记类型，包括：

| Member      | Description | KIND |
| ----------- | ----------- | ---- |
| `KEY_WORD`  | 关键字      | 0    |
| `ID`        | 标识符      | 1    |
| `INT`       | 整型数字    | 2    |
| `BOOL`      | 布尔类型    | 3    |
| `CHAR`      | 字符        | 4    |
| `STRING`    | 字符串      | 5    |
| `SYMBOL`    | 合法的符号  | 6    |
| `NONE`      | 无类型      | 7    |
| `ERROR`     | 错误        | 8    |
| `ENDOFFILE` | 文件结束    | 9    |

### 保留字与关键字

支持以下符号：

| Category  | Classification       | Content                                             |
| --------- | -------------------- | --------------------------------------------------- |
| Keywords  | Class related        | class, constructor, function, method, field, static |
|           | Function related     | int, char, boolean, void, true, false, this         |
|           | Control flow related | if, else, while, return                             |
| Operators | Delimiters           | {, }, (, ), [, ], ., ,, ;                           |
|           | Arithmetic operators | +, -, *, /                                          |
|           | Logical operators    | &,\|,~                                              |
|           | Comparison operators | <, >, =, >=, <=, ==, !=                             |

编写主函数进行测试，可得到词法分析结果：

```c++
#include "Scanner.h"
#include <iostream>

using namespace std;

int main() {
  Scanner scanner;
  scanner.openFile("test.jack");
  Scanner::Token token = scanner.nextToken();
  while (token.kind != Scanner::ENDOFFILE) {
    cout << "[Token]: " << token.lexeme << " [Kind]: " << token.kind << endl;
    token = scanner.nextToken();
  }
  scanner.closeFile();
  return 0;
}
```

<img src="https://raw.githubusercontent.com/Sweet196/Picgo-images/main/problems/202305181923217.png" style="zoom: 50%;" />

## 语法分析

对应文件：`Parser.cpp`
使用递归下降的方法实现
语法分析器有两个任务:
1, 判断源程序是否符合语法规则 
2, 生成抽象语法树

### 语法分析的任务

语法分析具有两个任务

* 判断源程序是否符合语法规则
* 生成抽象语法树

本jack编译器使用了上下文无关文法(BNF)进行定义，如下所示，其中非粗体字表示非终结符, 粗体字表示终结符

<pre>
    program -> classlist
    classlist -> classlist class
               | class
    class -> <strong>class</strong> ID <strong>{</strong> classVarDecList subroutineDecList <strong>}</strong>
    classVarDecList -> classVarDecList classVarDec
             	     |
    classVarDec -> <strong>static</strong> type varNameList <strong>;</strong>
                 | <strong>field</strong> type varNameList <strong>;</strong>
    varNameList -> varNameList <strong>,</strong> ID
                 | ID
    type -> <strong>int</strong>
          | <strong>float</strong>
          | <strong>char</strong>
          | <strong>boolean</strong>
          | <strong>void</strong>
          | ID
    subroutineDecList -> subroutineDecList subroutineDec
                       | 
    subroutineDec -> <strong>constructor</strong> type ID <strong>(</strong> params <strong>)</strong> subroutineBody
                   | <strong>function</strong> type ID <strong>(</strong> params <strong>)</strong> subroutineBody
                   | <strong>method</strong> type ID <strong>(</strong>params <strong>)</strong> subroutineBody
    params -> paramList
            | 
    paramList -> paramList <strong>,</strong> param
               | param
    param -> type ID
    subroutineBody -> <strong>{</strong> varDecList statements <strong>}</strong>
    varDecList -> varDecList varDec
                | 
    varDec -> type varNameList <strong>;</strong>
    statements -> statements statement
                | 
    statement -> assign_statement
               | if_statement
               | while_statement
               | return_statement
               | call_statement <strong>;</strong>
    assign_statement -> leftValue <strong>=</strong> expression <strong>;</strong> 
    leftValue -> ID
               | ID <strong>[</strong> expression <strong>]</strong>
    if_statement -> <strong>if (</strong> expression <strong>)</strong> statement
                  | <strong>if (</strong> expression <strong>)</strong> statement <strong>else</strong> statement
    while_statement -> <strong>while (</strong> expression <strong>) {</strong> statement <strong>}</strong>
    return_statement -> <strong>return ; </strong>
                      | <strong>return</strong> expression <strong>;</strong>
    call_statement -> ID <strong>(</strong> expressions <strong>)</strong> 
                    | ID <strong>.</strong> ID <strong>(</strong> expressions <strong>)</strong>
    expressions -> expression_list
                 | 
    expression_list -> expression_list <strong>,</strong> expression
                     | expression
    expression -> expression <strong>&</strong> boolExpression
                | expression <strong>|</strong> boolExpression
                | boolExpression
    boolExpression -> additive_expression relational_operator additive_expression
                    | additive_expression
    relational_operator -> <strong><=</strong> 
                         | <strong>>=</strong>
                         | <strong>==</strong>
                         | <strong><</strong>
                         | <strong>></strong>
                         | <strong>!=</strong>
    additive_expression -> additive_expression <strong>+</strong> term
                         | additive_expression <strong>–</strong> term
                         | term    
    term -> term <strong>*</strong> factor
          | term <strong>/</strong> factor
          | factor
    factor -> <strong>-</strong> positive_factor
            | positive_factor
    positive_factor -> <strong>~</strong> not_factor
                     | not_factor
    not_factor -> <strong>INT_CONST</strong>
                | <strong>CHAR_CONST</strong>
                | <strong>STRING_CONST</strong>
                | keywordConstant
                | ID
                | ID <strong>[</strong> expression <strong>]</strong>
                | call_expression
                | <strong>(</strong> expression <strong>)</strong>
    keywordConstant -> <strong>true</strong>
                     | <strong>false</strong>
                     | <strong>null</strong>
                     | <strong>this</strong>
    call_expression -> ID <strong>(</strong> expression <strong>)</strong>
                     | ID <strong>.</strong> ID <strong>(</strong> expression <strong>)</strong>
</pre>
## 语义分析

## 中间代码生成

## 总结与展望
