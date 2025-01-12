CC=g++
CFLAGS = -w -g -std=c++11

all: parser++

parser++: main.o  token_def.o grammar_def.o
	$(CC) $(CFLAGS) -o parser++ main.o token_def.o grammar_def.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

token_def.o: lexer/token_def.cpp
	$(CC) $(CFLAGS) -c lexer/token_def.cpp

grammar_def.o: grammar/grammar_def.cpp
	$(CC) $(CFLAGS) -c grammar/grammar_def.cpp

clean:
	rm -f *.o parser++
