#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
extern char *yytext;
extern int yylineno; // 提供当前行数信息
using namespace std;

// 变量节点
class varNode
{
public:
	varNode(string type) : type(type) {}
	varNode(string name, string type) : name(name), type(type) {}
	varNode(string name, string type, int num) : name(name), type(type), num(num) {}

	string getRepresentation();

	string name;
	string type;
	int num = -1;
	bool isAddress = false; // 判断指针类型，使其可以判断无struct等语法情况下的指针
	string boolString;		 // 将bool变量囊括进普通变量中
	string prefix = "";
};

// 函数节点
class funcNode
{
public:
	funcNode() {}
	funcNode(string name, string returnType) : name(name), returnType(returnType) {}

	string name;	   // 函数名
	string returnType; // 函数返回类型
	bool isdefinied = false;
	bool parameterVariable = false;
	vector<varNode *> paralist; // 记录形参列表
};

// block的内容
class Block
{
public:
	Block() {}
	Block(bool canBreak): canBreak(canBreak) {}
	Block(funcNode *func): func(func), isfunc(true) {}

	funcNode *func = NULL;			   // 如果是函数，记录函数名
	bool isfunc = false;			   // 记录是否是函数
	map<string, varNode *> varMap;	   // 变量的map
    map<string, varNode *> arrayMap;
	string breakLabel;
	bool canBreak = false;
};

class treeNode
{
public:
	string name;
	string content = "";
	int line = -1; // 所在代码行数
	int childrenNum = 0;
	vector<treeNode *> children; // sibling 是邻居的意思，这个vector用来存孩子

	treeNode(string name, int childrenNum, ...);
	void printTree(int degree, ofstream &os);

	treeNode *firstChild();
	treeNode *lastChild();
	treeNode *getChild(int index);
};
extern treeNode *root;
#endif