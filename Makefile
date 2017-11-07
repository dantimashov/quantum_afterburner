CXX=g++
CXX_FLAGS=-Wall

all: qrace
main.o: ./src/main.cpp ./src/game.h ./src/spacecraft.h ./src/obstaclesAndBonuses.h
	$(CXX) $(CXX_FLAGS) -c ./src/main.cpp

qrace: ./src/main.o
	$(CXX) $(CXX_FLAGS) ./src/main.o -o qrace -lsfml-graphics -lsfml-window -lsfml-system

clean: rm ./src/* -r
.PHONY: clean all

