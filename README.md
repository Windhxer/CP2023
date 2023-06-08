### 构造方法
1. 生成中间代码生成器
在根目录执行：
```
make
```
即可构建中间代码生成器

2. 验证测试程序
+ 在根目录执行：（需要环境中有 qemu-user 和 riscv64-unknown-elf-gcc ）
```
make quickSort
bash quickSort.sh
```
即可验证快速排序程序

+ 在根目录执行：（需要环境中有 qemu-user 和 riscv64-unknown-elf-gcc ）
```
make quickSort
bash matrix.sh
```
即可验证矩阵乘法程序