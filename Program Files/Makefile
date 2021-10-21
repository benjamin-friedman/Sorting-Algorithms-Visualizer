CC = g++
CFLAGS = -std=c++11 -g -Wall -Werror -pedantic -pthread
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = main.o SortingAlgorithms.o
EXE = SortingAlgorithmsVisualizer

$(EXE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(SFMLFLAGS)
main.o: main.cpp SortingAlgorithms.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o
SortingAlgorithms.o: SortingAlgorithms.cpp SortingAlgorithms.h
	$(CC) $(CFLAGS) -c SortingAlgorithms.cpp -o SortingAlgorithms.o

clean:
	rm $(EXE) $(OBJECTS)
