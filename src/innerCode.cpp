#include "innerCode.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
innerCode::innerCode()
{
}

void innerCode::addCode(string code)
{
	codeList.push_back(code);
}

void innerCode::printCode(ofstream &os)
{
	for (int i = 0; i < codeList.size(); i++)
	{
		os << codeList[i] << endl;
		cout << codeList[i] << endl;
	}
}

string innerCode::createCodeForVar(string name, string op, varNode *node1, varNode *node2)
{
	return name + " := " + node1->getRepresentation() + " " + op + " " + node2->getRepresentation();
}

string innerCode::createCodeForAssign(varNode *node1, varNode *node2)
{
	return node1->getRepresentation() + " := " + node2->getRepresentation();
}

string innerCode::createCodeForParameter(varNode *node)
{
	return "PARAM " + node->getRepresentation();
}

string innerCode::createCodeForArgument(varNode* node)
{
	return "ARG " + node->getRepresentation();
}

string innerCode::createCodeForReturn(varNode* node)
{
	return "RETURN " + node->getRepresentation();
}