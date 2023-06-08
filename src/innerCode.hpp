#ifndef _INNERCODE_H_
#define _INNERCODE_H_

#include <iostream>
#include <fstream>
#include "tree.hpp"
#include <string>
extern treeNode* root;

using namespace std;

class innerCode {
private:
	vector<string> codeList;

public:
	int tempNum = 0;
	int varNum = 0;
	int labelNum = 0;
	int arrayNum = 0;

	innerCode();
	void addCode(string code);
	void printCode(ofstream &os);
	void addCodeForAssignment(string destination, string source);
	void addCodeForAssignment(string destination, string source1, string op, string source2);
	void addCodeForParameter(string parameter);
	void addCodeForArgument(string argument);
	void addCodeForArray(string arrayName, string step, string size);
	void addCodeForFunction(string funcName);
	void addCodeForEnd();
	void addCodeForCall(string funcName);
	void addCodeForCallAssignment(string destination, string funcName);
	void addCodeForIf(string condition, string label);
	void addCodeForGoto(string label);
	void addCodeForLabel(string label);
	void addCodeForReturn();
	void addCodeForReturn(string data);

	string createCodeForVar(string name, string op, varNode* node1, varNode* node2);
	string createCodeForAssign(varNode* node1, varNode* node2);
	string createCodeForParameter(varNode* node); // 描述函数参数（形参）
	string createCodeForReturn(varNode* node);
	string createCodeForArgument(varNode* node); // 描述调用函数的实参
};

#endif // !_INNERCODE_H_
