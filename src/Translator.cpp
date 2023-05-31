#include <stdio.h>
#include "Translator.hpp"
#include "innerCode.hpp"
#include "tree.hpp"
#include <cassert>
using namespace std;

Translator::Translator(treeNode* root): root(root) {
	translateInit();
}

Translator::~Translator() {

}

void Translator::printErrorMsg(int line, string msg) {
	printf("ERROR: line %d: %s\n", line, msg);
}

bool Translator::varDefined(string varName) {
	return blockStack.back()->varMap.find(varName) != blockStack.back()->varMap.end();
}

varNode* Translator::createTemp(string type) {
	string tempName = "temp" + innerCode.tempNum++;
	varNode* temp = new varNode(tempName, type);
	blockStack.back()->varMap.insert({tempName, temp});
	return temp;
}

varNode* Translator::createVar(string name, string type, bool flag) {
	if (flag) {
		varNode* var = new varNode(name, type, innerCode.varNum++);
		blockStack.back()->varMap.insert({name, var});
		return var;
	}
	else {
		varNode* var = new varNode(name, type);
		return var;
	}
}

arrayNode* Translator::getArrayNode(string arrayName) {
	for (int i = blockStack.size() - 1; i >= 0; i--) {
		if (blockStack[i]->arrayMap.find(arrayName) != blockStack[i]->arrayMap.end()) {
			return blockStack[i]->arrayMap[arrayName];
		}
	}
	return new arrayNode();
}

varNode* Translator::findVar(string varName) {
	for (int i = blockStack.size() - 1; i >= 0; i--) {
		if (blockStack[i]->varMap.find(varName) != blockStack[i]->varMap.find(varName)) {
			return blockStack[i]->varMap[varName];
		}
	}
	return NULL;
}

void Translator::translateInit() {
	Block* globalBlock = new Block();
	blockStack.push_back(globalBlock);

	funcNode* printNode = new funcNode("print", "void");
	
	varNode* paraNode = new varNode("int");
	printNode->paralist.push_back(paraNode);

	funcPool.insert({"print", printNode});

	// read

	translateProgram(root);
}

void Translator::translateProgram(treeNode* node) {
	if (node->name == "function_definition") {
		translateFunctionDefinition(node);
	}
	else if (node->name == "declaration") {
		translateDeclaration(node);
	}
	else {
		if (node != NULL) {
			for (int i = 0; i < node->childrenNum; i++) {
				translateProgram(node->getChild(i));
			}
		}
	}
}

void Translator::translateDeclaration(treeNode* declaration) {
	treeNode* typeNode = declaration->firstChild();
	if (declaration->getChild(1)->content == ";") {
		return;
	}

	translateInitDeclaratorList(typeNode, declaration->getChild(1));
}

void Translator::translateInitDeclaratorList(treeNode* typeNode, treeNode* initDeclaratorList) {
	if (initDeclaratorList->childrenNum == 1) {
		translateInitDeclarator(typeNode, initDeclaratorList->firstChild());
	}
	else if (initDeclaratorList->childrenNum == 2) {
		translateInitDeclaratorList(typeNode, initDeclaratorList->firstChild());
		translateInitDeclarator(typeNode, initDeclaratorList->getChild(2));
	}
}

void Translator::translateInitDeclarator(treeNode* typeNode, treeNode* initDeclarator) {
	// 无初始化
	if (initDeclarator->childrenNum == 1) {
		translateDeclarator(typeNode, initDeclarator->firstChild());
	}
	// 有初始化
	else if (initDeclarator->childrenNum == 3) {
		translateDeclarator(typeNode, initDeclarator->firstChild(), initDeclarator->lastChild());
	}
}

// 无初始化
void Translator::translateDeclarator(treeNode* typeNode, treeNode* declarator) {
	// 普通变量
	if (declarator->childrenNum == 1) {
		if (typeNode->content == "void") {
			printErrorMsg(typeNode->line, "Variables cannot be declared as void!");
			exit(1);
		}
		treeNode* identifier = declarator->firstChild();
		if (!varDefined(identifier->content)) {
			createVar(identifier->content, typeNode->content, true);
		}
		else {
			printErrorMsg(identifier->line, "Variable redefinition!");
			exit(1);
		}
	}

	// 数组
	else if (declarator->getChild(1)->name == "[") {
		string arrayName = declarator->firstChild()->content;

		varNode* sizeNode = translateAssignmentExpression(declarator->getChild(2));
		if (sizeNode->type != "int") {
			printErrorMsg(declarator->line, "The array size must be an integer!");
			exit(1);
		}
		if (typeNode->content == "int") {
			varNode* temp = createTemp("int");
			varNode* temp1 = createTemp("int");
			innerCode.addCode(temp1->name + " := I4");
			innerCode.addCode(temp->name + " := " + temp1->name + " * " + sizeNode->name);
		}
		else if (typeNode->content == "double") {
			varNode* temp = createTemp("double");
			varNode* temp1 = createTemp("int");
			innerCode.addCode(temp1->name + " := I8");
			innerCode.addCode(temp->name + " := " + temp1->name + " * " + sizeNode->name);
		}
		else if (typeNode->content == "bool") {
			
		}

		arrayNode* array = new arrayNode(arrayName, typeNode->content, innerCode.arrayNum);
		innerCode.addCode("DEC array" + innerCode.arrayNum + ' ' + arrayName);
		innerCode.arrayNum++;
		blockStack.back()->arrayMap.insert({arrayName, array});
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
void Translator::translateDeclarator(treeNode* typeNode, treeNode* declarator, treeNode* initializer) {
	if (declarator->firstChild()->name != "IDENTIFIER") {
		printErrorMsg(declarator->line, "Complex variables cannot be initialized!");
		exit(1);
	}
	
	if (varDefined(declarator->firstChild()->content)) {
		printErrorMsg(declarator->line, "The variable is redefined!");
		exit(1);
	}

	varNode* var = createVar(declarator->firstChild()->content, typeNode->content, true);
	varNode* value = translateAssignmentExpression(initializer->firstChild());
	if (value->type != typeNode->content) {
		printErrorMsg(initializer->line, "Different data types are initialized!");
		exit(1);
	}
	innerCode.addCode(innerCode.createCodeForAssign(var, value));
}

void Translator::translateFunctionDefinition(treeNode* functionDefinition) {
	treeNode* typeSpecifier = functionDefinition->firstChild();
	treeNode* declarator = functionDefinition->getChild(1);
	treeNode* compoundStatement = functionDefinition->lastChild();

	string returnType = typeSpecifier->firstChild()->content;
	string funcName = declarator->firstChild()->firstChild()->content;

	funcNode* tempFunc = NULL;
	// 函数池已存在该函数
	if (funcPool.find(funcName) != funcPool.end()) {
		// 该函数已被定义过，error
		if (funcPool[funcName]->isdefinied) {
			printErrorMsg(functionDefinition->line, "The function is redefined!");
		}
		// 若未被定义，则只是声明，记录下声明时的信息
		tempFunc = funcPool[funcName];
		funcPool.erase(funcPool.find(funcName));
	}
	
	funcNode* func = new funcNode(funcName, returnType);
	func->isdefinied = true;
	funcPool.insert({funcName, func});
	Block* funcBlock = new Block(func);
	blockStack.push_back(funcBlock);

	innerCode.addCode("FUNCTION " + funcName + " :");

	if (declarator->getChild(2)->name == "parameter_list") {
		translateParameterList(functionDefinition->getChild(2), func, true);
	}
	else if (declarator->getChild(2)->name == "identifier_list") {
		printErrorMsg(functionDefinition->line, "The format of the function argument is incorrect!");
		exit(1);
	}

	// 比较声明时和定义时是否相当
	if (tempFunc != NULL) {
		if (tempFunc->returnType != func->returnType) {
			printErrorMsg(functionDefinition->line, "The declaration and definition of the function do not match!");
			exit(1);
		}
		if (tempFunc->paralist.size() != func->paralist.size()) {
			printErrorMsg(functionDefinition->line, "The declaration and definition of the function do not match!");
			exit(1);
		}
		for (int i = 0; i < tempFunc->paralist.size(); i++) {
			if (tempFunc->paralist[i]->type != func->paralist[i]->type) {
				printErrorMsg(functionDefinition->line, "The declaration and definition of the function do not match!");
				exit(1);
			}
		}
	}

	translateCompoundStatement(functionDefinition->lastChild());

	blockStack.pop_back();
}

void Translator::translateParameterList(treeNode* parameterList, funcNode* func, bool isDefinition) {
	if (parameterList->firstChild()->childrenNum == 1) {
		translateParameterDeclaration(parameterList->firstChild(), func, isDefinition);
	}
	else {
		translateParameterList(parameterList->firstChild(), func, isDefinition);
		translateParameterDeclaration(parameterList->lastChild(), func, isDefinition);
	}
}

void Translator::translateParameterDeclaration(treeNode* parameterDeclaration, funcNode* func, bool isDefinition) {
	if (isDefinition) {
		if (parameterDeclaration->childrenNum != 2) {
			printErrorMsg(parameterDeclaration->line, "The format of the function argument is incorrect!");
			exit(1);
		}
		treeNode* typeNode = parameterDeclaration->firstChild();
		if (typeNode->content == "void") {
			printErrorMsg(parameterDeclaration->line, "Function argument type cannot be void!");
			exit(1);
		}
		treeNode* declarator = parameterDeclaration->lastChild();
		if (declarator->childrenNum == 1) {
			varNode* var = createVar(declarator->firstChild()->content, typeNode->content, true);
			funcPool[declarator->firstChild()->content]->paralist.push_back(var);
			innerCode.addCode(innerCode.createCodeForParameter(var));
		}
		else if (declarator->getChild(1)->name == "[") {
			string arrayName = declarator->firstChild()->content;
			varNode* sizeNode = translateAssignmentExpression(declarator->getChild(2));
			if (sizeNode->type != "int") {
				printErrorMsg(declarator->line, "The array size must be an integer!");
				exit(1);
			}
			if (typeNode->content == "int") {
				varNode* temp = createTemp("int");
				varNode* temp1 = createTemp("int");
				innerCode.addCode(temp1->name + " := I4");
				innerCode.addCode(temp->name + " := " + temp1->name + " * " + sizeNode->name);
			}
			else if (typeNode->content == "double") {
				varNode* temp = createTemp("double");
				varNode* temp1 = createTemp("int");
				innerCode.addCode(temp1->name + " := I8");
				innerCode.addCode(temp->name + " := " + temp1->name + " * " + sizeNode->name);
			}
			else if (typeNode->content == "bool") {
			
			}

			arrayNode* array = new arrayNode(arrayName, typeNode->content, innerCode.arrayNum++);
			innerCode.addCode(innerCode.createCodeForParameter(array));
		}
	}
}

varNode* Translator::translateAssignmentExpression(treeNode* assignmentExpression) {
	if (assignmentExpression->childrenNum == 1) {
		return translateLogicalOrExpression(assignmentExpression->firstChild());
	}
	else {
		treeNode* unaryExpression = assignmentExpression->firstChild();
		treeNode* assignmentOperator = assignmentExpression->getChild(1);
		treeNode* assignmentExpression1 = assignmentExpression->lastChild();
		varNode* var = translateUnaryExpression(unaryExpression);
		varNode* valueNode = translateAssignmentExpression(assignmentExpression1);
		if (assignmentOperator->name == "=") {
			innerCode.addCode(innerCode.createCodeForAssign(var, valueNode));
			return var;
		}
		// +=, -+, ...
		else {

		}
	}
}

void Translator::translateCompoundStatement(treeNode* compoundStatement) {
	if (compoundStatement->childrenNum == 2) {
		return;
	}

	translateBlockItemList(compoundStatement->getChild(1));
}

void Translator::translateBlockItemList(treeNode* blockItemList) {
	if (blockItemList->childrenNum == 1) {
		translateBlockItem(blockItemList->firstChild());
	}
	else {
		translateBlockItemList(blockItemList->firstChild());
		translateBlockItem(blockItemList->lastChild());
	}
}

void Translator::translateBlockItem(treeNode* blockItem) {
	if (blockItem->firstChild()->name == "declaration") {
		translateDeclaration(blockItem->firstChild());
	}
	else {
		translateStatement(blockItem->firstChild());
	}
}

void Translator::translateStatement(treeNode* statement) {
	if (statement->firstChild()->name == "labeled_statement") {

	}
	else if (statement->firstChild()->name == "compound_statement") {
		translateCompoundStatement(statement->firstChild());
	}
	else if (statement->firstChild()->name == "expression_statement") {
		translateExpressionStatement(statement->firstChild());
	}
	else if (statement->firstChild()->name == "selection_statement") {
		translateSelectionStatement(statement->firstChild());
	}
	else if (statement->firstChild()->name == "iteration_statement") {
		translateIterationStatement(statement->firstChild());
	}
	else if (statement->firstChild()->name == "jump_statement") {
		translateJumpStatement(statement->firstChild());
	}
}

void Translator::translateExpressionStatement(treeNode* expressionStatement) {
	if (expressionStatement->childrenNum == 2) {
		translateExpression(expressionStatement->firstChild());
	}
}

varNode* Translator::translateExpression(treeNode* expression) {
	if (expression->childrenNum == 1) {
		return translateAssignmentExpression(expression->firstChild());
	}
}

varNode* Translator::translateLogicalOrExpression(treeNode* logicalOrExpression) {
	if (logicalOrExpression->childrenNum == 1) {
		return translateLogicalAndExpression(logicalOrExpression->firstChild());
	}
	else {
		varNode* node1 = translateLogicalOrExpression(logicalOrExpression->firstChild());
		varNode* node2 = translateLogicalAndExpression(logicalOrExpression->lastChild());

		if (node1->type != "bool" || node2->type != "bool") {
			printErrorMsg(logicalOrExpression->line, "Logic or operations can only use Boolean data!");
			exit(1);
		}

		varNode* temp = createTemp("bool");
		innerCode.addCode(innerCode.createCodeForVar(temp->name, "||", node1, node2));

		temp->boolString = node1->getRepresentation() + " || " + node2->getRepresentation();
		return temp;
	}
}

varNode* Translator::translateLogicalAndExpression(treeNode* logicalAndExpression) {
	if (logicalAndExpression->childrenNum == 1) {
		return translateInclusiveOrExpression(logicalAndExpression->firstChild());
	}

	varNode* node1 = translateLogicalAndExpression(logicalAndExpression->firstChild());
	varNode* node2 = translateInclusiveOrExpression(logicalAndExpression->lastChild());
	if (node1->type != "bool" || node2->type != "bool") {
		printErrorMsg(logicalAndExpression->line, "Logic and operations can only use Boolean data!");
		exit(1);
	}

	varNode* temp = createTemp("bool");
	innerCode.addCode(innerCode.createCodeForVar(temp->name, "&&", node1, node2));

	temp->boolString = node1->getRepresentation() + " && " + node2->getRepresentation();
	return temp;
}

varNode* Translator::translateInclusiveOrExpression(treeNode* inclusiveOrExpression) {
	if (inclusiveOrExpression->childrenNum == 1) {
		return translateExclusiveOrExpression(inclusiveOrExpression->firstChild());
	}

	varNode* node1 = translateInclusiveOrExpression(inclusiveOrExpression->firstChild());
	varNode* node2 = translateExclusiveOrExpression(inclusiveOrExpression->lastChild());
	if (node1->type != "int" || node2->type != "int") {
		printErrorMsg(inclusiveOrExpression->line, "Inclusive or operations can only use Integer data!");
		exit(1);
	}

	varNode* temp = createTemp("int");
	innerCode.addCode(innerCode.createCodeForVar(temp->name, "|", node1, node2));

	return temp;
}

varNode* Translator::translateExclusiveOrExpression(treeNode* exclusiveOrExpression) {
	if (exclusiveOrExpression->childrenNum == 1) {
		return translateAndExpression(exclusiveOrExpression->firstChild());
	}

	varNode* node1 = translateExclusiveOrExpression(exclusiveOrExpression->firstChild());
	varNode* node2 = translateAndExpression(exclusiveOrExpression->lastChild());
	if (node1->type != "int" || node2->type != "int") {
		printErrorMsg(exclusiveOrExpression->line, "Exclusive or operations can only use Integer data!");
		exit(1);
	}

	varNode* temp = createTemp("int");
	innerCode.addCode(innerCode.createCodeForVar(temp->name, "^", node1, node2));

	return temp;
}

varNode* Translator::translateAndExpression(treeNode* andExpression) {
	if (andExpression->childrenNum == 1) {
		return translateEqualityExpression(andExpression->firstChild());
	}

	varNode* node1 = translateAndExpression(andExpression->firstChild());
	varNode* node2 = translateEqualityExpression(andExpression->lastChild());
	if (node1->type != "int" || node2->type != "int") {
		printErrorMsg(andExpression->line, "And operations can only use Integer data!");
		exit(1);
	}

	varNode* temp = createTemp("int");
	innerCode.addCode(innerCode.createCodeForVar(temp->name, "&", node1, node2));

	return temp;
}

varNode* Translator::translateEqualityExpression(treeNode* equalityExpression) {
	if (equalityExpression->childrenNum == 1) {
		return translateRelationalExpression(equalityExpression->firstChild());
	}
	
	varNode* node1 = translateEqualityExpression(equalityExpression->firstChild());
	string op = equalityExpression->getChild(1)->name;
	varNode* node2 = translateRelationalExpression(equalityExpression->lastChild());
	// 不支持不同数据类型的比较
	if (node1->type != node2->type) {
		printErrorMsg(equalityExpression->line, "Different types of data!");
		exit(1);
	}
	varNode* temp = createTemp(node1->type);
	temp->boolString = node1->getRepresentation() + " " + op + " " + node2->getRepresentation();
	innerCode.addCode(innerCode.createCodeForVar(temp->name, op, node1, node2));

	return temp;
}

varNode* Translator::translateRelationalExpression(treeNode* relationalExpression) {
	if (relationalExpression->childrenNum == 1) {
		return translateShiftExpression(relationalExpression->firstChild());
	}

	varNode* node1 = translateRelationalExpression(relationalExpression->firstChild());

	string op = relationalExpression->getChild(1)->name;
	if (op == "LE_OP") {
		op = "<=";
	}
	else if (op == "GE_OP") {
		op = ">=";
	}

	varNode* node2 = translateShiftExpression(relationalExpression->lastChild());
	if (node1->type != node2->type) {
		printErrorMsg(relationalExpression->line, "Different types of data!");
		exit(1);
	}

	varNode* temp = createTemp(node1->type);
	temp->boolString = node1->getRepresentation() + " " + op + " " + node2->getRepresentation();
	innerCode.addCode(innerCode.createCodeForVar(temp->name, op, node1, node2));

	return temp;
}

varNode* Translator::translateShiftExpression(treeNode* shiftExpression) {
	if (shiftExpression->childrenNum == 1) {
		return translateAdditiveExpression(shiftExpression->firstChild());
	}
	varNode* node1 = translateShiftExpression(shiftExpression->firstChild());
	string op = shiftExpression->getChild(1)->name;
	if (op == "LEFT_OP") {
		op = "<<";
	}
	else if (op == "RIGHT_OP") {
		op = ">>";
	}
	varNode* node2 = translateAdditiveExpression(shiftExpression->lastChild());
	if (node1->type != "int" ||  node1->type != "int") {
		printErrorMsg(shiftExpression->line, "Shift operations can only use Integer data!");
		exit(1);
	}

	varNode* temp = createTemp("int");
	innerCode.addCode(innerCode.createCodeForVar(temp->name, op, node1, node2));

	return temp;
}

varNode* Translator::translateAdditiveExpression(treeNode* additiveExpression) {
	if (additiveExpression->childrenNum == 1) {
		return translateMultiplicativeExpression(additiveExpression->firstChild());
	}

	varNode* node1 = translateAdditiveExpression(additiveExpression->firstChild());
	string op = additiveExpression->getChild(1)->name;
	varNode* node2 = translateMultiplicativeExpression(additiveExpression->lastChild());
	if (node1->type != node2->type) {
		printErrorMsg(additiveExpression->line, "Different types of data!");
		exit(1);
	}

	varNode* temp = createTemp(node1->type);
	innerCode.addCode(innerCode.createCodeForVar(temp->name, op, node1, node2));

	return temp;
}

varNode* Translator::translateMultiplicativeExpression(treeNode* multiplicativeExpression) {
	if (multiplicativeExpression->childrenNum == 1) {
		return translateUnaryExpression(multiplicativeExpression->firstChild());
	}

	varNode* node1 = translateMultiplicativeExpression(multiplicativeExpression->firstChild());
	string op = multiplicativeExpression->getChild(1)->name;
	varNode* node2 = translateUnaryExpression(multiplicativeExpression->lastChild());
	if (node1->type != node2->type) {
		printErrorMsg(multiplicativeExpression->line, "Different types of data!");
		exit(1);
	}

	varNode* temp = createTemp(node1->type);
	innerCode.addCode(innerCode.createCodeForVar(temp->name, op, node1, node2));

	return temp;
}

varNode* Translator::translateUnaryExpression(treeNode* unaryExpression) {
	if (unaryExpression->childrenNum == 1) {
		return translatePostfixExpression(unaryExpression->firstChild());
	}

	if (unaryExpression->firstChild()->name == "INC_OP") {
		string op = "++";
		varNode* node = translateUnaryExpression(unaryExpression->lastChild());
		if (node->type != "int") {
			printErrorMsg(unaryExpression->line, "Pre-increment(++) operations can only use Integer data!");
			exit(1);
		}

		varNode* temp = createTemp("int");
		innerCode.addCode(temp->name + " := I1");
		if (node->useAddress) {
			innerCode.addCode("*" + node->name + " := *" + node->name + " + " + temp->name);
		}
		else {
			innerCode.addCode(node->getRepresentation()+ " := " + node->getRepresentation() + " + " + temp->name);
		}
		return node;
	}
	else if (unaryExpression->firstChild()->name == "DEC_OP") {
		string op =  "--";
		varNode* node = translateUnaryExpression(unaryExpression->lastChild());
		if (node->type != "int") {
			printErrorMsg(unaryExpression->line, "Pre-decrement(--) operations can only use Integer data!");
			exit(1);
		}

		varNode* temp = createTemp("int");
		innerCode.addCode(temp->name + " := I1");
		if (node->useAddress) {
			innerCode.addCode("*" + node->name + " := *" + node->name + " - " + temp->name);
		}
		else {
			innerCode.addCode(node->getRepresentation() + " := " + node->getRepresentation() + " - " + temp->name);
		}
		return node;
	}
	else if (unaryExpression->firstChild()->name == "unary_operator") {
		string op = unaryExpression->firstChild()->firstChild()->name;
		varNode* node = translateUnaryExpression(unaryExpression->lastChild());
		if (op == "+") {
			if (node->type != "int" && node->type != "double") {
				printErrorMsg(unaryExpression->line, "Operator '+' can only use int or double!");
				exit(1);
			}
			return node;
		}
		else if (op == "-") {
			if (node->type != "int" && node->type != "double") {
				printErrorMsg(unaryExpression->line, "Operator '-' can only be used in int or double!");
				exit(1);
			}

			varNode* temp = createTemp(node->type);
			innerCode.addCode(temp->name + " := I0");

			varNode* temp1 = createTemp(node->type);

			if (node->useAddress) {
				innerCode.addCode(temp1->name + " := " + temp->name + " - *" + node->name);
			}
			else {
				innerCode.addCode(temp1->name + " := " + temp->name + " - " + node->getRepresentation());
			}
			return temp1;
		}
		// ~, !等
		else {

		}
	}
}

varNode* Translator::translatePostfixExpression(treeNode* postfixExpression) {
	if (postfixExpression->childrenNum == 1)  {
		return translatePrimaryExpression(postfixExpression->firstChild());
	}
	// postfix_expression:	postfix_expression  expression ']'
	if (postfixExpression->lastChild()->name == "]") {
		// 暂不考虑二维数组
		if (postfixExpression->firstChild()->childrenNum == 1) {
			varNode* expression = translateExpression(postfixExpression->getChild(2));
			arrayNode* array = getArrayNode(postfixExpression->firstChild()->firstChild()->firstChild()->content);
			if (array->num < 0) {
				printErrorMsg(postfixExpression->line, "Array undefined!");
				exit(1);
			}

			varNode* temp = createTemp(array->type);
			temp->useAddress = true;

			// 暂时只考虑int数组
			if (array->type == "int") {
				varNode* temp1 = createTemp("int");
				varNode* temp2 = createTemp("int");

				innerCode.addCode(temp2->name + " := I4");
				innerCode.addCode(temp1->name + " := " + expression->getRepresentation() + " * " + temp2->name);
				innerCode.addCode(temp->name + " := &" + innerCode.getarrayNodeName(array) + " + " + temp1->getRepresentation());
				return temp;
			}
		}
	}
	// postfix_expression:	postfix_expression '(' ')'
	else if (postfixExpression->lastChild()->name == ")") {
		string funcName = postfixExpression->firstChild()->firstChild()->content;
		if (funcPool.find(funcName) == funcPool.end()) {
			printErrorMsg(postfixExpression->line, "Function " + funcName + " is undefined!");
			exit(1);
		}

		if (postfixExpression->childrenNum == 4) {
			translateArgumentExpressionList(funcPool[funcName], postfixExpression->getChild(2));
		}
		
		funcNode* func = funcPool[funcName];
		if (func->returnType == "void") {
			innerCode.addCode("CALL " + funcName);
		}
		else {
			varNode* temp = createTemp(func->returnType);
			innerCode.addCode(temp->name + " := CALL " + funcName);
		}
	}
	else if (postfixExpression->lastChild()->name == "INC_OP") {

	}
	else if (postfixExpression->lastChild()->name == "DEC_OP") {

	}
}

varNode* Translator::translatePrimaryExpression(treeNode* primaryExpression) {
	if (primaryExpression->firstChild()->name == "IDENTIFIER") {
		varNode* var = findVar(primaryExpression->firstChild()->content);
		if (var == NULL) {
			printErrorMsg(primaryExpression->line, "Variable undefined!");
			exit(1);
		}
		return var;
	}
	else if (primaryExpression->firstChild()->name == "TRUE") {

	}
	else if (primaryExpression->firstChild()->name == "FALSE") {

	}
	else if (primaryExpression->firstChild()->name == "CONSTANT_INT") {
		varNode* temp = createTemp("int");
		innerCode.addCode(temp->name + " := I" + primaryExpression->firstChild()->content);
		return temp;
	}
	else if (primaryExpression->firstChild()->name == "CONSTANT_DOUBLE") {

	}
	else if (primaryExpression->firstChild()->name == "(") {

	}
	
}

void Translator::translateArgumentExpressionList(funcNode* func, treeNode* argumentExpression) {
	int index = func->paralist.size() - 1;
	while (argumentExpression->childrenNum == 3) {
		varNode* expression = translateAssignmentExpression(argumentExpression->lastChild());
		if (index < 0 || func->paralist[index]->type != expression->type) {
			printErrorMsg(argumentExpression->line, "Function argument passing error!");
			exit(1);
		}
		innerCode.addCode(innerCode.createCodeForArgument(expression));
		index--;
		argumentExpression = argumentExpression->firstChild();
	}
	varNode* expression = translateAssignmentExpression(argumentExpression->firstChild());
	if (index != 0 || func->paralist[index]->type != expression->type) {
		printErrorMsg(argumentExpression->line, "Function argument passing error!");
		exit(1);
	}
	innerCode.addCode(innerCode.createCodeForArgument(expression));
}

void Translator::translateSelectionStatement(treeNode* selectionStatement) {

}
void Translator::translateIterationStatement(treeNode* iterationStatement) {

}
void Translator::translateJumpStatement(treeNode* jumpStatement) {

}