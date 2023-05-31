#include <stdarg.h>
#include <string.h>
#include "tree.hpp"
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
	if (children.size() == 0)
	{
		return NULL;
	}
	return children[0];
}

treeNode *treeNode::lastChild()
{
	if (children.size() == 0)
	{
		return NULL;
	}
	return children.back();
}