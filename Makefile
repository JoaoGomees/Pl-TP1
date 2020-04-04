projeto: lex.yy.c estrutura.c 
	gcc -o projeto lex.yy.c estrutura.c

lex.yy.c: parser.l
	lex parser.l

clean:	
	rm lex.yy.c projeto *.json



