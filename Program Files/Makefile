CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Werror -pedantic -pthread
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJ = main.o SortingAlgorithms.o
EXE = SortingAlgorithmsVisualizer

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ) $(SFMLFLAGS)
main.o: main.cpp SortingAlgorithms.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o
SortingAlgorithms.o: SortingAlgorithms.cpp SortingAlgorithms.h
	$(CXX) $(CXXFLAGS) -c SortingAlgorithms.cpp -o SortingAlgorithms.o

clean:
	rm $(EXE) $(OBJ)
