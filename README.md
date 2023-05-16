### 5.14添加
在根目录下执行：
```
make
```
或
```
make lexer_only_compile
```
即可完成构建

然后在根目录下执行：
```
make lexer_only_run
```
即可将./other/quickSort_cmm.c进行词法分析，结果放在./out/lexer_only.txt

### praser架构
通过词法分析与语法分析构建语法树(参考http://www.quut.com/c/ANSI-C-grammar-l-1998.html
和 http://www.quut.com/c/ANSI-C-grammar-y-1995.html)，而后在.y文件的main函数中对语法树进行分析，从而拆分代码结构
tree/praser等有待修改
根据yacc中的文法进行praser文件中函数的书写

### innerCode
innerCode.h/cpp文件里用来实现var变量等的记录并进行一定的优化