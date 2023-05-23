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
	string createCode(string tempname, string op, Node node1, Node node2);
	string createCode(Node node1,Node node2);
	string createCode(Node node);
	string createCode(string form, Node node);

	string getNodeName(Node node);
	string getarrayNodeName(Node node);
};

#endif // !_INNERCODE_H_
