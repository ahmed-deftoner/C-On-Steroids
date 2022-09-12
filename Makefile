run: main.out
	./main.out input.cos

main.out: main.cpp
	g++ -o main.out main.cpp