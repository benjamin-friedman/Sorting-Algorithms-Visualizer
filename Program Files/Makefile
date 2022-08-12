# Author: Benjamin G. Friedman
# Date: 05/20/2022
# File: Makefile
# Description: Makefile for the sorting algorithms visualizer program.


CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Og -g -fsanitize=undefined # comment out -Og... when done debugging
LDLIBS = -pthread -lsfml-graphics -lsfml-window -lsfml-system
EXE1 = SortingAlgorithmsVisualizer
OBJ1 = Main.o SortingAlgorithms.o
EXES = $(EXE1)


all: $(EXES)
.PHONY: all clean


$(EXE1): $(OBJ1)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm $(EXES) $(wildcard *.o)
