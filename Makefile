.PHONY: all clean

all: getInnerCode

clean:
	rm -rf ./out/* ./tester/quicksort/quickSort ./tester/matrix/matrix ./tester/advisor/advisor

flex: ./src/lexer.l
	flex -o ./out/lexer.cpp ./src/lexer.l

bison: ./src/parser.y
	bison -d -o ./out/parser.cpp ./src/parser.y

getInnerCode: flex bison ./src/tree.cpp ./src/translator.cpp ./src/innerCode.cpp
	g++ -o ./out/getInnerCode ./out/lexer.cpp ./out/parser.cpp ./src/tree.cpp ./src/translator.cpp ./src/innerCode.cpp

quickSort: ./out/getInnerCode ./code/quickSort.c
	./out/getInnerCode ./code/quickSort.c ./out/quickSortTree.txt ./out/quickSortInnerCode.txt
	python3 ./src/codeGenerator.py ./out/quickSortInnerCode.txt ./out/quickSortAsm.s
	riscv64-unknown-elf-gcc -o ./tester/quicksort/quickSort ./out/quickSortAsm.s -lc

matrix: ./out/getInnerCode ./code/matrix.c
	./out/getInnerCode ./code/matrix.c ./out/matrixTree.txt ./out/matrixInnerCode.txt
	python3 ./src/codeGenerator.py ./out/matrixInnerCode.txt ./out/matrixAsm.s
	riscv64-unknown-elf-gcc -o ./tester/matrix/matrix ./out/matrixAsm.s

advisor: ./out/getInnerCode ./code/advisor.c
	./out/getInnerCode ./code/advisor.c ./out/advisorTree.txt ./out/advisorInnerCode.txt
	python3 ./src/codeGenerator.py ./out/advisorInnerCode.txt ./out/advisorAsm.s
	riscv64-unknown-elf-gcc -o ./tester/advisor/advisor ./out/advisorAsm.s