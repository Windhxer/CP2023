#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "tree.hpp"
using namespace std;
treeNode::treeNode(string name, int childrenNum, ...) : name(name), childrenNum(childrenNum)
{
	va_list valist;
	va_start(valist, childrenNum);
	if (childrenNum > 0)
	{
		for (int i = 0; i < childrenNum; i++)
		{
			treeNode *child = va_arg(valist, treeNode *);
			children.push_back(child);
		}
		line = firstChild()->line;
		if (childrenNum == 1)
		{
			content = firstChild()->content;
		}
	}
	else if (childrenNum == 0)
	{
		int line = va_arg(valist, int);
		this->line = line;
		if (name == "CONSTANT_INT")
		{
			int value;
			if (strlen(yytext) > 1 && yytext[0] == '0' && yytext[1] != 'x')
			{
				sscanf(yytext, "%o", &value); // 8进制整数
			}
			else if (strlen(yytext) > 1 && yytext[1] == 'x')
			{
				sscanf(yytext, "%x", &value); // 16进制整数
			}
			else
				value = atoi(yytext); // 10进制整数
			content = to_string(value);
		}
		else if (name == "CONSTANT_DOUBLE")
		{
			content = yytext;
		}
		else if (name == "TRUE")
		{
			content = "true";
		}
		else if (name == "FALSE")
		{
			content = "false";
		}
		else if (name == "STRING_LITERAL")
		{
			content = yytext;
		}
		else
		{
			content = yytext;
		}
	}
}

treeNode *treeNode::firstChild()
{
	if (childrenNum == 0)
	{
		return NULL;
	}
	return children[0];
}

treeNode *treeNode::lastChild()
{
	if (childrenNum == 0)
	{
		return NULL;
	}
	return children.back();
}

treeNode *treeNode::getChild(int index)
{
	if (index >= childrenNum || index < 0)
	{
		return NULL;
	}
	return children[index];
}

string varNode::getRepresentation()
{
	// temp
	if (num < 0)
	{
		return prefix + name;
	}
	else
	{
		if (type.find("array") != string::npos)
        {
            return prefix + "array" + to_string(num);
        }
        return prefix + "var" + to_string(num);
	}
}

void treeNode::printTree(int degree, ofstream &os)
{
	string tab = "";
	for (int i = 0; i < degree; i++)
	{
		tab += "  ";
	}
	if (childrenNum == 0)
	{
		os << tab << name << endl;
	}
	else
	{
		os << tab << name << endl << tab << "{" << endl;
		for (int i = 0; i < childrenNum; i++)
		{
			children[i]->printTree(degree + 1, os);
		}
		os << tab << "}" << endl;
	}
}