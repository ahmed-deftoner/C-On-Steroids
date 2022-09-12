EXEC = a.out
CC = g++
OBJ = lexer.o main.o parser.o

run : $(EXEC)
	./$(EXEC) sample_code.ol

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

lexer.o : lexer.cpp lexer.h
	$(CC) -c lexer.cpp

main.o : main.cpp lexer.h
	$(CC) -c main.cpp

parser.o:parser.cpp parser.h
	$(CC) -c parser.cpp

clean:
	rm -f $(EXEC) lexer.o main.o parser.o
