CPP_FLAGS =
CXX = g++
all:main clean
main.o:src/main.cpp src/game.h src/spacecraft.h src/obstaclesAndBonuses.h
	$(CXX) $(CPP_FLAGS) -c src/main.cpp
main:main.o 
	$(CXX) $(CPP_FLAGS) main.o -o bin/quantum_afterburner -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -f main *.o
.PHONY: clean all
