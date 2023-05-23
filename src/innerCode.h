#ifndef _INNERCODE_H_
#define _INNERCODE_H_

#include <iostream>
#include "tree.h"
#include<string>
extern struct treeNode* root;

using namespace std;

class InnerCode {
private:
	vector<string> codeList;

public:
	int tempNum = 0;
	int varNum = 0;
	int labelNum = 0;
	int arrayNum = 0;

	InnerCode();
	void addCode(string);
	void printCode();
	//面向var的代码生成重载
	string createCode(string tempname, string op, Node node1, Node node2);
	//面向assign的代码生成重载
	string createCode(Node node1,Node node2);
	//面向Parameter的代码生成重载
	string createCode(Node node);
	//面向return与arguments的生成重载，使用时form参数填入“RETURN”与“ARG”
	string createCode(string form, Node node);

	//获取节点名称,form 填入“VAR”与“ARRAY”进行选择
	string getNodeName(string form , Node node);
};

#endif // !_INNERCODE_H_
