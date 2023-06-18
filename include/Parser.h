#ifndef _PARSER_H
#define _PARSER_H

#include "Scanner.h"
#include <deque>
#include <string>
#include <vector>

using namespace std;

class Parser {
public:
  enum NodeKind {   // NodeKind 枚举类型，列出了在语法分析中可能出现的不同节点种类
    None,   //无节点种类，作为默认值。
    CLASS_K,  //类节点
    CLASS_VAR_DEC_K,  //类变量声明节点
    SUBROUTINE_DEC_K,  //函数声明节点
    BASIC_TYPE_K,   //基本类型节点
    CLASS_TYPE_K,   //类类型节点
    NULL_K,  //空节点
    PARAM_K,   //参数节点
    VAR_DEC_K,   //变量声明节点
    ARRAY_K,   //数组节点
    VAR_K,   //变量节点
    IF_STATEMENT_K,    //条件语句节点（if语句）
    WHILE_STATEMENT_K,   //循环语句节点（while语句）
    CALL_EXPRESSION_K,   //调用表达式节点
    RETURN_STATEMENT_K,   //返回语句节点
    CALL_STATEMENT_K,   //调用语句节点
    BOOL_EXPRESSION_K,   //布尔表达式节点
    FUNCTION_CALL_K,    //函数调用节点
    CONSTRUCTOR_CALL_K,   //构造函数调用节点
    COMPARE_K,    //比较节点
    OPERATION_K,   //操作节点
    BOOL_K,   //布尔节点
    ASSIGN_K,   //赋值节点
    SUBROUTINE_BODY_K,   //函数体节点
    BOOL_CONST_K,   //布尔常量节点
    NEGATIVE_K,    //负数节点
    METHOD_CALL_K,   //方法调用节点
    INT_CONST_K,    //整数常量节点
    CHAR_CONST_K,    //字符常量节点
    STRING_CONST_K,    //字符串常量节点
    KEY_WORD_CONST,   //关键字常量节点
    THIS_K    //this关键字节点
  };
  class TreeNode {  // 嵌套类，表示语法树中的一个节点。（表示词法分析器生成的一个标记）
  public:
    Scanner::Token token;//每个节点包含了一个Scanner::Token对象（表示词法分析器生成的一个标记）
    TreeNode *child[5];  //指向最多5个子节点的指针
    TreeNode *next;      // 指向下一个节点的指针
    NodeKind nodeKind;   //节点的种类（NodeKind）
    TreeNode() {
      nodeKind = None;
      child[0] = child[1] = child[2] = child[3] = child[4] = nullptr;
      next = nullptr;
    }
  };

private:
  vector<string> filenames;  // 存储源文件名的字符串向量
  string currentParserFilename;  //:当前正在解析的文件名
  TreeNode *syntaxTree;   //指向语法树根节点的指针
  Scanner scanner;   //Scanner类的对象，用于词法分析
  bool haveReturnStatement; // 要保证每个函数都有return语句, 即使返回值为void

  Scanner::Token getToken();   // 从缓冲区中取出一个token
  Scanner::Token ungetToken(); // 把上一次取出的token放入到缓冲区中
  deque<Scanner::Token> tokenBuffer1; // 左缓冲区，用于存储从词法分析器获取的标记。
  deque<Scanner::Token> tokenBuffer2; // 右缓冲区，用于存储未使用的标记。
  string getFullName(string name);    // 返回完整的名称，接受一个名称作为参数。
  //一系列私有成员函数，用于解析不同的语法规则，如解析类列表、类定义、类变量声明列表、变量名列表等。
  TreeNode *parseClassList();   //解析类列表
  TreeNode *parseClass();       //解析类定义
  TreeNode *parseClassVarDecList();  //解析类变量声明列表
  TreeNode *parseClassVarDec();    //解析类变量声明
  TreeNode *parseVarNameList();    //解析变量名列表
  TreeNode *parseType();  //解析类型
  TreeNode *parseSubroutineDecList();   //解析函数声明列表
  TreeNode *parseSubroutinDec();  //解析函数声明
  TreeNode *parseParams();   //解析参数
  TreeNode *parseParamList();   //解析参数列表
  TreeNode *parseParam();   //解析参数
  TreeNode *parseSubroutineBody();   //解析函数体
  TreeNode *parseVarDecList();   //解析变量声明列表
  TreeNode *parseVarDec();   //解析变量声明
  TreeNode *parseStatements();   //解析语句列表
  TreeNode *parseStatement();  //解析语句
  TreeNode *parseAssignStatement();   //解析赋值语句
  TreeNode *parseLeftValue();   //解析赋值语句的左值
  TreeNode *parseIfStatement();   //解析条件语句（if语句）
  TreeNode *parseWhileStatement();  //解析循环语句（while语句）
  TreeNode *parseReturnStatement();   //解析返回语句
  TreeNode *parseCallStatement();   //解析调用语句
  TreeNode *parseExpressions();   //解析表达式列表
  TreeNode *parseExpressionList();   //解析表达式列表
  TreeNode *parseExpression();  //解析表达式
  TreeNode *parseBoolExpression();   //解析布尔表达式
  TreeNode *parseAdditiveExpression();   //解析加法表达式
  TreeNode *parseTerm();  //解析项
  TreeNode *parseFactor();   //解析因子
  TreeNode *parsePositiveFactor();   //解析正因子
  TreeNode *parseNotFactor();    //解析非因子
  TreeNode *parseCallExpression();   //解析调用表达式

  void printSyntaxTree(TreeNode *tree);

public:
  Parser(vector<string> &filenames);  //类的构造函数，接受一个字符串向量作为参数，用于初始化 Parser 类的对象。
  bool hasError();   //判断语法分析过程中是否出现错误，并返回布尔值表示是否有错误发生。
  TreeNode *getSyntaxTree();   //获取语法分析生成的语法树（Syntax Tree），返回类型为 TreeNode*，即指向语法树根节点的指针
  void print();
  void parse_program();   //解析程序的入口函数，开始对源代码进行语法分析
  static string getCallerName(string const& fullName);   //静态成员函数，接受一个字符串参数 fullName，返回调用者的名称。
  static string getFunctionName(string const &fullName);   //静态成员函数，接受一个字符串参数 fullName，返回函数的名称。
};

#endif
