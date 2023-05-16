#ifndef _TREE_H_

#define _TREE_H_

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cstdarg>
#include<iostream>
#include<string>
extern char *yytext;
extern int yylineno;//提供当前行数信息
using namespace std;

//变量节点
struct varNode {
	string name;
	string type;
	int num = -1;
	bool useAddress = false;
	string boolString;
};

//函数节点
struct funcNode {
	bool isdefinied = false;
	string name;				//函数名
	string rtype;				//函数返回类型
	vector<varNode> paralist;	//记录形参列表
};

//数组节点
struct arrayNode {
	string name;
	string type;
	int num = -1;
};


//block的内容
class Block {
public:
	funcNode func;	//如果是函数，记录函数名
	bool isfunc = false;//记录是否是函数
	map<string, struct varNode> varMap;		//变量的map
	map<string, struct arrayNode> arrayMap;	//数组的map
	string breakLabelname;
	bool canBreak = false;
};


struct gramTree {
    string content;
    string name;
    int line;       //所在代码行数
    struct gramTree *left;
    struct gramTree *right;
};

extern struct gramTree *root;

//使用va_list处理变参
struct gramTree* create_tree(string name, int num,...);
void eval(struct gramTree *head,int leavel);
char* my_substring(char* s, int begin, int end);
void freeGramTree(gramTree* node);

#endif