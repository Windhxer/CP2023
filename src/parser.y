%{
#include <stdio.h>
#include <fstream>
#include <string>
#include "tree.hpp"
#include "translator.hpp"
using namespace std;

extern char *yytext;
extern int column;
extern FILE * yyin;
extern FILE * yyout;
treeNode* root = NULL;
extern int yylineno;

int yylex(void);
void yyerror(const char*); 
%}

%union{
	class treeNode* tN;
}
%output "parser.cpp"

%token <tN> IDENTIFIER CONSTANT STRING_LITERAL SIZEOF CONSTANT_INT CONSTANT_DOUBLE CONSTANT_CHAR
%token <tN> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token <tN> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token <tN> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token <tN> XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token <tN> CHAR INT DOUBLE VOID BOOL 

%token <tN> CASE IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token <tN> TRUE FALSE

%token <tN> ';' ',' ':' '=' '[' ']' '.' '&' '!' '~' '-' '+' '*' '/' '%' '<' '>' '^' '|' '?' '{' '}' '(' ')'

%type <tN> primary_expression postfix_expression argument_expression_list unary_expression unary_operator
%type <tN> multiplicative_expression additive_expression shift_expression relational_expression equality_expression
%type <tN> and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <tN> assignment_expression assignment_operator expression

%type <tN> declaration init_declarator_list init_declarator type_specifier

%type <tN> declarator 

%type <tN> parameter_list parameter_declaration identifier_list
%type <tN> /* abstract_declarator */ initializer initializer_list designation designator_list
%type <tN> designator statement labeled_statement compound_statement block_item_list block_item expression_statement
%type <tN> selection_statement iteration_statement jump_statement translation_unit external_declaration function_definition
%type <tN> declaration_list

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

Program: 
	translation_unit {
		root = new treeNode("Program",1,$1);
	}
	;

/*基本表达式*/
primary_expression: 
	IDENTIFIER {
		$$ = new treeNode("primary_expression",1,$1);
	}
	|
	TRUE {
		$$ = new treeNode("primary_expression",1,$1);
	}
	|
	FALSE {
		$$ = new treeNode("primary_expression",1,$1);
	}
	| CONSTANT_INT {
		$$ = new treeNode("primary_expression",1,$1);
		
	}
	| CONSTANT_DOUBLE {
		$$ = new treeNode("primary_expression",1,$1);
	}
	| CONSTANT_CHAR {
		$$ = new treeNode("primary_expression",1,$1);
	}
	| STRING_LITERAL {
		$$ = new treeNode("primary_expression",1,$1);
	}
	| '(' expression ')'{
		$$ = new treeNode("primary_expression",3,$1,$2,$3);
	}
	;

/*后缀表达式*/
postfix_expression:
	primary_expression{
		$$ = new treeNode("postfix_expression",1,$1);
	}
	| 	postfix_expression '[' expression ']'{
		$$ = new treeNode("postfix_expression",4,$1,$2,$3,$4);
		//数组调用
	}
	| 	postfix_expression '(' ')'{
		$$ = new treeNode("postfix_expression",3,$1,$2,$3);
		//函数调用
	}
	| 	postfix_expression '(' argument_expression_list ')'{
		$$ = new treeNode("postfix_expression",4,$1,$2,$3,$4);
		//函数调用
	}
	| 	postfix_expression INC_OP{
		//++
		$$ = new treeNode("postfix_expression",2,$1,$2);
	}
	| 	postfix_expression DEC_OP{
		//--
		$$ = new treeNode("postfix_expression",2,$1,$2);
	}
	;

argument_expression_list:
	assignment_expression{
		$$ = new treeNode("argument_expression_list",1,$1);
	}
	| 	argument_expression_list ',' assignment_expression {
		$$ = new treeNode("argument_expression_list",3,$1,$2,$3);
	}
	;

/*一元表达式*/
unary_expression:
	postfix_expression{
		$$ = new treeNode("unary_expression",1,$1);
	}
	| 	INC_OP unary_expression{
		//++
		$$ = new treeNode("unary_expression",2,$1,$2);
	}
	| 	DEC_OP unary_expression{
		//--
		$$ = new treeNode("unary_expression",2,$1,$2);
	}
	| 	unary_operator unary_expression{
		$$ = new treeNode("unary_expression",2,$1,$2);
	}
	;

/*单目运算符*/
unary_operator:
	'+' {
		$$ = new treeNode("unary_operator",1,$1);
	}
	| '-' {
		$$ = new treeNode("unary_operator",1,$1);
	}
	| '~' {
		$$ = new treeNode("unary_operator",1,$1);
	}
	| '!' {
		$$ = new treeNode("unary_operator",1,$1);
	}
	| '*' {
		$$ = new treeNode("unaru_operator",1,$1);
	}
	| '&' {
		$$ = new treeNode("unaru_operator",1,$1);
	}
	;

/*可乘表达式*/
multiplicative_expression:
	unary_expression {
		$$ = new treeNode("multiplicative_expression",1,$1);
	}
	| multiplicative_expression '*' unary_expression {
		$$ = new treeNode("multiplicative_expression",3,$1,$2,$3);
	}
	| multiplicative_expression '/' unary_expression {
		$$ = new treeNode("multiplicative_expression",3,$1,$2,$3);
	}
	| multiplicative_expression '%' unary_expression {
		$$ = new treeNode("multiplicative_expression",3,$1,$2,$3);
	}
	;

/*可加表达式*/
additive_expression:
	multiplicative_expression  {
		$$ = new treeNode("additive_expression",1,$1);
	}
	| additive_expression '+' multiplicative_expression {
		$$ = new treeNode("additive_expression",3,$1,$2,$3);
	}
	| additive_expression '-' multiplicative_expression {
		$$ = new treeNode("additive_expression",3,$1,$2,$3);
	}
	;

/*左移右移*/
shift_expression:
	additive_expression {
		$$ = new treeNode("shift_expression",1,$1);
	}
	| shift_expression LEFT_OP additive_expression {
		//<<
		$$ = new treeNode("shift_expression",3,$1,$2,$3);
	}
	| shift_expression RIGHT_OP additive_expression {
		//<<
		$$ = new treeNode("shift_expression",3,$1,$2,$3);
	}
	;

/*关系表达式*/
relational_expression:
	shift_expression {
		$$ = new treeNode("relational_expression",1,$1);
	}
	| relational_expression '<' shift_expression {
		$$ = new treeNode("relational_expression",3,$1,$2,$3);
	}
	| relational_expression '>' shift_expression {
		$$ = new treeNode("relational_expression",3,$1,$2,$3);
	}
	| relational_expression LE_OP shift_expression {
		// <= 
		$$ = new treeNode("relational_expression",3,$1,$2,$3);
	}
	| relational_expression GE_OP shift_expression {
		// >=
		$$ = new treeNode("relational_expression",3,$1,$2,$3);
	}
	;

/*相等表达式*/
equality_expression:
	relational_expression {
		$$ = new treeNode("equality_expression",1,$1);
	}
	| equality_expression EQ_OP relational_expression {
		// ==
		$$ = new treeNode("equality_expression",3,$1,$2,$3);
	}
	| equality_expression NE_OP relational_expression {
		// !=
		$$ = new treeNode("equality_expression",3,$1,$2,$3);
	}
	;

and_expression:
	equality_expression {
		$$ = new treeNode("and_expression",1,$1);
	}
	| and_expression '&' equality_expression {
		$$ = new treeNode("and_expression",3,$1,$2,$3);
	}
	;

/*异或*/
exclusive_or_expression:
	and_expression {
		$$ = new treeNode("exclusive_or_expression",1,$1);
	}
	| exclusive_or_expression '^' and_expression {
		$$ = new treeNode("exclusive_or_expression",3,$1,$2,$3);
	}
	;

/*或*/
inclusive_or_expression:
	exclusive_or_expression {
		$$ = new treeNode("inclusive_or_expression",1,$1);
	}
	| inclusive_or_expression '|' exclusive_or_expression {
		$$ = new treeNode("inclusive_or_expression",3,$1,$2,$3);
	}
	;

/*and逻辑表达式*/
logical_and_expression:
	inclusive_or_expression {
		$$ = new treeNode("logical_and_expression",1,$1);
	}
	| logical_and_expression AND_OP inclusive_or_expression {
		//&&
		$$ = new treeNode("logical_and_expression",3,$1,$2,$3);
	}
	;

/*or 逻辑表达式*/
logical_or_expression:
	logical_and_expression {
		$$ = new treeNode("logical_or_expression",1,$1);
	}
	| logical_or_expression OR_OP logical_and_expression {
		//||
		$$ = new treeNode("logical_or_expression",3,$1,$2,$3);
	}
	;

/*赋值表达式*/
assignment_expression:
	logical_or_expression {
		//条件表达式
		$$ = new treeNode("assignment_expression",1,$1);
	}
	| unary_expression assignment_operator assignment_expression {
		$$ = new treeNode("assignment_expression",3,$1,$2,$3);
	}
	;

/*赋值运算符*/
assignment_operator:
	'=' {
		$$ = new treeNode("assignment_operator",1,$1);
	}
	| MUL_ASSIGN {
		//*=
		$$ = new treeNode("assignment_operator",1,$1);
	}
	| DIV_ASSIGN {
		// /=
		$$ = new treeNode("assignment_operator",1,$1);
	}
	| MOD_ASSIGN {
		// %=
		$$ = new treeNode("assignment_operator",1,$1);
	}
	| ADD_ASSIGN {
		// += 
		$$ = new treeNode("assignment_operator",1,$1);
	}
	| SUB_ASSIGN {
		// -=
		$$ = new treeNode("assignment_operator",1,$1);
	}
	| LEFT_ASSIGN {
		// <<=
		$$ = new treeNode("assignment_operator",1,$1);
	}
	| RIGHT_ASSIGN {
		// >>=
		$$ = new treeNode("assignment_operator",1,$1);
	}
	| AND_ASSIGN {
		// &=
		$$ = new treeNode("assignment_operator",1,$1);
	}
	| XOR_ASSIGN {
		// ^=
		$$ = new treeNode("assignment_operator",1,$1);
	}
	| OR_ASSIGN {
		// |=
		$$ = new treeNode("assignment_operator",1,$1);
	}
	;

/*表达式*/
expression:
	assignment_expression {
		//赋值表达式
		$$ = new treeNode("expression",1,$1);
	}
	| expression ',' assignment_expression {
		//逗号表达式
		$$ = new treeNode("expression",3,$1,$2,$3);
	}
	;


declaration:
	type_specifier ';' {
		$$ = new treeNode("declaration",2,$1,$2); //?
	}
	| type_specifier init_declarator_list ';' {
		$$ = new treeNode("declaration",3,$1,$2,$3);
	}
	;


init_declarator_list:
	init_declarator {
		$$ = new treeNode("init_declarator_list",1,$1);
	}
	| init_declarator_list ',' init_declarator {
		$$ = new treeNode("init_declarator_list",3,$1,$2,$3);
	}
	;

init_declarator:
	declarator {
		$$ = new treeNode("init_declarator",1,$1);
	}
	| declarator '=' initializer {
		$$ = new treeNode("init_declarator",3,$1,$2,$3);
	}
	;


/*类型说明符*/
type_specifier:
	VOID {
		$$ = new treeNode("type_specifier",1,$1);
	}
	| CHAR {
		$$ = new treeNode("type_specifier",1,$1);
	}
	| INT {
		$$ = new treeNode("type_specifier",1,$1);
	}
	| DOUBLE {
		$$ = new treeNode("type_specifier",1,$1);	
	}
	| BOOL {
		$$ = new treeNode("type_specifier",1,$1);
	}
	;



declarator:
	IDENTIFIER {
		//变量
		$$ = new treeNode("declarator",1,$1);
	}
	/* | '(' declarator ')' {
		//.....
		$$ = new treeNode("declarator",3,$1,$2,$3);
	} */
	| declarator '[' assignment_expression ']' {
		//数组
		//printf("assignment_expression");
		$$ = new treeNode("declarator",4,$1,$2,$3,$4);
	}
	/* | declarator '[' '*' ']' {
		//....
		$$ = new treeNode("declarator",4,$1,$2,$3,$4);
	} */
	| declarator '[' ']' {
		//数组
		$$ = new treeNode("declarator",3,$1,$2,$3);
	}
	| declarator '(' parameter_list ')' {
		//函数
		$$ = new treeNode("declarator",4,$1,$2,$3,$4);
	}
	| declarator '(' identifier_list ')' {
		//函数
		$$ = new treeNode("declarator",4,$1,$2,$3,$4);
	}
	| declarator '(' ')' {
		//函数
		$$ = new treeNode("declarator",3,$1,$2,$3);
	}
	;


//参数列表
parameter_list:
	parameter_declaration {
		$$ = new treeNode("parameter_list",1,$1);
	}
	| parameter_list ',' parameter_declaration {
		$$ = new treeNode("parameter_list",3,$1,$2,$3);
	}
	;

parameter_declaration:
	type_specifier declarator {
		$$ = new treeNode("parameter_declaration",2,$1,$2);
	}
	/* | type_specifier abstract_declarator {
		$$ = new treeNode("parameter_declaration",2,$1,$2);
	} */
	| type_specifier {
		$$ = new treeNode("parameter_declaration",1,$1);
	}
	;

identifier_list:
	IDENTIFIER {
		$$ = new treeNode("identifier_list",1,$1);
	}
	| identifier_list ',' IDENTIFIER {
		$$ = new treeNode("identifier_list",3,$1,$2,$3);
	}
	;

/* abstract_declarator:
	'(' abstract_declarator ')' {
		$$ = new treeNode("abstract_declarator",3,$1,$2,$3);
	}
	| '[' ']' {
		$$ = new treeNode("abstract_declarator",2,$1,$2);
	}
	| '[' assignment_expression ']' {
		$$ = new treeNode("abstract_declarator",3,$1,$2,$3);
	}
	| abstract_declarator '[' ']' {
		$$ = new treeNode("abstract_declarator",3,$1,$2,$3);
	}
	| abstract_declarator '[' assignment_expression ']' {
		$$ = new treeNode("abstract_declarator",4,$1,$2,$3,$4);
	}
	| '[' '*' ']' {
		$$ = new treeNode("abstract_declarator",3,$1,$2,$3);
	}
	| abstract_declarator '[' '*' ']' {
		$$ = new treeNode("abstract_declarator",4,$1,$2,$3,$4);
	}
	| '(' ')' {
		$$ = new treeNode("abstract_declarator",2,$1,$2);
	}
	| '(' parameter_list ')' {
		$$ = new treeNode("abstract_declarator",3,$1,$2,$3);
	}
	| abstract_declarator '(' ')' {
		$$ = new treeNode("abstract_declarator",3,$1,$2,$3);
	}
	| abstract_declarator '(' parameter_list ')' {
		$$ = new treeNode("abstract_declarator",4,$1,$2,$3,$4);
	}
	; */

//初始化
initializer:
	assignment_expression {
		$$ = new treeNode("initializer",1,$1);
	}
	/* | '{' initializer_list '}' {
		//列表初始化 {1,1,1}
		$$ = new treeNode("initializer",3,$1,$2,$3);
	}
	| '{' initializer_list ',' '}' {
		//列表初始化 {1,1,1,}
		$$ = new treeNode("initializer",4,$1,$2,$3,$4);
	} */
	;

initializer_list:
	initializer {
		$$ = new treeNode("initializer_list",1,$1);
	}
	| designation initializer {
		$$ = new treeNode("initializer_list",2,$1,$2);
	}
	| initializer_list ',' initializer {
		$$ = new treeNode("initializer_list",3,$1,$2,$3);
	}
	| initializer_list ',' designation initializer {
		$$ = new treeNode("initializer_list",3,$1,$2,$3);
	}
	;

designation:
	designator_list '=' {
		$$ = new treeNode("designation",2,$1,$2);
	}
	;

designator_list:
	designator {
		$$ = new treeNode("designator_list",1,$1);
	}
	| designator_list designator {
		$$ = new treeNode("designator_list",2,$1,$2);
	}
	;

designator: 
	'[' logical_or_expression ']' {
		$$ = new treeNode("designator",3,$1,$2,$3);
	}
	| '.' IDENTIFIER {
		$$ = new treeNode("designator",2,$1,$2);
	}
	;

//声明
statement:
	labeled_statement {
		$$ = new treeNode("statement",1,$1);
	}
	| compound_statement {
		$$ = new treeNode("statement",1,$1);
	}
	| expression_statement{
		$$ = new treeNode("statement",1,$1);
	}
	| selection_statement {
		$$ = new treeNode("statement",1,$1);
	}
	| iteration_statement {
		$$ = new treeNode("statement",1,$1);
	}
	| jump_statement {
		$$ = new treeNode("statement",1,$1);
	}
	;

//标签声明
labeled_statement:
	IDENTIFIER ':' statement {
		$$ = new treeNode("labeled_statement",3,$1,$2,$3);
	}
	| CASE logical_or_expression ':' statement {
		$$ = new treeNode("labeled_statement",4,$1,$2,$3,$4);
	}
	;

//复合语句
compound_statement:
	'{' '}' {
		$$ = new treeNode("compound_statement",2,$1,$2);
	}
	| '{' block_item_list '}' {
		$$ = new treeNode("compound_statement",3,$1,$2,$3);
	}
	;

block_item_list:
	block_item {
		$$ = new treeNode("block_item_list",1,$1);
	}
	| block_item_list block_item {
		$$ = new treeNode("block_item_list",2,$1,$2);
	}
	;

block_item:
	declaration {
		$$ = new treeNode("block_item",1,$1);
	}
	| statement {
		$$ = new treeNode("block_item",1,$1);
	}
	;

expression_statement:
	';' {
		$$ = new treeNode("expression_statement",1,$1);
	}
	| expression ';' {
		$$ = new treeNode("expression_statement",2,$1,$2);
	}
	;

//条件语句
selection_statement:
	IF '(' expression ')' statement %prec LOWER_THAN_ELSE {
		$$ = new treeNode("selection_statement",5,$1,$2,$3,$4,$5);
	}
    | IF '(' expression ')' statement ELSE statement {
		$$ = new treeNode("selection_statement",7,$1,$2,$3,$4,$5,$6,$7);
	}
    | SWITCH '(' expression ')' statement {
		$$ = new treeNode("selection_statement",5,$1,$2,$3,$4,$5);
	}
    ;

//循环语句
iteration_statement:
	WHILE '(' expression ')' statement {
		$$ = new treeNode("iteration_statement",5,$1,$2,$3,$4,$5);
	}
	| DO statement WHILE '(' expression ')' ';' {
		$$ = new treeNode("iteration_statement",7,$1,$2,$3,$4,$5,$6,$7);
	}
	| FOR '(' expression_statement expression_statement ')' statement {
		$$ = new treeNode("iteration_statement",6,$1,$2,$3,$4,$5,$6);
	}
	| FOR '(' expression_statement expression_statement expression ')' statement {
		$$ = new treeNode("iteration_statement",7,$1,$2,$3,$4,$5,$6,$7);
	}
	| FOR '(' declaration expression_statement ')' statement {
		$$ = new treeNode("iteration_statement",6,$1,$2,$3,$4,$5,$6);
	}
	| FOR '(' declaration expression_statement expression ')' statement {
		$$ = new treeNode("iteration_statement",7,$1,$2,$3,$4,$5,$6,$7);
	}
	;

//跳转指令
jump_statement:
	GOTO IDENTIFIER ';' {
		$$ = new treeNode("jump_statement",2,$1,$2);
	}
	| CONTINUE ';' {
		$$ = new treeNode("jump_statement",2,$1,$2);
	}
	| BREAK ';' {
		$$ = new treeNode("jump_statement",2,$1,$2);
	}
	| RETURN ';' {
		$$ = new treeNode("jump_statement",2,$1,$2);
	}
	| RETURN expression ';' {
		$$ = new treeNode("jump_statement",3,$1,$2,$3);
	}
	;

translation_unit:
	external_declaration {
		$$ = new treeNode("translation_unit",1,$1);
	}
	| translation_unit external_declaration {
		$$ = new treeNode("translation_unit",2,$1,$2);
	}
	;

external_declaration:
	function_definition {
		$$ = new treeNode("external_declaration",1,$1);
		//函数定义
	}
	| declaration {
		$$ = new treeNode("external_declaration",1,$1);
		//变量声明
	}
	;

function_definition:
	/* type_specifier declarator declaration_list compound_statement {
		$$ = new treeNode("function_definition",4,$1,$2,$3,$4);
	} */
	type_specifier declarator compound_statement {
		$$ = new treeNode("function_definition",3,$1,$2,$3);
	}
	;

declaration_list:
	declaration {
		$$ = new treeNode("declaration_list",1,$1);
	}
	| declaration_list declaration {
		$$ = new treeNode("declaration_list",2,$1,$2);
	}
	;

%%

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

int main(int argc,char* argv[]) {
	yyin = fopen(argv[1],"r");
	
	yyparse();
	printf("\n");
	ofstream treeOs;
	treeOs.open("test/tree.txt");
	root->printTree(0, treeOs);

	translator *t = new translator(root);

	ofstream innerCodeOs;
	innerCodeOs.open("test/innerCode.txt");
	t->innerCode.printCode(innerCodeOs);

	/* freeGramTree(root); */

	fclose(yyin);
	return 0;
}