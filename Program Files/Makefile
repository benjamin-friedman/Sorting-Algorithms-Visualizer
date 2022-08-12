# Author: Benjamin G. Friedman
# Date: 05/20/2022
# File: Makefile
# Description: Makefile for the sorting algorithms visualizer program.


CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
DEBUG = # -Og -g -fsanitize=undefined # comment out when done debugging
EXE1 = SortingAlgorithmsVisualizer
OBJ1 = Main.o SortingAlgorithms.o
EXES = $(EXE1)


all: $(EXES)
.PHONY: all clean


$(EXE1): $(OBJ1)
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $@ $^ $(LDLIBS)

%.o: %.c %.h
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $< -o $@
%.o: %.c
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $< -o $@

clean:
	-rm $(EXES) $(wildcard *.o)
