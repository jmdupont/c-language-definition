
clean : grammar
	rm grammar

grammar : grammar.c Makefile
	g++  -O0 -g -Wall grammar.c -o grammar

test: grammar grammar.c
	./grammar
all :
	gcc -fdump-translation-unit -c *.c
