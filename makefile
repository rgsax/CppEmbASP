target: all

all:
	g++ main.cpp -o main -std=c++17 -lboost_system -lboost_filesystem -pthread
