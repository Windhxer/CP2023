#include "innerCode.hpp"
innerCode::innerCode()
{
}

void innerCode::addCode(string code)
{
	codeList.push_back(code);
}

void innerCode::printCode()
{
}

string innerCode::createCodeForVar(string name, string op, varNode *node1, varNode *node2)
{
	return name + " := " + node1->getRepresentation() + " " + op + " " + node2->getRepresentation();
}