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
通过词法分析与语法分析构建语法树，而后在.y文件的main函数中对语法树进行分析，从而拆分代码结构