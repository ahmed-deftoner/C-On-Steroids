run: main.out
	./main.out input.cos

main.o: main.cpp
	g++ -o main.out main.cpp