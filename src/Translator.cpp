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

// flag 表示需要分配varNum并插入到block中
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
	printfNode->paralist.push_back(new varNode("string"));
	funcPool.insert({"printf", printfNode});

	funcNode *scanfNode = new funcNode("scanf", "void");
	scanfNode->parameterVariable = true;
	scanfNode->paralist.push_back(new varNode("string"));
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
	// 普通变量
	if (declarator->childrenNum == 1)
	{
		// 变量不能是void
		if (typeNode->content == "void")
		{
			printErrorMsg(typeNode->line, "Variables cannot be declared as void!");
			exit(1);
		}
		treeNode *identifier = declarator->firstChild();

		if (varDefined(identifier->content))
		{
			printErrorMsg(identifier->line, "Variable redefinition!");
			exit(1);
		}

		createVar(identifier->content, typeNode->content);
	}

	// 数组
	else if (declarator->getChild(1)->name == "[")
	{
		if (declarator->childrenNum == 3)
		{
			printErrorMsg(declarator->line, "Array size not specified!");
			exit(1);
		}
		string arrayName = declarator->firstChild()->firstChild()->content;
		if (this->varDefined(arrayName))
		{
			printErrorMsg(declarator->line, "Variable redefinition!");
			exit(1);
		}

		varNode *sizeNode = translateAssignmentExpression(declarator->getChild(2));
		if (sizeNode->type != "int")
		{
			printErrorMsg(declarator->line, "The array size must be an integer!");
			exit(1);
		}

		varNode *temp1 = createTemp("int");
		varNode *temp2 = createTemp("int");
		if (typeNode->content == "int")
		{
			innerCode.addCode(temp1->name + " := I4");
		}
		else if (typeNode->content == "double")
		{
			innerCode.addCode(temp1->name + " := I8");
		}
		else if (typeNode->content == "char")
		{
			innerCode.addCode(temp1->name + " := I1");
		}
		else if (typeNode->content == "bool")
		{
		}

		varNode *array = createVar(arrayName, "array_" + typeNode->content);
		// array->isAddress = true;
		innerCode.addCode(temp2->name + " := " + temp1->name + " * " + sizeNode->getRepresentation());
		innerCode.addCode("ARRAY " + array->getRepresentation() + " " + temp2->name);
	}

	// 函数
	// else if (declarator->getChild(1)->name == "(") {
	// 	string funcName = declarator->firstChild()->firstChild()->content;
	// 	if (blockStack.size() != 1) {
	// 		printErrorMsg(declarator->line, "Functions can only be defined globally!");
	// 		exit(1);
	// 	}
	// 	if (findFunc(funcName)) {
	// 		printErrorMsg(declarator->line, "The function is redefined!");
	// 		exit(1);
	// 	}

	// 	funcNode* func = new funcNode(funcName, typeNode->content);

	// 	if (declarator->getChild(2)->name == "parameter_list") {

	// 	}
	// 	else if (declarator->getChild(2)->name == "identifier_list") {

	// 	}
	// 	else {

	// 	}
	// }
}

// 有初始化
void translator::translateDeclarator(treeNode *typeNode, treeNode *declarator, treeNode *initializer)
{
	if (declarator->firstChild()->name != "IDENTIFIER")
	{
		printErrorMsg(declarator->line, "Complex variables cannot be initialized!");
		exit(1);
	}

	if (varDefined(declarator->firstChild()->content))
	{
		printErrorMsg(declarator->line, "The variable is redefined!");
		exit(1);
	}

	varNode *var = createVar(declarator->firstChild()->content, typeNode->content);
	varNode *value = translateAssignmentExpression(initializer->firstChild());
	if (value->type != typeNode->content)
	{
		printErrorMsg(initializer->line, "Different data types are initialized!");
		exit(1);
	}
	innerCode.addCode(innerCode.createCodeForAssign(var, value));
}

void translator::translateFunctionDefinition(treeNode *functionDefinition)
{
	treeNode *typeSpecifier = functionDefinition->firstChild();
	treeNode *declarator = functionDefinition->getChild(1);
	treeNode *compoundStatement = functionDefinition->lastChild();

	string returnType = typeSpecifier->firstChild()->content;
	string funcName = declarator->firstChild()->firstChild()->content;

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

	innerCode.addCode("FUNCTION " + funcName + " :");

	if (declarator->getChild(2)->name == "parameter_list")
	{
		translateParameterList(declarator->getChild(2), func, true);
	}
	else if (declarator->getChild(2)->name == "identifier_list")
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
		if (parameterDeclaration->childrenNum == 1 && parameterDeclaration->firstChild()->firstChild()->name == "VOID")
		{
			return;
		}
		// 不支持只指定数据类型而不指定形参
		if (parameterDeclaration->childrenNum != 2)
		{
			printErrorMsg(parameterDeclaration->line, "The format of the function argument is incorrect!");
			exit(1);
		}

		treeNode *typeNode = parameterDeclaration->firstChild();
		if (typeNode->firstChild()->name == "VOID")
		{
			printErrorMsg(parameterDeclaration->line, "Function argument type cannot be void!");
			exit(1);
		}

		treeNode *declarator = parameterDeclaration->lastChild();

		// 简单数据类型的参数
		if (declarator->childrenNum == 1)
		{
			varNode *var = createVar(declarator->firstChild()->content, typeNode->content);
			func->paralist.push_back(var);
			innerCode.addCode(innerCode.createCodeForParameter(var));
		}
		// 数组作为参数，只考虑一维数组
		else if (declarator->getChild(1)->name == "[")
		{
			// 只能是 void fun(int a[]) 的形式
			// 即 declarator:	declarator	'[' ']'
			if (declarator->childrenNum != 3)
			{
				printErrorMsg(parameterDeclaration->line, "Incorrect parameter type!");
				exit(1);
			}

			varNode *array = createVar(declarator->firstChild()->content, "array_" + typeNode->content);
			innerCode.addCode(innerCode.createCodeForParameter(array));
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
		cout << endl
			 << unaryExpressionNode->type << endl
			 << assignmentExpressionNode->type << endl;
		if (unaryExpressionNode->type == assignmentExpressionNode->type)
		{
			if (assignmentExpression->getChild(1)->firstChild()->name == "=")
			{
				innerCode.addCode(innerCode.createCodeForAssign(unaryExpressionNode, assignmentExpressionNode));
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
		innerCode.addCode(innerCode.createCodeForVar(temp->name, "||", node1, node2));

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
	innerCode.addCode(innerCode.createCodeForVar(temp->name, "&&", node1, node2));

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
	innerCode.addCode(innerCode.createCodeForVar(temp->name, "|", node1, node2));

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
	innerCode.addCode(innerCode.createCodeForVar(temp->name, "^", node1, node2));

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
	innerCode.addCode(innerCode.createCodeForVar(temp->name, "&", node1, node2));

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
	innerCode.addCode(innerCode.createCodeForVar(temp->name, op, node1, node2));

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
	innerCode.addCode(innerCode.createCodeForVar(temp->name, op, node1, node2));

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
	innerCode.addCode(innerCode.createCodeForVar(temp->name, op, node1, node2));

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
	innerCode.addCode(innerCode.createCodeForVar(temp->name, op, node1, node2));

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
	innerCode.addCode(innerCode.createCodeForVar(temp->name, op, node1, node2));

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
		innerCode.addCode(temp->name + " := I1");
		innerCode.addCode(node->getRepresentation() + " := " + node->getRepresentation() + " + " + temp->name);
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
		innerCode.addCode(temp->name + " := I1");
		innerCode.addCode(node->getRepresentation() + " := " + node->getRepresentation() + " - " + temp->name);
		return node;
	}
	else if (unaryExpression->firstChild()->name == "unary_operator")
	{
		string op = unaryExpression->firstChild()->firstChild()->name;
		varNode *node = translateUnaryExpression(unaryExpression->lastChild());
		if (op == "+")
		{
			if (node->type != "int" && node->type != "double")
			{
				printErrorMsg(unaryExpression->line, "Operator '+' can only use int or double!");
				exit(1);
			}
			return node;
		}
		else if (op == "-")
		{
			if (node->type != "int" && node->type != "double")
			{
				printErrorMsg(unaryExpression->line, "Operator '-' can only be used in int or double!");
				exit(1);
			}

			varNode *temp = createTemp(node->type);
			innerCode.addCode(temp->name + " := I0");

			varNode *temp1 = createTemp(node->type);

			innerCode.addCode(temp1->name + " := " + temp->name + " - " + node->getRepresentation());

			return temp1;
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
			if (array->type.substr(0, 5) != "array")
			{
				printErrorMsg(postfixExpression->line, "This is not an array variable!");
				exit(1);
			}

			string arrayDataType = array->type.substr(6);
			varNode *expression = translateExpression(postfixExpression->getChild(2));

			// temp->isAddress = true;

			varNode *temp1 = createTemp("int");
			varNode *temp2 = createTemp("int");
			varNode *temp3 = createTemp(arrayDataType);

			if (arrayDataType == "int")
			{
				innerCode.addCode(temp1->name + " := I4");
			}
			else if (arrayDataType == "double")
			{
				innerCode.addCode(temp1->name + " := I8");
			}
			else if (arrayDataType == "char")
			{
				innerCode.addCode(temp1->name + " := I1");
			}
			innerCode.addCode(temp2->name + " := " + expression->getRepresentation() + " * " + temp1->getRepresentation());
			innerCode.addCode(temp3->name + " := " + array->getRepresentation() + " + " + temp2->getRepresentation());
			temp3->isAddress = true;
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
			innerCode.addCode("CALL " + funcName);
			return new varNode("void");
		}
		else
		{
			varNode *temp = createTemp(func->returnType);
			innerCode.addCode(temp->name + " := CALL " + funcName);
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
		innerCode.addCode(temp1->name + " := " + postfixExpressionNode->getRepresentation());

		varNode *temp2 = createTemp("int");
		innerCode.addCode(temp2->name + " := I1");
		innerCode.addCode(postfixExpressionNode->getRepresentation() + " := " + postfixExpressionNode->getRepresentation() + " + " + temp2->name);

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
		innerCode.addCode(temp1->name + " := " + postfixExpressionNode->getRepresentation());

		varNode *temp2 = createTemp("int");
		innerCode.addCode(temp2->name + " := I1");
		innerCode.addCode(postfixExpressionNode->getRepresentation() + " := " + postfixExpressionNode->getRepresentation() + " - " + temp2->name);

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
		innerCode.addCode(temp->name + " := I" + primaryExpression->firstChild()->content);
		return temp;
	}
	else if (primaryExpression->firstChild()->name == "CONSTANT_DOUBLE")
	{
		varNode *temp = createTemp("double");
		innerCode.addCode(temp->name + " := F" + primaryExpression->firstChild()->content);
		return temp;
	}
	else if (primaryExpression->firstChild()->name == "CONSTANT_CHAR")
	{
		varNode *temp = createTemp("char");
		innerCode.addCode(temp->name + " := " + primaryExpression->firstChild()->content);
		return temp;
	}
	else if (primaryExpression->firstChild()->name == "STRING_LITERAL")
	{
		varNode *temp = createTemp("string");
		innerCode.addCode(temp->name + " := " + primaryExpression->firstChild()->content);
		return temp;
	}
	else if (primaryExpression->firstChild()->name == "(")
	{
	}
}

void translator::translateArgumentExpressionList(funcNode *func, treeNode *argumentExpression)
{
	if (!func->parameterVariable)
	{
		int index = func->paralist.size() - 1;
		treeNode *temp = argumentExpression;
		while (temp->childrenNum == 3)
		{
			varNode *expression = translateAssignmentExpression(temp->lastChild());
			if (index < 0 || func->paralist[index]->type != expression->type)
			{
				printErrorMsg(temp->line, "Function argument passing error!");
				exit(1);
			}
			innerCode.addCode(innerCode.createCodeForArgument(expression));
			index--;
			temp = temp->firstChild();
		}
		varNode *expression = translateAssignmentExpression(temp->firstChild());
		if (index != 0 || func->paralist[index]->type != expression->type)
		{
			printErrorMsg(temp->line, "Function argument passing error!");
			exit(1);
		}
		innerCode.addCode(innerCode.createCodeForArgument(expression));
	}
	// 参数可变
	else
	{
		int argumentNum = 0;
		for (treeNode *temp = argumentExpression; temp->name != "assignment_expression"; argumentNum++, temp = temp->firstChild())
		{
		}
		if (argumentNum < func->paralist.size())
		{
			printErrorMsg(argumentExpression->line, "Function argument passing error!");
			exit(1);
		}
		treeNode *temp = argumentExpression;
		for (int i = 0; i < argumentNum - func->paralist.size(); i++)
		{
			varNode *expression = translateAssignmentExpression(temp->lastChild());
			innerCode.addCode(innerCode.createCodeForArgument(expression));
			temp = temp->firstChild();
		}

		for (int i = func->paralist.size() - 1; i >= 0; i--)
		{
			varNode *expression = translateAssignmentExpression(temp->lastChild());
			if (expression->type != func->paralist[i]->type)
			{
				printErrorMsg(argumentExpression->line, "Function argument passing error!");
				exit(1);
			}
			innerCode.addCode(innerCode.createCodeForArgument(expression));
			temp = temp->firstChild();
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

		innerCode.addCode("IF " + expressionNode->boolString + " GOTO " + label1);

		innerCode.addCode("GOTO " + label2);
		innerCode.addCode("LABEL: " + label1 + " :");
		translateStatement(selectionStatement->lastChild());
		innerCode.addCode("LABEL " + label2 + " :");
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

		innerCode.addCode("IF " + expressionNode->boolString + " GOTO " + label1);
		innerCode.addCode("GOTO " + label2);

		innerCode.addCode("LABEL " + label1 + " :");
		translateStatement(selectionStatement->getChild(5));

		innerCode.addCode("GOTO " + label3);
		blockStack.pop_back();

		Block *elseBlock = new Block();
		blockStack.push_back(elseBlock);

		innerCode.addCode("LABEL " + label2 + " :");
		translateStatement(selectionStatement->lastChild());

		innerCode.addCode("LABEL " + label3 + " :");

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

		varNode *expressionNode = translateExpression(iterationStatement->getChild(2));
		if (expressionNode->type != "bool")
		{
			printErrorMsg(iterationStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}

		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		newBlock->breakLabel = label3;

		innerCode.addCode("LABEL " + label1 + " :");
		innerCode.addCode("IF " + expressionNode->boolString + " GOTO " + label2);
		innerCode.addCode("GOTO " + label3);

		innerCode.addCode("LABEL " + label2 + " :");
		translateStatement(iterationStatement->lastChild());
		innerCode.addCode("GOTO " + label1);

		blockStack.pop_back();
		delete newBlock;
		innerCode.addCode("LABEL " + label3 + " :");
	}
	else if (iterationStatement->firstChild()->name == "DO")
	{
	}
	else if (iterationStatement->firstChild()->name == "FOR" && iterationStatement->childrenNum == 6 && iterationStatement->getChild(2)->name == "expression_statement")
	{
		Block *newBlock = new Block(true);
		blockStack.push_back(newBlock);

		translateExpressionStatement(iterationStatement->getChild(2));
		varNode *expressionStatementNode = translateExpressionStatement(iterationStatement->getChild(3));
		if (expressionStatementNode->type != "bool")
		{
			printErrorMsg(iterationStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}

		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		newBlock->breakLabel = label3;

		innerCode.addCode("LABEL " + label1 + " :");
		innerCode.addCode("IF " + expressionStatementNode->boolString + " GOTO" + label2);
		innerCode.addCode("GOTO " + label3);

		innerCode.addCode("LABEL " + label2 + " :");
		translateStatement(iterationStatement->lastChild());
		innerCode.addCode("GOTO " + label1);

		blockStack.pop_back();
		delete newBlock;
		innerCode.addCode("LABEL " + label3 + " :");
	}
	else if (iterationStatement->firstChild()->name == "FOR" && iterationStatement->childrenNum == 7 && iterationStatement->getChild(2)->name == "expression_statement")
	{
		Block *newBlock = new Block(true);
		blockStack.push_back(newBlock);

		translateExpressionStatement(iterationStatement->getChild(2));
		varNode *expressionStatementNode = translateExpressionStatement(iterationStatement->getChild(3));
		if (expressionStatementNode->type != "bool")
		{
			printErrorMsg(iterationStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}

		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		newBlock->breakLabel = label3;

		innerCode.addCode("LABEL " + label1 + " :");
		innerCode.addCode("IF " + expressionStatementNode->boolString + " GOTO " + label2);
		innerCode.addCode("GOTO " + label3);

		innerCode.addCode("LABEL " + label2 + " :");
		translateStatement(iterationStatement->lastChild());
		translateExpression(iterationStatement->getChild(4));
		innerCode.addCode("GOTO " + label1);

		blockStack.pop_back();
		delete newBlock;
		innerCode.addCode("LABEL " + label3 + " :");
	}
	else if (iterationStatement->firstChild()->name == "FOR" && iterationStatement->childrenNum == 6 && iterationStatement->getChild(2)->name == "declaration")
	{
		Block *newBlock = new Block(true);
		blockStack.push_back(newBlock);

		translateDeclaration(iterationStatement->getChild(2));
		varNode *expressionStatementNode = translateExpressionStatement(iterationStatement->getChild(3));
		if (expressionStatementNode->type != "bool")
		{
			printErrorMsg(iterationStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}

		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		newBlock->breakLabel = label3;

		innerCode.addCode("LABEL " + label1 + " :");
		innerCode.addCode("IF " + expressionStatementNode->boolString + " GOTO" + label2);
		innerCode.addCode("GOTO " + label3);

		innerCode.addCode("LABEL " + label2 + " :");
		translateStatement(iterationStatement->lastChild());
		innerCode.addCode("GOTO " + label1);

		blockStack.pop_back();
		delete newBlock;
		innerCode.addCode("LABEL " + label3 + " :");
	}
	else if (iterationStatement->firstChild()->name == "FOR" && iterationStatement->childrenNum == 7 && iterationStatement->getChild(2)->name == "declaration")
	{
		Block *newBlock = new Block(true);
		blockStack.push_back(newBlock);

		translateDeclaration(iterationStatement->getChild(2));
		varNode *expressionStatementNode = translateExpressionStatement(iterationStatement->getChild(3));
		if (expressionStatementNode->type != "bool")
		{
			printErrorMsg(iterationStatement->line, "Only Boolean expressions are supported!");
			exit(1);
		}

		string label1 = createLabel();
		string label2 = createLabel();
		string label3 = createLabel();

		newBlock->breakLabel = label3;

		innerCode.addCode("LABEL " + label1 + " :");
		innerCode.addCode("IF " + expressionStatementNode->boolString + " GOTO " + label2);
		innerCode.addCode("GOTO " + label3);

		innerCode.addCode("LABEL " + label2 + " :");
		translateStatement(iterationStatement->lastChild());
		translateExpression(iterationStatement->getChild(4));
		innerCode.addCode("GOTO " + label1);

		blockStack.pop_back();
		delete newBlock;
		innerCode.addCode("LABEL " + label3 + " :");
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
	}
	else if (jumpStatement->firstChild()->name == "RETURN" && jumpStatement->childrenNum == 2)
	{
		if (getFuncReturnType() != "void")
		{
			printErrorMsg(jumpStatement->line, "Return data type error!");
			exit(1);
		}
		innerCode.addCode("RETURN");
	}
	else if (jumpStatement->firstChild()->name == "RETURN" && jumpStatement->childrenNum == 3)
	{
		varNode *expression = translateExpression(jumpStatement->getChild(1));
		if (expression->type != getFuncReturnType())
		{
			printErrorMsg(jumpStatement->line, "Return data type error!");
			cout << expression->type << endl;
			exit(1);
		}
		innerCode.addCode(innerCode.createCodeForReturn(expression));
	}
}