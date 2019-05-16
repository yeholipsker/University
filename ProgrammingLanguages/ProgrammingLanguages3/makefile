ex3: lex.yy.o ex3.tab.o
	g++ ex3.tab.o lex.yy.o -o ex3.out

ex3.tab.o: ex3.tab.c
	g++ -c ex3.tab.c

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

lex.yy.c: ex3.lex ex3.tab.h
	flex ex3.lex

ex3.tab.c ex3.tab.h: clean
	bison -d -v ex3.y --debug --verbose

clean:
	rm -f *.h *.c *.o  *.out*

