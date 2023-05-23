#include"tree.h"

treeNode* create_tree(string name, int num,...) {
    va_list valist;
    treeNode* head = new treeNode();
    if(!head) {
        //内存不足
        printf("空间不足 \n");
        exit(0);
    }
    head->content = "";
    head->name = name;
    va_start(valist,num);
    //对于多节点情况，如果仅为 name-content 形式，则直接修改内容，否则使其与后续节点一同进入子节点的vector
    if(num > 0) {
        treeNode* temp = NULL;
        temp = va_arg(valist,treeNode*);
        temp->parent = head;
        head->sibs.push_back(temp);
        head->line = temp->line;
        if(num == 1) {
            if(temp->content.size() > 0)
                head->content = temp->content;
        }
        else {
            for(int i = 1; i < num; ++i ) {
                treeNode* tempForRight = NULL;
                tempForRight = va_arg(valist, treeNode *);
                tempForRight->parent = head;
                head->sibs.push_back(tempForRight);
            }
        }
    }
    //对于token节点，直接对其进行类型判断，将常数直接进行处理
    //值得注意的是，尽管此处没有单独列出，identifier也是特殊单独处理，只是其内容与其余内容的yytext并无区分
    else {
        int line = va_arg(valist,int);
        head->line = line;
        if(head->name == "CONSTANT_INT") {
           int value;
           if(strlen(yytext) > 1 && yytext[0] == '0' && yytext[1] != 'x') {
               sscanf(yytext,"%o",&value); //8进制整数
           }
           else if(strlen(yytext) > 1 && yytext[1] == 'x'){
               sscanf(yytext,"%x",&value); //16进制整数
           }
           else value = atoi(yytext);      //10进制整数
           head->content = to_string(value);
        }
        else if(head->name == "CONSTANT_DOUBLE") {
           head->content = yytext;
        }
        else if(head->name == "TRUE") {
           head->content = to_string(1);
        }
        else if(head->name == "FALSE") {
           head->content = to_string(0);
        }
        else {
            head->content = yytext;
        }
    }
    return head;
}

//进行树的打印
void eval(treeNode *head,int leavel) {
    if(head!=NULL) {
        string Name = head->name;
        if(head->line!=-1) {
            for(int i=0;i<leavel;++i) {
                cout << ". ";
            }
            cout << head->name;
        
            if(head->name == "IDENTIFIER"||head->name == "BOOL"|| head->name == "INT" || 
            head->name == "CHAR" || head->name == "DOUBLE") {
                cout << ":" << head->content;
            }
            else if(head->name == "CONSTANT_INT" || head->name == "TRUE" || head->name == "FALSE") {
                cout << ":" << head->content << " ";
            }
            else if(head->name == "CONSTANT_DOUBLE") {
                cout << ":" << head->content << " ";
            }
            else if(head->name=="STRING_LITERAL") {
                cout << ":" << head->content;
            }
            else {
                cout << " <" << head->line << ">";
            }
            cout << endl;
        }
        //逐个子节点进行打印
        for (int i = 0; i < head->sibs.size(); i++){
            eval(head->sibs[i],leavel+1);
        }
    }
}

//释放树节点空间
void freeGramTree(treeNode* node) {
	if (node == NULL)
		return;
    auto treeIt = node->sibs.begin();
        for (; treeIt <= node->sibs.end() - 1;treeIt++){
        freeGramTree(*treeIt);
        }
	delete node;
}
