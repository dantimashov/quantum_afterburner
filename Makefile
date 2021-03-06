CXX=g++
CXX_FLAGS=-Wall

all: qrace clean
main.o: ./src/main.cpp ./src/game.h ./src/spacecraft.h ./src/obstaclesAndBonuses.h
	$(CXX) $(CXX_FLAGS) -c ./src/main.cpp

qrace: ./src/main.o
	$(CXX) $(CXX_FLAGS) ./src/main.o -o qrace -lsfml-graphics -lsfml-window -lsfml-system

clean: 
	rm -f main ./src/*.o
.PHONY: clean all

