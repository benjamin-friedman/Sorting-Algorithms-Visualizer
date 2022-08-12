/*
  Author: Benjamin G. Friedman
  Date: November 8th, 2021
  File: main.cpp
  Description:
      - Contains the main function for the sorting algorithms visualization. In summary, there is an array of
        positive integers and a vector of rectangle objects where the magnitude of an integer at index i corresponds to
        the height of the rectangle at index i. As the array gets sorted, the heights of the rectangles simultaneously
        get updated to visualize the sorting process.
*/


#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <memory>
#include <SFML/Graphics.hpp>
#include "SortingAlgorithms.h"


// Global variables
// SFML window
const int windowWidth = 1250;
const int windowHeight = 600;
extern const size_t totalNumbers = 250;

// Sorting algorithms
const std::string acceptableSortingAlgorithms[] = { "bubble", "selection", "insertion", "shell", "quick", "heap", "merge", "counting", "bucket", "radix" };
const size_t acceptableSortingAlgorithmsSize = sizeof(acceptableSortingAlgorithms) / sizeof(*acceptableSortingAlgorithms);
const std::string bestTimeComplexities[] = { "N", "N^2", "N", "Nlog(N)", "Nlog(N)", "Nlog(N)", "Nlog(N)", "N + K", "N + K", "NK" };
const std::string averageTimeComplexities[] = { "N^2", "N^2", "N^2", "depends on gap sequence", "Nlog(N)", "Nlog(N)", "Nlog(N)", "N + K", "N + K", "NK" };
const std::string worstTimeComplexities[] = { "N^2", "N^2", "N^2", "N^2", "N^2", "Nlog(N)", "Nlog(N)", "N + K", "N^2", "NK" };


/***** General Helper Functions *****/
/* Validates the command line arguments. */
void validateCLA(int argc, char* argv[]);

/* Creates an array of positive random integers with a given start and end range. */
void randomizeArray(int *a, size_t size, int startRange, int endRange);

/* Initializes a vector of rectangles where the height of each rectangle at index "i" in the vector corresponds to the magnitude of the
   number at index "i" in the array. */
void initializeRectangles(std::vector<std::shared_ptr<sf::RectangleShape>>& recs, const int* a, size_t size, double recWidth);

/* Initializes the title diplayed in the window showing the sorting algorithms name and its time complexities. */
void initializeTitle(sf::Text& title, sf::Font& font, const std::string& sortingAlgorithmSelected);

/* Creates the string for the title.  */
std::string createTitleString(const std::string& sortingAlgorithmSelected);

/* Updates the height of each rectangle in the vector based on how the array has been sorted at some instantaneous point in time. By updating
   the heights, the current progress of the sorting process is kept up to date in the vector of rectangles. */
void updateRectangles(std::vector<std::shared_ptr<sf::RectangleShape>>& recs, const int *a);

/* Prints out all of the rectangles to the screen allowing it to be visualized how the array of integers looks during an instantaneous moment
   during the sorting process. */
void printRectangles(const std::vector<std::shared_ptr<sf::RectangleShape>>& recs, sf::RenderWindow& window, const sf::Text& title);

/* Assigns the correct sorting algorithm to the function pointer based on what sorting algorithm was entered into the command line. */
void assignSortingAlgorithm(void (**fpSortingAlgorithm)(int*, int), const std::string& sortingAlgorithmSelected);




int main(int argc, char* argv[]) { 
    
    // Validate command line arguments
    validateCLA(argc, argv);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sorting Algorithms Visualizer");
    std::vector<std::shared_ptr<sf::RectangleShape>> recs;    // Rectangles
    int numbers[totalNumbers];                                // Array to be sorted
    void (*fpSortingAlgorithm)(int*, int);                    // Sorting algorithm function
    std::string sortingAlgorithmSelected(argv[1]);            
    const double recWidth = static_cast<double>(windowWidth) / totalNumbers;
    sf::Font font;
    sf::Text title;

    // Initialize the array, rectangles, and title
    randomizeArray(numbers, totalNumbers, 0, windowHeight * 0.8);
    initializeRectangles(recs, numbers, totalNumbers, recWidth);
    initializeTitle(title, font, sortingAlgorithmSelected);

    // Begin the sorting process and visualization
    assignSortingAlgorithm(&fpSortingAlgorithm, sortingAlgorithmSelected);
    std::thread sortingAlgorithm(fpSortingAlgorithm, numbers, totalNumbers);

    while (window.isOpen())
    {
	sf::Event event;
	while (window.pollEvent(event)) {
	    if (event.type == sf::Event::Closed)
		window.close();
	}
	updateRectangles(recs, numbers);
	printRectangles(recs, window, title);
    }

    
    sortingAlgorithm.join();
    
    return 0;
}




/***** General Helper Function Defintions *****/
void validateCLA(int argc, char* argv[]) {
    if (argc != 3) {
	std::cout << "Command line argument error. Expected \"./SortingAlgorithmVisualizer [sorting-algorithm-name] sort\"\n\n";
	exit(1);
    }

    std::string sortingAlgorithmSelected(argv[1]);
    std::string sort(argv[2]);

    if (sort != "sort") {
	std::cout << "Command line argument error. Second command line argument must be the word \"sort\"\n\n";
	exit(2);
    }

    bool validSelection = false;
    for (size_t i = 0; i < acceptableSortingAlgorithmsSize && !validSelection; ++i) {
	if (sortingAlgorithmSelected == acceptableSortingAlgorithms[i])
	    validSelection = true;
    }

    if (!validSelection) {
	std::cout << "Command line argument error. Valid sorting algorithms are as follows:\n";
	for (size_t i = 0; i < acceptableSortingAlgorithmsSize && !validSelection; ++i)
	    std::cout << acceptableSortingAlgorithms[i] << " sort" << std::endl;
	std::cout << std::endl;
	exit(3);
    }
}



void randomizeArray(int *a, size_t size, int startRange, int endRange) {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> dist(startRange, endRange);

    for (size_t i = 0; i < size; ++i)
	a[i] = dist(generator);
}



void initializeRectangles(std::vector<std::shared_ptr<sf::RectangleShape>>& recs, const int* a, size_t size, double recWidth) {
    for (size_t i = 0; i < size; ++i) {
	auto rec = std::make_shared<sf::RectangleShape>();
	rec->setFillColor(sf::Color::Blue);
	rec->setOutlineColor(sf::Color::Black);
	rec->setOutlineThickness(1);
	rec->setSize(sf::Vector2f(recWidth, a[i]));
	rec->setPosition(sf::Vector2f(i * recWidth, windowHeight - a[i]));
	recs.push_back(rec);
    }
}



void initializeTitle(sf::Text& title, sf::Font& font, const std::string& sortingAlgorithmSelected) {
    if (!font.loadFromFile("arial.ttf")) {
	std::cout << "Error. Failed to load font file\n\n";
	exit(4);
    }
    title.setFont(font);
    title.setFillColor(sf::Color::Black);
    title.setCharacterSize(20);
    title.setString(createTitleString(sortingAlgorithmSelected));
    
}



std::string createTitleString(const std::string& sortingAlgorithmSelected) {
    std::string titleString(sortingAlgorithmSelected);
    size_t index;
    if (titleString == "bubble")
	index = 0;
    else if (titleString == "selection")
	index = 1;
    else if (titleString == "insertion")
	index = 2;
    else if (titleString == "shell")
	index = 3;
    else if (titleString == "quick")
	index = 4;
    else if (titleString == "heap")
	index = 5;
    else if (titleString == "merge")
	index = 6;
    else if (titleString == "counting")
	index = 7;
    else if (titleString == "radix")
	index = 8;
    else if (titleString == "bucket")
	index = 9;
    
    titleString[0] = toupper(titleString[0]);
    titleString += " Sort                    Time Complexities     ";
    titleString += "BEST: " + bestTimeComplexities[index] + "     ";
    titleString += "WORST: " + worstTimeComplexities[index] + "     ";
    titleString += "AVERAGE: " + averageTimeComplexities[index];
    return titleString;
}



void updateRectangles(std::vector<std::shared_ptr<sf::RectangleShape>>& recs, const int *a) {
    sf::Vector2f temp;
    for (size_t i = 0; i < recs.size(); ++i) {
	if (recs[i]->getSize().y != a[i]) {
	    temp.x = recs[i]->getSize().x;
	    temp.y = a[i];
	    recs[i]->setSize(temp);
	    temp.x = recs[i]->getPosition().x;
	    temp.y = windowHeight - a[i];
	    recs[i]->setPosition(temp);
	}
    }
}



void printRectangles(const std::vector<std::shared_ptr<sf::RectangleShape>>& recs, sf::RenderWindow& window, const sf::Text& title) {
    window.clear(sf::Color::White);
    for (auto rec = recs.begin(); rec != recs.end(); ++rec)
	window.draw(**rec);
    window.draw(title);
    window.display();
}



void assignSortingAlgorithm(void (**fpSortingAlgorithm)(int*, int), const std::string& sortingAlgorithmSelected) {
    if (sortingAlgorithmSelected == "bubble")
	*fpSortingAlgorithm = &bubbleSort;
    else if (sortingAlgorithmSelected == "selection")
	*fpSortingAlgorithm = &selectionSort;
    else if (sortingAlgorithmSelected == "insertion")
	*fpSortingAlgorithm = &insertionSort;
    else if (sortingAlgorithmSelected == "shell")
	*fpSortingAlgorithm = &shellSort;
    else if (sortingAlgorithmSelected == "quick")
	*fpSortingAlgorithm = &quickSort;
    else if (sortingAlgorithmSelected == "heap")
	*fpSortingAlgorithm = &heapSort;
    else if (sortingAlgorithmSelected == "merge")
	*fpSortingAlgorithm = &mergeSortWrapper;
    else if (sortingAlgorithmSelected == "counting")
	*fpSortingAlgorithm = &countingSort;
    else if (sortingAlgorithmSelected == "radix")
	*fpSortingAlgorithm = &radixSort;
    else if (sortingAlgorithmSelected == "bucket")
	*fpSortingAlgorithm = &bucketSort;
}
