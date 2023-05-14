all: lexer_only_compile

lexer_only_compile: ./src/lexer_only.l
	flex ./src/lexer_only.l
	g++ ./src/lexer_only.cpp -o ./out/lexer_only

lexer_only_run: ./out/lexer_only
	./out/lexer_only ./other/quickSort_cmm.c ./out/lexer_only.txt

clean:
	rm -f ./src/lexer_only.cpp ./out/lexer_only