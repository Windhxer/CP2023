.PHONY: all clean

all: getInnerCode

clean:
	rm -rf ./out/* ./tester/quicksort/quickSort

flex: ./src/lexer.l
	flex -o ./out/lexer.cpp ./src/lexer.l

bison: ./src/parser.y
	bison -d -o ./out/parser.cpp ./src/parser.y

getInnerCode: flex bison ./src/tree.cpp ./src/translator.cpp ./src/innerCode.cpp
	g++ -o ./out/getInnerCode ./out/lexer.cpp ./out/parser.cpp ./src/tree.cpp ./src/translator.cpp ./src/innerCode.cpp

draft: ./out/getInnerCode ./draft/draft.c
	./out/getInnerCode ./draft/draft.c ./out/draftTree.txt ./out/draftInnerCode.txt
	python3 ./src/codeGenerator.py ./out/draftInnerCode.txt ./out/draftAsm.s
	riscv64-unknown-elf-gcc -o ./out/draft ./out/draftAsm.s

quickSort: ./out/getInnerCode ./code/quickSort.c
	./out/getInnerCode ./code/quickSort.c ./out/quickSortTree.txt ./out/quickSortInnerCode.txt
	python3 ./src/codeGenerator.py ./out/quickSortInnerCode.txt ./out/quickSortAsm.s
	riscv64-unknown-elf-gcc -o ./tester/quicksort/quickSort ./out/quickSortAsm.s -lc

matrix: ./out/getInnerCode ./code/matrix.c
	./out/getInnerCode ./code/matrix.c ./out/matrixTree.txt ./out/matrixInnerCode.txt
	python3 ./src/codeGenerator.py ./out/matrixInnerCode.txt ./out/matrixAsm.s
	riscv64-unknown-elf-gcc -o ./tester/matrix/matrix ./out/matrixAsm.s