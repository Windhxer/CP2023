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

void innerCode::addCodeForAssignment(string destination, string source)
{
	addCode(destination + " := " + source);
}
void innerCode::addCodeForAssignment(string destination, string source1, string op, string source2)
{
	addCode(destination + " := " + source1 + " " + op + " " + source2);
}
void innerCode::addCodeForParameter(string parameter)
{
	addCode("PARAM " + parameter);
}
void innerCode::addCodeForArgument(string argument)
{
	addCode("ARG " + argument);
}
void innerCode::addCodeForArray(string arrayName, string step, string size)
{
	addCode("ARRAY " + arrayName + " " + step + " * " + size);
}

void innerCode::addCodeForFunction(string funcName)
{
	addCode("FUNCTION " + funcName);
}

void innerCode::addCodeForEnd()
{
	addCode("END");
}

void innerCode::addCodeForCall(string funcName)
{
	addCode("CALL " + funcName);
}

void innerCode::addCodeForCallAssignment(string destination, string funcName)
{
	addCode(destination + " := CALL " + funcName);
}

void innerCode::addCodeForIf(string condition, string label)
{
	addCode("IF " + condition + " GOTO " + label);
}

void innerCode::addCodeForGoto(string label)
{
	addCode("GOTO " + label);
}

void innerCode::addCodeForLabel(string label)
{
	addCode("LABEL " + label);
}

void innerCode::addCodeForReturn()
{
	addCode("RETURN");
}

void innerCode::addCodeForReturn(string data)
{
	addCode("RETURN " + data);
}