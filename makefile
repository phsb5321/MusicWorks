all: main
main: main.cpp
	g++  -pthread -lncurses main.cpp -o main 

