#include <stdio.h>
#include <iostream>
#include "translator.hpp"
#include "innerCode.hpp"
#include "tree.hpp"
#include <cassert>
using namespace std;

translator::translator(treeNode *root) : root(root)
{
	translateInit();
}

translator::~translator()
{
}

void translator::printErrorMsg(int line, string msg)
{
	printf("ERROR: line %d: %s\n", line, msg.c_str());
}

bool translator::varDefined(string varName)
{
	return blockStack.back()->varMap.find(varName) != blockStack.back()->varMap.end();
}

varNode *translator::createTemp(string type)
{
	string tempName = "temp" + to_string(innerCode.tempNum++);
	varNode *temp = new varNode(tempName, type);
	blockStack.back()->varMap.insert({tempName, temp});
	return temp;
}

varNode *translator::createArray(string name, string type)
{
    varNode *array = new varNode(name, type, innerCode.arrayNum++);
    blockStack.back()->varMap.insert({name, array});
    return array;
}

varNode *translator::createVar(string name, string type)
{
	varNode *var = new varNode(name, type, innerCode.varNum++);
	blockStack.back()->varMap.insert({name, var});
	return var;
}

varNode *translator::findVar(string varName)
{
	for (int i = blockStack.size() - 1; i >= 0; i--)
	{
		if (blockStack[i]->varMap.find(varName) != blockStack[i]->varMap.end())
		{
			return blockStack[i]->varMap[varName];
		}
	}
	return NULL;
}

string translator::getPointerType(treeNode *pointer, string type)
{
	while (pointer->name != "*")
	{
		type = "pointer_" + type;
		pointer = pointer->lastChild();
	}
	return type;
}

string translator::getFuncReturnType()
{
	for (int i = blockStack.size() - 1; i >= 0; i--)
	{
		if (blockStack[i]->isfunc)
		{
			return blockStack[i]->func->returnType;
		}
	}
	return "";
}

string translator::createLabel()
{
	return "label" + to_string(innerCode.labelNum++);
}

void translator::translateInit()
{
	Block *globalBlock = new Block();
	blockStack.push_back(globalBlock);

	funcNode *printfNode = new funcNode("printf", "void");
	printfNode->parameterVariable = true;
	printfNode->paralist.push_back(new varNode("pointer_char"));
	funcPool.insert({"printf", printfNode});

	funcNode *scanfNode = new funcNode("scanf", "void");
	scanfNode->parameterVariable = true;
	scanfNode->paralist.push_back(new varNode("pointer_char"));
	funcPool.insert({"scanf", scanfNode});

	translateProgram(root);
}

void translator::translateProgram(treeNode *node)
{
	if (node->name == "function_definition")
	{
		translateFunctionDefinition(node);
	}
	else if (node->name == "declaration")
	{
		translateDeclaration(node);
	}
	else
	{
		if (node != NULL)
		{
			for (int i = 0; i < node->childrenNum; i++)
			{
				translateProgram(node->getChild(i));
			}
		}
	}
}

void translator::translateDeclaration(treeNode *declaration)
{
	if (declaration->childrenNum == 2)
	{
		return;
	}

	translateInitDeclaratorList(declaration->firstChild(), declaration->getChild(1));
}

void translator::translateInitDeclaratorList(treeNode *typeNode, treeNode *initDeclaratorList)
{
	if (initDeclaratorList->childrenNum == 1)
	{
		translateInitDeclarator(typeNode, initDeclaratorList->firstChild());
	}
	else if (initDeclaratorList->childrenNum == 3)
	{
		translateInitDeclaratorList(typeNode, initDeclaratorList->firstChild());
		translateInitDeclarator(typeNode, initDeclaratorList->lastChild());
	}
}

void translator::translateInitDeclarator(treeNode *typeNode, treeNode *initDeclarator)
{
	// 无初始化
	if (initDeclarator->childrenNum == 1)
	{
		translateDeclarator(typeNode, initDeclarator->firstChild());
	}
	// 有初始化
	else if (initDeclarator->childrenNum == 3)
	{
		translateDeclarator(typeNode, initDeclarator->firstChild(), initDeclarator->lastChild());
	}
}

// 无初始化
void translator::translateDeclarator(treeNode *typeNode, treeNode *declarator)
{
	if (declarator->childrenNum == 1)
	{
		translateDirectDeclarator(typeNode->content, declarator->lastChild());
	}
	else
	{
		translateDirectDeclarator(getPointerType(declarator->firstChild(), typeNode->content), declarator->lastChild());
	}
}

// 有初始化
void translator::translateDeclarator(treeNode *typeNode, treeNode *declarator, treeNode *initializer)
{
	string type;
	if (declarator->childrenNum == 2)
	{
		type = getPointerType(declarator->firstChild(), typeNode->content);
	}
	else
	{
		type = typeNode->content;
	}

	treeNode *directDeclarator = declarator->lastChild();
	if (directDeclarator->childrenNum != 1)
	{
		printErrorMsg(declarator->line, "Complex variables cannot be initialized!");
		exit(1);
	}

	varNode *var = translateDirectDeclarator(type, directDeclarator);
	varNode *value = translateAssignmentExpression(initializer->firstChild());
	if (var->type != value->type)
	{
		printErrorMsg(declarator->line, "Different data types are initialized!");
		exit(1);
	}
	innerCode.addCodeForAssignment(var->getRepresentation(), value->getRepresentation());
}

varNode *translator::translateDirectDeclarator(string type, treeNode *directDeclarator)
{
	// 普通变量
	if (directDeclarator->childrenNum == 1)
	{
		if (type == "void")
		{
			printErrorMsg(directDeclarator->line, "Variables cannot be declared as void!");
			exit(1);
		}
		treeNode *identifier = directDeclarator->firstChild();
		if (varDefined(identifier->content))
		{
			printErrorMsg(identifier->line, "Variable redefinition!");
			exit(1);
		}
		return createVar(identifier->content, type);
	}
	// 数组
	else if (directDeclarator->getChild(1)->name == "[")
	{
		if (directDeclarator->childrenNum == 3)
		{
			printErrorMsg(directDeclarator->line, "Array size not specified!");
			exit(1);
		}
		string arrayName = directDeclarator->firstChild()->content;
		if (varDefined(arrayName))
		{
			printErrorMsg(directDeclarator->line, "Variable redefinition!");
			exit(1);
		}
		varNode *sizeNode = translateAssignmentExpression(directDeclarator->getChild(2));
		if (sizeNode->type != "int")
		{
			printErrorMsg(directDeclarator->line, "The array size must be an integer!");
			exit(1);
		}

		varNode *temp1 = createTemp("int");
		innerCode.addCodeForAssignment(temp1->getRepresentation(), "I" + to_string(varNode::getSize(type)));
		varNode *array = createVar(arrayName, "pointer_" + type);
		innerCode.addCodeForArray(array->getRepresentation(), temp1->getRepresentation(), sizeNode->getRepresentation());
		return array;
	}
}


void translator::translateFunctionDefinition(treeNode *functionDefinition)
{
	treeNode *typeSpecifier = functionDefinition->firstChild();
	treeNode *declarator = functionDefinition->getChild(1);
	treeNode *directDeclarator = declarator->lastChild();
	treeNode *compoundStatement = functionDefinition->lastChild();

	string returnType;
	if (declarator->childrenNum == 2)
	{
		returnType = getPointerType(declarator->firstChild(), typeSpecifier->content);
	}
	else
	{
		returnType = typeSpecifier->firstChild()->content;
	}


	string funcName = directDeclarator->firstChild()->content;

	funcNode *tempFunc = NULL;
	// 函数池已存在该函数
	if (funcPool.find(funcName) != funcPool.end())
	{
		// 该函数已被定义过，error
		if (funcPool[funcName]->isdefinied)
		{
			printErrorMsg(functionDefinition->line, "The function is redefined!");
		}
		// 若未被定义，则只是声明，记录下声明时的信息
		tempFunc = funcPool[funcName];
		funcPool.erase(funcPool.find(funcName));
	}
	funcNode *func = new funcNode(funcName, returnType);
	func->isdefinied = true;
	funcPool.insert({funcName, func});
	Block *funcBlock = new Block(func);
	blockStack.push_back(funcBlock);
	
	innerCode.addCodeForFunction(funcName);
	
	if (directDeclarator->getChild(2)->name == "parameter_list")
	{
		
		translateParameterList(directDeclarator->getChild(2), func, true);
	}
	else if (directDeclarator->getChild(2)->name == "identifier_list")
	{
		printErrorMsg(functionDefinition->line, "The format of the function argument is incorrect!");
		exit(1);
	}
	// 比较声明时和定义时是否相当
	if (tempFunc != NULL)
	{
		if (tempFunc->returnType != func->returnType)
		{
			printErrorMsg(functionDefinition->line, "The declaration and definition of the function do not match!");
			exit(1);
		}
		if (tempFunc->paralist.size() != func->paralist.size())
		{
			printErrorMsg(functionDefinition->line, "The declaration and definition of the function do not match!");
			exit(1);
		}
		for (int i = 0; i < tempFunc->paralist.size(); i++)
		{
			if (tempFunc->paralist[i]->type != func->paralist[i]->type)
			{
				printErrorMsg(functionDefinition->line, "The declaration and definition of the function do not match!");
				exit(1);
			}
		}
	}

	translateCompoundStatement(functionDefinition->lastChild());

	blockStack.pop_back();

	innerCode.addCodeForEnd();
}

void translator::translateParameterList(treeNode *parameterList, funcNode *func, bool isDefinition)
{
	if (parameterList->childrenNum == 1)
	{
		translateParameterDeclaration(parameterList->firstChild(), func, isDefinition);
	}
	else
	{
		translateParameterList(parameterList->firstChild(), func, isDefinition);
		translateParameterDeclaration(parameterList->lastChild(), func, isDefinition);
	}
}

void translator::translateParameterDeclaration(treeNode *parameterDeclaration, funcNode *func, bool isDefinition)
{
	if (isDefinition)
	{
		if (parameterDeclaration->childrenNum == 1 && parameterDeclaration->firstChild()->content == "void")
		{
			return;
		}
		// 不支持只指定数据类型而不指定形参
		if (parameterDeclaration->childrenNum != 2)
		{
			printErrorMsg(parameterDeclaration->line, "The format of the function argument is incorrect!");
			exit(1);
		}

		treeNode *declarator = parameterDeclaration->lastChild();
		string type = parameterDeclaration->firstChild()->content;
		if (declarator->childrenNum == 2)
		{
			type = getPointerType(declarator->firstChild(), type);
		}

		treeNode *directDeclarator = declarator->lastChild();
		if (type == "void")
		{
			printErrorMsg(parameterDeclaration->line, "Function argument type cannot be void!");
			exit(1);
		}

		// 简单数据类型的参数
		if (directDeclarator->childrenNum == 1)
		{
			varNode *var = createVar(directDeclarator->content, type);
			func->paralist.push_back(var);
			innerCode.addCodeForParameter(var->getRepresentation());
		}
		// 数组作为参数，只考虑一维数组
		else if (directDeclarator->getChild(1)->name == "[")
		{
			// 只能是 void fun(int a[]) 的形式
			// 即 declarator:	declarator	'[' ']'
			if (directDeclarator->childrenNum != 3)
			{
				printErrorMsg(parameterDeclaration->line, "Incorrect parameter type!");
				exit(1);
			}
			varNode *array = createVar(directDeclarator->firstChild()->content, "pointer_" + type);
			func->paralist.push_back(array);
			innerCode.addCodeForParameter(array->getRepresentation());
		}
	}
}

varNode *translator::translateAssignmentExpression(treeNode *assignmentExpression)
{
	if (assignmentExpression->childrenNum == 1)
	{
		return translateLogicalOrExpression(assignmentExpression->firstChild());
	}
	else
	{
		varNode *unaryExpressionNode = translateUnaryExpression(assignmentExpression->firstChild());
		varNode *assignmentExpressionNode = translateAssignmentExpression(assignmentExpression->lastChild());
		if (unaryExpressionNode->type == assignmentExpressionNode->type)
		{
			if (assignmentExpression->getChild(1)->firstChild()->name == "=")
			{
				innerCode.addCodeForAssignment(unaryExpressionNode->getRepresentation(), assignmentExpressionNode->getRepresentation());
				return unaryExpressionNode;
			}
			// +=, -+, ...
			else
			{
			}
		}
		else
		{
			printErrorMsg(assignmentExpression->line, "Data type error!");
			exit(1);
		}
	}
}

void translator::translateCompoundStatement(treeNode *compoundStatement)
{
	if (compoundStatement->childrenNum == 2)
	{
		return;
	}

	translateBlockItemList(compoundStatement->getChild(1));
}

void translator::translateBlockItemList(treeNode *blockItemList)
{
	if (blockItemList->childrenNum == 1)
	{
		translateBlockItem(blockItemList->firstChild());
	}
	else
	{
		translateBlockItemList(blockItemList->firstChild());
		translateBlockItem(blockItemList->lastChild());
	}
}

void translator::translateBlockItem(treeNode *blockItem)
{
	if (blockItem->firstChild()->name == "declaration")
	{
		translateDeclaration(blockItem->firstChild());
	}
	else
	{
		translateStatement(blockItem->firstChild());
	}
}

void translator::translateStatement(treeNode *statement)
{
	if (statement->firstChild()->name == "labeled_statement")
	{
	}
	else if (statement->firstChild()->name == "compound_statement")
	{
		translateCompoundStatement(statement->firstChild());
	}
	else if (statement->firstChild()->name == "expression_statement")
	{
		translateExpressionStatement(statement->firstChild());
	}
	else if (statement->firstChild()->name == "selection_statement")
	{
		translateSelectionStatement(statement->firstChild());
	}
	else if (statement->firstChild()->name == "iteration_statement")
	{
		translateIterationStatement(statement->firstChild());
	}
	else if (statement->firstChild()->name == "jump_statement")
	{
		translateJumpStatement(statement->firstChild());
	}
}

varNode *translator::translateExpressionStatement(treeNode *expressionStatement)
{
	if (expressionStatement->childrenNum == 2)
	{
		return translateExpression(expressionStatement->firstChild());
	}
}

varNode *translator::translateExpression(treeNode *expression)
{
	if (expression->childrenNum == 1)
	{
		return translateAssignmentExpression(expression->firstChild());
	}
}

varNode *translator::translateLogicalOrExpression(treeNode *logicalOrExpression)
{
	if (logicalOrExpression->childrenNum == 1)
	{
		return translateLogicalAndExpression(logicalOrExpression->firstChild());
	}
	else
	{
		varNode *node1 = translateLogicalOrExpression(logicalOrExpression->firstChild());
		varNode *node2 = translateLogicalAndExpression(logicalOrExpression->lastChild());

		if (node1->type != "bool" || node2->type != "bool")
		{
			printErrorMsg(logicalOrExpression->line, "Logic or operations can only use Boolean data!");
			exit(1);
		}

		varNode *temp = createTemp("bool");
		innerCode.addCodeForAssignment(temp->getRepresentation(), node1->getRepresentation(), "||", node2->getRepresentation());

		temp->boolString = node1->getRepresentation() + " || " + node2->getRepresentation();
		return temp;
	}
}

varNode *translator::translateLogicalAndExpression(treeNode *logicalAndExpression)
{
	if (logicalAndExpression->childrenNum == 1)
	{
		return translateInclusiveOrExpression(logicalAndExpression->firstChild());
	}

	varNode *node1 = translateLogicalAndExpression(logicalAndExpression->firstChild());
	varNode *node2 = translateInclusiveOrExpression(logicalAndExpression->lastChild());
	if (node1->type != "bool" || node2->type != "bool")
	{
		printErrorMsg(logicalAndExpression->line, "Logic and operations can only use Boolean data!");
		exit(1);
	}

	varNode *temp = createTemp("bool");
	innerCode.addCodeForAssignment(temp->getRepresentation(), node1->getRepresentation(), "&&", node2->getRepresentation());

	temp->boolString = node1->getRepresentation() + " && " + node2->getRepresentation();
	return temp;
}

varNode *translator::translateInclusiveOrExpression(treeNode *inclusiveOrExpression)
{
	if (inclusiveOrExpression->childrenNum == 1)
	{
		return translateExclusiveOrExpression(inclusiveOrExpression->firstChild());
	}

	varNode *node1 = translateInclusiveOrExpression(inclusiveOrExpression->firstChild());
	varNode *node2 = translateExclusiveOrExpression(inclusiveOrExpression->lastChild());
	if (node1->type != "int" || node2->type != "int")
	{
		printErrorMsg(inclusiveOrExpression->line, "Inclusive or operations can only use Integer data!");
		exit(1);
	}

	varNode *temp = createTemp("int");
		innerCode.addCodeForAssignment(temp->getRepresentation(), node1->getRepresentation(), "|", node2->getRepresentation());


	return temp;
}

varNode *translator::translateExclusiveOrExpression(treeNode *exclusiveOrExpression)
{
	if (exclusiveOrExpression->childrenNum == 1)
	{
		return translateAndExpression(exclusiveOrExpression->firstChild());
	}

	varNode *node1 = translateExclusiveOrExpression(exclusiveOrExpression->firstChild());
	varNode *node2 = translateAndExpression(exclusiveOrExpression->lastChild());
	if (node1->type != "int" || node2->type != "int")
	{
		printErrorMsg(exclusiveOrExpression->line, "Exclusive or operations can only use Integer data!");
		exit(1);
	}

	varNode *temp = createTemp("int");
	innerCode.addCodeForAssignment(temp->getRepresentation(), node1->getRepresentation(), "^", node2->getRepresentation());


	return temp;
}

varNode *translator::translateAndExpression(treeNode *andExpression)
{
	if (andExpression->childrenNum == 1)
	{
		return translateEqualityExpression(andExpression->firstChild());
	}

	varNode *node1 = translateAndExpression(andExpression->firstChild());
	varNode *node2 = translateEqualityExpression(andExpression->lastChild());
	if (node1->type != "int" || node2->type != "int")
	{
		printErrorMsg(andExpression->line, "And operations can only use Integer data!");
		exit(1);
	}

	varNode *temp = createTemp("int");
	innerCode.addCodeForAssignment(temp->getRepresentation(), node1->getRepresentation(), "&", node2->getRepresentation());


	return temp;
}

varNode *translator::translateEqualityExpression(treeNode *equalityExpression)
{
	if (equalityExpression->childrenNum == 1)
	{
		return translateRelationalExpression(equalityExpression->firstChild());
	}

	varNode *node1 = translateEqualityExpression(equalityExpression->firstChild());
	string op = equalityExpression->getChild(1)->name;
	varNode *node2 = translateRelationalExpression(equalityExpression->lastChild());
	// 不支持不同数据类型的比较
	if (node1->type != node2->type)
	{
		printErrorMsg(equalityExpression->line, "Different types of data!");
		exit(1);
	}
	varNode *temp = createTemp("bool");
	temp->boolString = node1->getRepresentation() + " " + op + " " + node2->getRepresentation();
	innerCode.addCodeForAssignment(temp->getRepresentation(), node1->getRepresentation(), op, node2->getRepresentation());


	return temp;
}

varNode *translator::translateRelationalExpression(treeNode *relationalExpression)
{
	if (relationalExpression->childrenNum == 1)
	{
		return translateShiftExpression(relationalExpression->firstChild());
	}

	varNode *node1 = translateRelationalExpression(relationalExpression->firstChild());

	string op = relationalExpression->getChild(1)->name;
	if (op == "LE_OP")
	{
		op = "<=";
	}
	else if (op == "GE_OP")
	{
		op = ">=";
	}

	varNode *node2 = translateShiftExpression(relationalExpression->lastChild());
	if (node1->type != node2->type)
	{
		printErrorMsg(relationalExpression->line, "Different types of data!");
		exit(1);
	}

	varNode *temp = createTemp("bool");
	temp->boolString = node1->getRepresentation() + " " + op + " " + node2->getRepresentation();
	innerCode.addCodeForAssignment(temp->getRepresentation(), node1->getRepresentation(), op, node2->getRepresentation());


	return temp;
}

varNode *translator::translateShiftExpression(treeNode *shiftExpression)
{
	if (shiftExpression->childrenNum == 1)
	{
		return translateAdditiveExpression(shiftExpression->firstChild());
	}
	varNode *node1 = translateShiftExpression(shiftExpression->firstChild());
	string op = shiftExpression->getChild(1)->name;
	if (op == "LEFT_OP")
	{
		op = "<<";
	}
	else if (op == "RIGHT_OP")
	{
		op = ">>";
	}
	varNode *node2 = translateAdditiveExpression(shiftExpression->lastChild());
	if (node1->type != "int" || node1->type != "int")
	{
		printErrorMsg(shiftExpression->line, "Shift operations can only use Integer data!");
		exit(1);
	}

	varNode *temp = createTemp("int");
	innerCode.addCodeForAssignment(temp->getRepresentation(), node1->getRepresentation(), op, node2->getRepresentation());


	return temp;
}

varNode *translator::translateAdditiveExpression(treeNode *additiveExpression)
{
	if (additiveExpression->childrenNum == 1)
	{
		return translateMultiplicativeExpression(additiveExpression->firstChild());
	}

	varNode *node1 = translateAdditiveExpression(additiveExpression->firstChild());
	string op = additiveExpression->getChild(1)->name;
	varNode *node2 = translateMultiplicativeExpression(additiveExpression->lastChild());
	if (node1->type != node2->type)
	{
		printErrorMsg(additiveExpression->line, "Different types of data!");
		exit(1);
	}

	varNode *temp = createTemp(node1->type);
	innerCode.addCodeForAssignment(temp->getRepresentation(), node1->getRepresentation(), op, node2->getRepresentation());


	return temp;
}

varNode *translator::translateMultiplicativeExpression(treeNode *multiplicativeExpression)
{
	if (multiplicativeExpression->childrenNum == 1)
	{
		return translateUnaryExpression(multiplicativeExpression->firstChild());
	}

	varNode *node1 = translateMultiplicativeExpression(multiplicativeExpression->firstChild());
	string op = multiplicativeExpression->getChild(1)->name;
	varNode *node2 = translateUnaryExpression(multiplicativeExpression->lastChild());
	if (node1->type != node2->type)
	{
		printErrorMsg(multiplicativeExpression->line, "Different types of data!");
		exit(1);
	}

	varNode *temp = createTemp(node1->type);
	innerCode.addCodeForAssignment(temp->getRepresentation(), node1->getRepresentation(), op, node2->getRepresentation());


	return temp;
}

varNode *translator::translateUnaryExpression(treeNode *unaryExpression)
{
	if (unaryExpression->childrenNum == 1)
	{
		return translatePostfixExpression(unaryExpression->firstChild());
	}

	if (unaryExpression->firstChild()->name == "INC_OP")
	{
		varNode *node = translateUnaryExpression(unaryExpression->lastChild());
		if (node->type != "int")
		{
			printErrorMsg(unaryExpression->line, "Pre-increment(++) operations can only use Integer data!");
			exit(1);
		}

		varNode *temp = createTemp("int");
		innerCode.addCodeForAssignment(temp->getRepresentation(), "I1");
		innerCode.addCodeForAssignment(node->getRepresentation(), node->getRepresentation(), "+", temp->getRepresentation());
		return node;
	}
	else if (unaryExpression->firstChild()->name == "DEC_OP")
	{
		varNode *node = translateUnaryExpression(unaryExpression->lastChild());
		if (node->type != "int")
		{
			printErrorMsg(unaryExpression->line, "Pre-decrement(--) operations can only use Integer data!");
			exit(1);
		}

		varNode *temp = createTemp("int");
		innerCode.addCodeForAssignment(temp->getRepresentation(), "I1");
		innerCode.addCodeForAssignment(node->getRepresentation(), node->getRepresentation(), "-", temp->getRepresentation());
		return node;
	}
	else if (unaryExpression->firstChild()->name == "unary_operator")
	{
		string op = unaryExpression->firstChild()->firstChild()->name;
		varNode *unaryExpressionNode = translateUnaryExpression(unaryExpression->lastChild());
		if (op == "+")
		{
			if (unaryExpressionNode->type != "int" && unaryExpressionNode->type != "double")
			{
				printErrorMsg(unaryExpression->line, "Operator '+' can only use int or double!");
				exit(1);
			}
			return unaryExpressionNode;
		}
		else if (op == "-")
		{
			if (unaryExpressionNode->type != "int" && unaryExpressionNode->type != "double")
			{
				printErrorMsg(unaryExpression->line, "Operator '-' can only be used in int or double!");
				exit(1);
			}

			varNode *temp = createTemp(unaryExpressionNode->type);
			innerCode.addCodeForAssignment(temp->getRepresentation(), "I0");

			varNode *temp1 = createTemp(unaryExpressionNode->type);
			innerCode.addCodeForAssignment(temp1->getRepresentation(), temp->getRepresentation(), "-", unaryExpressionNode->getRepresentation());

			return temp1;
		}
		else if (op == "&")
		{
			varNode *temp = createTemp("pointer_" + unaryExpressionNode->type);
            size_t pos = unaryExpressionNode->getRepresentation().find("*");
            if (pos != string::npos)
            {
                innerCode.addCodeForAssignment(temp->getRepresentation(), unaryExpressionNode->getRepresentation().substr(pos + 1));
            }
            else
            {
			    innerCode.addCodeForAssignment(temp->getRepresentation(), "8&" + unaryExpressionNode->getRepresentation());
            }
			return temp;
		}
		else if (op == "*")
		{
			varNode *temp = createTemp(unaryExpressionNode->type);
            // 地址传递
			innerCode.addCodeForAssignment(temp->getRepresentation(), unaryExpressionNode->getRepresentation());
            if (temp->type.find("pointer") != string::npos)
            {

            }
			temp->representation = to_string(varNode::getSize(varNode::getPointedDataType(unaryExpressionNode->type))) + "*" + temp->getRepresentation();
			temp->type = varNode::getPointedDataType(temp->type);
			return temp;
		}
		// ~, !等
		else
		{
		}
	}
}

varNode *translator::translatePostfixExpression(treeNode *postfixExpression)
{
	if (postfixExpression->childrenNum == 1)
	{
		return translatePrimaryExpression(postfixExpression->firstChild());
	}
	// postfix_expression:	postfix_expression '[' expression ']'
	if (postfixExpression->lastChild()->name == "]")
	{
		// 暂不考虑二维数组
		if (postfixExpression->firstChild()->childrenNum == 1)
		{
			varNode *array = translatePostfixExpression(postfixExpression->firstChild());
			if (array->type.find("pointer") == string::npos)
			{
				printErrorMsg(postfixExpression->line, "This is not an array variable!");
				exit(1);
			}

			string arrayDataType = varNode::getPointedDataType(array->type);
			varNode *expression = translateExpression(postfixExpression->getChild(2));

			// temp->isAddress = true;

			varNode *temp1 = createTemp("int");
			varNode *temp2 = createTemp("int");
			varNode *temp3 = createTemp(array->type);

			innerCode.addCodeForAssignment(temp1->getRepresentation(), "I" + to_string(varNode::getSize(arrayDataType)));
			innerCode.addCodeForAssignment(temp2->getRepresentation(), temp1->getRepresentation(), "*", expression->getRepresentation());
			innerCode.addCodeForAssignment(temp3->getRepresentation(), array->getRepresentation(), "+", temp2->getRepresentation());
			temp3->representation = to_string(varNode::getSize(arrayDataType)) + "*" + temp3->getRepresentation();
			temp3->type = arrayDataType;
			return temp3;
		}
	}
	// postfix_expression:	postfix_expression '(' ')'
	//						postfix_expression '(' argument_expression_list ')'
	else if (postfixExpression->lastChild()->name == ")")
	{
		string funcName = postfixExpression->firstChild()->firstChild()->content;
		// 函数未定义
		if (funcPool.find(funcName) == funcPool.end())
		{
			printErrorMsg(postfixExpression->line, "Function " + funcName + " is undefined!");
			exit(1);
		}

		// postfix_expression::		postfix_expression '(' argument_expression_list ')'
		if (postfixExpression->childrenNum == 4)
		{
			translateArgumentExpressionList(funcPool[funcName], postfixExpression->getChild(2));
		}

		funcNode *func = funcPool[funcName];
		if (func->returnType == "void")
		{
			innerCode.addCodeForCall(funcName);
			return new varNode("void");
		}
		else
		{
			varNode *temp = createTemp(func->returnType);
			innerCode.addCodeForCallAssignment(temp->getRepresentation(), funcName);
			return temp;
		}
	}
	else if (postfixExpression->lastChild()->name == "INC_OP")
	{
		varNode *postfixExpressionNode = translatePostfixExpression(postfixExpression->firstChild());
		if (postfixExpressionNode->type != "int")
		{
			printErrorMsg(postfixExpression->line, "Only integer data can increment!");
			exit(1);
		}

		varNode *temp1 = createTemp("int");
		innerCode.addCodeForAssignment(temp1->getRepresentation(), postfixExpressionNode->getRepresentation());

		varNode *temp2 = createTemp("int");
		innerCode.addCodeForAssignment(temp2->getRepresentation(), "I1");
		innerCode.addCodeForAssignment(postfixExpressionNode->getRepresentation(), postfixExpressionNode->getRepresentation(), "+", temp2->getRepresentation());

		return temp1;
	}
	else if (postfixExpression->lastChild()->name == "DEC_OP")
	{
		varNode *postfixExpressionNode = translatePostfixExpression(postfixExpression->firstChild());
		if (postfixExpressionNode->type != "int")
		{
			printErrorMsg(postfixExpression->line, "Only integer data can increment!");
			exit(1);
		}

		varNode *temp1 = createTemp("int");
		innerCode.addCodeForAssignment(temp1->getRepresentation(), postfixExpressionNode->getRepresentation());

		varNode *temp2 = createTemp("int");
		innerCode.addCodeForAssignment(temp2->getRepresentation(), "I1");
		innerCode.addCodeForAssignment(postfixExpressionNode->getRepresentation(), postfixExpressionNode->getRepresentation(), "-", temp2->getRepresentation());

		return temp1;
	}
}

varNode *translator::translatePrimaryExpression(treeNode *primaryExpression)
{
	if (primaryExpression->firstChild()->name == "IDENTIFIER")
	{
		varNode *var = findVar(primaryExpression->firstChild()->content);
		if (var == NULL)
		{
			printErrorMsg(primaryExpression->line, "Variable undefined!");
			exit(1);
		}
		return var;
	}
	else if (primaryExpression->firstChild()->name == "TRUE")
	{
	}
	else if (primaryExpression->firstChild()->name == "FALSE")
	{
	}
	else if (primaryExpression->firstChild()->name == "CONSTANT_INT")
	{
		varNode *temp = createTemp("int");
		innerCode.addCodeForAssignment(temp->getRepresentation(), "I" + primaryExpression->firstChild()->content);
		return temp;
	}
	else if (primaryExpression->firstChild()->name == "CONSTANT_DOUBLE")
	{
		varNode *temp = createTemp("double");
		innerCode.addCodeForAssignment(temp->getRepresentation(), "F" + primaryExpression->firstChild()->content);

		return temp;
	}
	else if (primaryExpression->firstChild()->name == "CONSTANT_CHAR")
	{
		varNode *temp = createTemp("char");
		innerCode.addCodeForAssignment(temp->getRepresentation(), primaryExpression->firstChild()->content);
		return temp;
	}
	else if (primaryExpression->firstChild()->name == "STRING_LITERAL")
	{
		varNode *temp = createTemp("pointer_char");
		innerCode.addCodeForAssignment(temp->getRepresentation(), primaryExpression->firstChild()->content);
		return temp;
	}
	else if (primaryExpression->firstChild()->name == "(")
	{
		return translateExpression(primaryExpression->getChild(1));
	}
}

void translator::translateArgumentExpressionList(funcNode *func, treeNode *argumentExpressionList)
{
	// 参数不可变
    if (!func->parameterVariable)
	{
        vector<treeNode *> arguments;
        treeNode *treeNodeTemp = NULL;
        for (treeNodeTemp = argumentExpressionList; treeNodeTemp->name != "assignment_expression"; treeNodeTemp = treeNodeTemp->firstChild())
        {
            arguments.insert(arguments.begin(), treeNodeTemp->lastChild());
        }

        if (arguments.size() != func->paralist.size())
        {
            printErrorMsg(argumentExpressionList->line, "Function argument passing error!");
			exit(1);
        }
        for (int i = 0; i < arguments.size(); i++)
        {
            varNode *assignmentExpressionNode = translateAssignmentExpression(arguments[i]);
            if (func->paralist[i]->type != assignmentExpressionNode->type)
            {
    			printErrorMsg(argumentExpressionList->line, "Function argument passing error!");
    			exit(1);
            }
			innerCode.addCodeForArgument(assignmentExpressionNode->getRepresentation());
        }
	}
	// 参数可变
	else
	{
        vector<treeNode *> arguments;
		for (treeNode *temp = argumentExpressionList; temp->name != "assignment_expression"; temp = temp->firstChild())
		{
            arguments.insert(arguments.begin(), temp->lastChild());
		}
		if (arguments.size() < func->paralist.size())
		{
			printErrorMsg(argumentExpressionList->line, "Function argument passing error!");
			exit(1);
		}
		for (int i = 0; i < arguments.size(); i++)
		{
            varNode *assignmentExpressionNode = translateAssignmentExpression(arguments[i]);
            if (i < func->paralist.size() && func->paralist[i]->type != assignmentExpressionNode->type)
            {
    			printErrorMsg(argumentExpressionList->line, "Function argument passing error!");
    			exit(1);
            }
			innerCode.addCodeForArgument(assignmentExpressionNode->getRepresentation());
		}
	}
}

void translator::translateSelectionStatement(treeNode *selectionStatement)
{
	// selection_statement:	IF '(' expression ')' statement
	if (selectionStatement->firstChild()->name == "IF" && selectionStatement->childrenNum == 5)
	{
		Block *newBlock = new Block();
		blockStack.push_back(newBlock);
		varNode *expressionNode = translateExpression(selectionStatement->getChild(2));
		if (expressionNode->type != "bool")
		{
			printErrorMsg(selectionStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}

		string label1 = createLabel();
		string label2 = createLabel();

		innerCode.addCodeForIf(expressionNode->boolString, label1);
		innerCode.addCodeForGoto(label2);

		innerCode.addCodeForLabel(label1);
		translateStatement(selectionStatement->lastChild());
		innerCode.addCodeForLabel(label2);
		blockStack.pop_back();
	}
	// selection_statement:	IF '(' expression ')' statement ELSE statement
	else if (selectionStatement->firstChild()->name == "IF" && selectionStatement->childrenNum == 7)
	{
		Block *newBlock = new Block();
		blockStack.push_back(newBlock);
		varNode *expressionNode = translateExpression(selectionStatement->getChild(2));
		if (expressionNode->type != "bool")
		{
			printErrorMsg(selectionStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}

		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		innerCode.addCodeForIf(expressionNode->boolString, label1);
		innerCode.addCodeForGoto(label2);

		innerCode.addCodeForLabel(label1);
		translateStatement(selectionStatement->getChild(4));

		innerCode.addCodeForGoto(label3);
		blockStack.pop_back();

		Block *elseBlock = new Block();
		blockStack.push_back(elseBlock);

		innerCode.addCodeForLabel(label2);
		translateStatement(selectionStatement->lastChild());

		innerCode.addCodeForLabel(label3);

		blockStack.pop_back();
	}
	else if (selectionStatement->firstChild()->name == "SWITCH")
	{
	}
}
void translator::translateIterationStatement(treeNode *iterationStatement)
{
	if (iterationStatement->firstChild()->name == "WHILE")
	{
		Block *newBlock = new Block(true);
		blockStack.push_back(newBlock);



		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		newBlock->breakLabel = label3;

		innerCode.addCodeForLabel(label1);
		varNode *expressionNode = translateExpression(iterationStatement->getChild(2));
		if (expressionNode->type != "bool")
		{
			printErrorMsg(iterationStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}
		innerCode.addCodeForIf(expressionNode->boolString, label2);
		innerCode.addCodeForGoto(label3);

		innerCode.addCodeForLabel(label2);
		translateStatement(iterationStatement->lastChild());
		innerCode.addCodeForGoto(label1);

		blockStack.pop_back();
		delete newBlock;
		innerCode.addCodeForLabel(label3);
	}
	else if (iterationStatement->firstChild()->name == "DO")
	{
	}
	else if (iterationStatement->firstChild()->name == "FOR" && iterationStatement->childrenNum == 6 && iterationStatement->getChild(2)->name == "expression_statement")
	{
		Block *newBlock = new Block(true);
		blockStack.push_back(newBlock);

		translateExpressionStatement(iterationStatement->getChild(2));

		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		newBlock->breakLabel = label3;

		innerCode.addCodeForLabel(label1);
		varNode *expressionStatementNode = translateExpressionStatement(iterationStatement->getChild(3));
		if (expressionStatementNode->type != "bool")
		{
			printErrorMsg(iterationStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}
		innerCode.addCodeForIf(expressionStatementNode->boolString, label2);
		innerCode.addCodeForGoto(label3);

		innerCode.addCodeForLabel(label2);
		translateStatement(iterationStatement->lastChild());
		innerCode.addCodeForGoto(label1);

		blockStack.pop_back();
		delete newBlock;
		innerCode.addCodeForLabel(label3);
	}
	else if (iterationStatement->firstChild()->name == "FOR" && iterationStatement->childrenNum == 7 && iterationStatement->getChild(2)->name == "expression_statement")
	{
		Block *newBlock = new Block(true);
		blockStack.push_back(newBlock);

		translateExpressionStatement(iterationStatement->getChild(2));


		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		newBlock->breakLabel = label3;

		innerCode.addCodeForLabel(label1);
		varNode *expressionStatementNode = translateExpressionStatement(iterationStatement->getChild(3));
		if (expressionStatementNode->type != "bool")
		{
			printErrorMsg(iterationStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}
		innerCode.addCodeForIf(expressionStatementNode->boolString, label2);
		innerCode.addCodeForGoto(label3);

		innerCode.addCodeForLabel(label2);
		translateStatement(iterationStatement->lastChild());
		translateExpression(iterationStatement->getChild(4));
		innerCode.addCodeForGoto(label1);

		blockStack.pop_back();
		delete newBlock;
		innerCode.addCodeForLabel(label3);
	}
	else if (iterationStatement->firstChild()->name == "FOR" && iterationStatement->childrenNum == 6 && iterationStatement->getChild(2)->name == "declaration")
	{
		Block *newBlock = new Block(true);
		blockStack.push_back(newBlock);

		translateDeclaration(iterationStatement->getChild(2));

		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		newBlock->breakLabel = label3;

		innerCode.addCodeForLabel(label1);
		varNode *expressionStatementNode = translateExpressionStatement(iterationStatement->getChild(3));
		if (expressionStatementNode->type != "bool")
		{
			printErrorMsg(iterationStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}
		innerCode.addCodeForIf(expressionStatementNode->boolString, label2);
		innerCode.addCodeForGoto(label3);

		innerCode.addCodeForLabel(label2);
		translateStatement(iterationStatement->lastChild());
		innerCode.addCodeForGoto(label1);

		blockStack.pop_back();
		delete newBlock;
		innerCode.addCodeForLabel(label3);
	}
	else if (iterationStatement->firstChild()->name == "FOR" && iterationStatement->childrenNum == 7 && iterationStatement->getChild(2)->name == "declaration")
	{
		Block *newBlock = new Block(true);
		blockStack.push_back(newBlock);

		translateDeclaration(iterationStatement->getChild(2));


		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		newBlock->breakLabel = label3;

		innerCode.addCodeForLabel(label1);
		varNode *expressionStatementNode = translateExpressionStatement(iterationStatement->getChild(3));
		if (expressionStatementNode->type != "bool")
		{
			printErrorMsg(iterationStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}
		innerCode.addCodeForIf(expressionStatementNode->boolString, label2);
		innerCode.addCodeForGoto(label3);

		innerCode.addCodeForLabel(label2);
		translateStatement(iterationStatement->lastChild());
		translateExpression(iterationStatement->getChild(4));
		innerCode.addCodeForGoto(label1);

		blockStack.pop_back();
		delete newBlock;
		innerCode.addCodeForLabel(label3);
	}
}
void translator::translateJumpStatement(treeNode *jumpStatement)
{
	if (jumpStatement->firstChild()->name == "GOTO")
	{
	}
	else if (jumpStatement->firstChild()->name == "CONTINUE")
	{
	}
	else if (jumpStatement->firstChild()->name == "BREAK")
	{
		if (!blockStack.back()->canBreak)
		{
			printErrorMsg(jumpStatement->line, "Can not break!");
			exit(1);
		}
		innerCode.addCodeForGoto(blockStack.back()->breakLabel);
	}
	else if (jumpStatement->firstChild()->name == "RETURN" && jumpStatement->childrenNum == 2)
	{
		if (getFuncReturnType() != "void")
		{
			printErrorMsg(jumpStatement->line, "Return data type error!");
			exit(1);
		}
		innerCode.addCodeForReturn();
	}
	else if (jumpStatement->firstChild()->name == "RETURN" && jumpStatement->childrenNum == 3)
	{
		varNode *expression = translateExpression(jumpStatement->getChild(1));
		if (expression->type != getFuncReturnType())
		{
			printErrorMsg(jumpStatement->line, "Return data type error!");
			exit(1);
		}
		innerCode.addCodeForReturn(expression->getRepresentation());
	}
}