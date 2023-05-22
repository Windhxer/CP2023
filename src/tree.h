#ifndef _TREE_H_

#define _TREE_H_

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cstdarg>
#include<iostream>
#include<string>
#include<vector>
#include<map>
extern char *yytext;
extern int yylineno;//提供当前行数信息
using namespace std;

//变量节点
struct varNode {
	string name;
	string type;
	int num = -1;
	bool useAddress = false;	//判断指针类型，使其可以判断无struct等语法情况下的指针
	string boolString;			//将bool变量囊括进普通变量中
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

class Node{
public:
	Node(void) { 
		Type = EMPTY;
		var = NULL;
		func = NULL;
		array = NULL;
	}
	Node(varNode * node1) { 
		var = node1;
		Type = VAR;
	}
	Node(arrayNode * node1) { 
		array = node1;
		Type = ARRAY;
	}
	Node(funcNode * node1) { 
		func = node1;
		Type = FUNC;
	}

	varNode *retVar(void) { return (Type == VAR) ? var : NULL; }
	arrayNode *retArray(void) { return (Type == ARRAY) ? array : NULL; }
	funcNode *retFunc(void) { return (Type == FUNC) ? func : NULL; }
	string retType(void) {
		switch (Type)
		{
		case VAR:
			return "VAR";
			break;
		case FUNC:
			return "FUNC";
			break;
		case ARRAY:
			return "ARRAY";
			break;
		default:
			return "EMPTY";
			break;
		}
	}
private:
	varNode * var;
	arrayNode * array;
	funcNode * func;
	enum {
			FUNC,
			ARRAY,
			VAR,
			EMPTY
		} Type;
};

//block的内容
class Block {
public:
	funcNode func;	//如果是函数，记录函数名
	bool isfunc = false;//记录是否是函数
	map<string, Node> varMap;		//变量的map
	map<string, Node> arrayMap;	//数组的map
	string breakLabelname;
	bool canBreak = false;
};

struct gramTree {
    string content;
    string name;
    int line;       //所在代码行数
    vector<struct gramTree *> sibs;
	struct gramTree *parent;
};

extern struct gramTree *root;

//使用va_list处理变参
struct gramTree* create_tree(string name, int num,...);
void eval(struct gramTree *head,int leavel);
char* my_substring(char* s, int begin, int end);
void freeGramTree(gramTree* node);

#endif