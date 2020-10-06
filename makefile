all: main
main: main.cpp
	g++  -pthread main.cpp -o main -lncurses

