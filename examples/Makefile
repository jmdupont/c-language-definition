
clean : grammar
	rm grammar

grammar : grammar.c
	g++  -g3 -save-temps grammar.c -o grammar

test: grammar
	./grammar
all :
	gcc -fdump-translation-unit -c *.c