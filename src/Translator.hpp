#ifndef _TRANSLATE_HPP_
#define _TRANSLATE_HPP_

#include <iostream>
#include <map>
#include <vector>
#include "tree.hpp"
#include "innerCode.hpp"
using namespace std;

class Translator{
public:
	Translator(treeNode* root);	//构造函数
	~Translator();	//析构函数

private:
	void printErrorMsg(int line, string msg);
	bool varDefined(string varName);
	varNode* createTemp(string type);
	varNode* createVar(string name, string type, bool flag);
	arrayNode* getArrayNode(string arrayName);
	varNode* findVar(string varName);

	void translateInit();
	void translateProgram(treeNode* node);
	void translateDeclaration(treeNode* declaration);
	void translateInitDeclaratorList(treeNode* typeNode, treeNode* initDeclaratorList);
	void translateInitDeclarator(treeNode* typeNode, treeNode* initDeclarator);
	void translateDeclarator(treeNode* typeNode, treeNode* declarator);
	void translateDeclarator(treeNode* typeNode, treeNode* declarator, treeNode* initializer);
	void translateFunctionDefinition(treeNode* functionDefinition);
	void translateParameterList(treeNode* parameterList, funcNode* func, bool isDefinition);
	void translateParameterDeclaration(treeNode* parameterDeclaration, funcNode* func, bool isDefinition);
	varNode* translateAssignmentExpression(treeNode* assignmentExpression);
	void translateCompoundStatement(treeNode* compoundStatement);
	void translateBlockItemList(treeNode* blockItemList);
	void translateBlockItem(treeNode* blockItem);
	void translateStatement(treeNode* statement);
	void translateExpressionStatement(treeNode* expressionStatement);
	varNode* translateExpression(treeNode* expression);
	varNode* translateLogicalOrExpression(treeNode* logicalOrExpression);
	varNode* translateLogicalAndExpression(treeNode* logicalAndExpression);
	varNode* translateInclusiveOrExpression(treeNode* inclusiveOrExpression);
	varNode* translateExclusiveOrExpression(treeNode* exclusiveOrExpression);
	varNode* translateAndExpression(treeNode* andExpression);
	varNode* translateEqualityExpression(treeNode* equalityExpression);
	varNode* translateRelationalExpression(treeNode* relationalExpression);
	varNode* translateShiftExpression(treeNode* shiftExpression);
	varNode* translateAdditiveExpression(treeNode* additiveExpression);
	varNode* translateMultiplicativeExpression(treeNode* multiplicativeExpression);
	varNode* translateUnaryExpression(treeNode* unaryExpression);
	varNode* translatePostfixExpression(treeNode* postfixExpression);
	varNode* translatePrimaryExpression(treeNode* primaryExpression);
	void translateArgumentExpressionList(funcNode* func, treeNode* argumentExpression);
	void translateSelectionStatement(treeNode* selectionStatement);
	void translateIterationStatement(treeNode* iterationStatement);
	void translateJumpStatement(treeNode* jumpStatement);

	map<string, funcNode*> funcPool;			//函数池
	vector<Block*> blockStack;				//维护的栈
	innerCode innerCode;					//中间代码生成工具
	treeNode* root;
};


#endif