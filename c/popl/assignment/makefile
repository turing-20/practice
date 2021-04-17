run: a.out
	./a.out

a.out: y.tab.c lex.yy.c
	gcc y.tab.c lex.yy.c

lex.yy.c: lexer.l
	flex lexer.l

y.tab.c: parser.y
	bison -y -d --warnings=none parser.y

clean:
	rm -f lex.yy.c y.tab.* *.out