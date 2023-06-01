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

使用手工编码，识别源程序中的单词(token)；通过扫描之后在`output.txt`中写入程序中的所有token及其kind。其中kind表示token的词性或类型。

<img src="https://raw.githubusercontent.com/Sweet196/Picgo-images/main/problems/202305181923217.png" style="zoom: 50%;" />

### 状态转移图

词法规则使用了正则表达式来定义，可以画出状态转移图(FA)。

1、简单的转移图示例

2、标识符，整型和浮点型的转移图

3、字符串的转移图

4、字符的转移图

## 语法分析器

对应文件：`Parser.cpp`

使用递归下降的方法实现

### 语法分析的任务

语法分析具有两个任务

* 判断源程序是否符合语法规则
* 生成抽象语法树

本jack编译器使用了上下文无关文法(BNF)进行定义，如下所示

（具体见[https://github.com/shellphy/jack-compiler](https://github.com/shellphy/jack-compiler)，显示了终结符和非终结符）

```
    program -> classlist
    classlist -> classlist class
               | class
    class -> class ID { classVarDecList subroutineDecList }
    classVarDecList -> classVarDecList classVarDec
             	     |
    classVarDec -> static type varNameList ;
                 | field type varNameList ;
    varNameList -> varNameList , ID
                 | ID
    type -> int
          | float
          | char
          | boolean
          | void
          | ID
    subroutineDecList -> subroutineDecList subroutineDec
                       | 
    subroutineDec -> constructor type ID ( params ) subroutineBody
                   | function type ID ( params ) subroutineBody
                   | method type ID (params ) subroutineBody
    params -> paramList
            | 
    paramList -> paramList , param
               | param
    param -> type ID
    subroutineBody -> { varDecList statements }
    varDecList -> varDecList varDec
                | 
    varDec -> type varNameList ;
    statements -> statements statement
                | 
    statement -> assign_statement
               | if_statement
               | while_statement
               | return_statement
               | call_statement ;
    assign_statement -> leftValue = expression ; 
    leftValue -> ID
               | ID [ expression ]
    if_statement -> if ( expression ) statement
                  | if ( expression ) statement else statement
    while_statement -> while ( expression ) { statement }
    return_statement -> return ; 
                      | return expression ;
    call_statement -> ID ( expressions ) 
                    | ID . ID ( expressions )
    expressions -> expression_list
                 | 
    expression_list -> expression_list , expression
                     | expression
    expression -> expression & boolExpression
                | expression | boolExpression
                | boolExpression
    boolExpression -> additive_expression relational_operator additive_expression
                    | additive_expression
    relational_operator -> <= 
                         | >=
                         | ==
                         | <
                         | >
                         | !=
    additive_expression -> additive_expression + term
                         | additive_expression – term
                         | term    
    term -> term * factor
          | term / factor
          | factor
    factor -> - positive_factor
            | positive_factor
    positive_factor -> ~ not_factor
                     | not_factor
    not_factor -> INT_CONST
                | CHAR_CONST
                | STRING_CONST
                | keywordConstant
                | ID
                | ID [ expression ]
                | call_expression
                | ( expression )
    keywordConstant -> true
                     | false
                     | null
                     | this
    call_expression -> ID ( expression )
                     | ID . ID ( expression )
```
