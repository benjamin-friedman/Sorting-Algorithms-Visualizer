#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <memory>
#include <SFML/Graphics.hpp>
#include "SortingAlgorithms.h"

/***** SFML window *****/
const int windowWidth = 1250;
const int windowHeight = 600;
extern const int totalNumbers = 250;


/***** Sorting Algorithms - names and time complexities *****/
const std::string acceptableSortingAlgorithms[] = { "bubble", "selection", "insertion", "shell", "quick", "heap", "merge", "counting", "bucket", "radix" };
const int acceptableSortingAlgorithmsSize = sizeof(acceptableSortingAlgorithms) / sizeof(*acceptableSortingAlgorithms);
const std::string bestTimeComplexities[] = { "N", "N^2", "N", "Nlog(N)", "Nlog(N)", "Nlog(N)", "Nlog(N)", "N + K", "N + K", "NK" };
const std::string averageTimeComplexities[] = { "N^2", "N^2", "N^2", "depends on gap sequence", "Nlog(N)", "Nlog(N)", "Nlog(N)", "N + K", "N + K", "NK" };
const std::string worstTimeComplexities[] = { "N^2", "N^2", "N^2", "N^2", "N^2", "Nlog(N)", "Nlog(N)", "N + K", "N^2", "NK" };


/***** General Helper Functions *****/
/* Creates an array of positive random integers with a given start and end range. */
void randomizeArray(int *a, int size, int startRange, int endRange);

/* Initializes a vector of rectangles where the height of each rectangle at index "i" in the vector corresponds to the magnitude of the
   number at index "i" in the array. */
void initializeRectangles(std::vector<std::shared_ptr<sf::RectangleShape>>& recs, const int* a, int size, double recWidth);

/* Updates the height of each rectangle in the vector based on how the array has been sorted at some instantaneous point in time. By updating
   the heights, the current progress of the sorting process is kept up to date in the vector of rectangles. */
void updateRectangles(std::vector<std::shared_ptr<sf::RectangleShape>>& recs, const int *a);

/* Prints out all of the rectangles to the screen allowing it to be visualized how the array of integers looks during an instantaneous moment
   during the sorting process. */
void printRectangles(const std::vector<std::shared_ptr<sf::RectangleShape>>& recs, sf::RenderWindow& window, const sf::Text& title);

/* Creates the title string based on the sorting algorithm selected - this title appears in the SFML window. */
std::string createTitle(const std::string& sortingAlgorithmSelected);



int main(int argc, char* argv[])
{
    /***** validate command line arguments *****/
    // no command line arguments
    if (argc != 3) {
	std::cout << "Command line argument error. Expected \"./SortingAlgorithmVisualizer [sorting-algorithm-name] sort\"\n\n";
	exit(1);
    }

    std::string sortingAlgorithmSelected(argv[1]);
    std::string _sort(argv[2]);

    // invalid command line arguments
    if (_sort != "sort") {
	std::cout << "Command line argument error. Second command line argument must be the word \"sort\"\n\n";
	exit(2);
    }

    bool validSelection = false;
    for (int i = 0; i < acceptableSortingAlgorithmsSize && !validSelection; i++) {
	if (sortingAlgorithmSelected == acceptableSortingAlgorithms[i])
	    validSelection = true;
    }

    if (!validSelection) {
	std::cout << "Command line argument error. Valid sorting algorithms are as follows:\n";
	for (int i = 0; i < acceptableSortingAlgorithmsSize && !validSelection; i++)
	    std::cout << acceptableSortingAlgorithms[i] << " sort" << std::endl;
	std::cout << std::endl;
	exit(3);
    }



    /**** begin the program *****/
    //SFML Window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sorting Algorithms Visualizer");

    /* The integer at index "i" is the height of the rectangle at index "i".
       As the array gets sorted, the corresponding rectangle has it's height updated
       thus visualizing the sorting process */
    std::vector<std::shared_ptr<sf::RectangleShape>> recs;
    int numbers[totalNumbers];
    void (*fpSortingAlgorithm)(int*, int);
    const double recWidth = static_cast<double>(windowWidth) / totalNumbers;

    // fill up the array with random numbers
    randomizeArray(numbers, totalNumbers, 0, windowHeight * 0.8);
    initializeRectangles(recs, numbers, totalNumbers, recWidth);

    // select the correct sorting algorithm 
    if (sortingAlgorithmSelected == "bubble")
	fpSortingAlgorithm = &bubbleSort;
    else if (sortingAlgorithmSelected == "selection")
	fpSortingAlgorithm = &selectionSort;
    else if (sortingAlgorithmSelected == "insertion")
	fpSortingAlgorithm = &insertionSort;
    else if (sortingAlgorithmSelected == "shell")
	fpSortingAlgorithm = &shellSort;
    else if (sortingAlgorithmSelected == "quick")
	fpSortingAlgorithm = &quickSort;
    else if (sortingAlgorithmSelected == "heap")
	fpSortingAlgorithm = &heapSort;
    else if (sortingAlgorithmSelected == "merge")
	fpSortingAlgorithm = &mergeSortWrapper;
    else if (sortingAlgorithmSelected == "counting")
	fpSortingAlgorithm = &countingSort;
    else if (sortingAlgorithmSelected == "radix")
	fpSortingAlgorithm = &radixSort;
    else if (sortingAlgorithmSelected == "bucket")
	fpSortingAlgorithm = &bucketSort;
        
    // title for the sorting algorithm
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
	std::cout << "Error. Failed to load font file\n\n";
	exit(4);
    }
    
    sf::Text title;
    title.setFont(font);
    title.setFillColor(sf::Color::Black);
    title.setCharacterSize(20);
    std::string titleString = createTitle(sortingAlgorithmSelected);
    title.setString(titleString);

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


/* General Helper Function Definitions */
void randomizeArray(int *a, int size, int startRange, int endRange) {
    //random number generator
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> dist(startRange, endRange);

    // fill up the array with random numbers
    for (int i = 0; i < size; i++)
	a[i] = dist(generator);
}


void initializeRectangles(std::vector<std::shared_ptr<sf::RectangleShape>>& recs, const int* a, int size, double recWidth) {
    for (int i = 0; i < size; i++) {
	auto rec = std::make_shared<sf::RectangleShape>();
	rec->setFillColor(sf::Color::Blue);
	rec->setOutlineColor(sf::Color::Black);
	rec->setOutlineThickness(1);
	rec->setSize(sf::Vector2f(recWidth, a[i]));
	rec->setPosition(sf::Vector2f(i * recWidth, windowHeight - a[i]));
	recs.push_back(rec);
    }
}


void updateRectangles(std::vector<std::shared_ptr<sf::RectangleShape>>& recs, const int *a) {
    sf::Vector2f temp;
    for (unsigned i = 0; i < recs.size(); i++) {
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
    for (unsigned i = 0; i < recs.size(); i++)
	window.draw(*recs[i]);
    window.draw(title);
    window.display();
}


std::string createTitle(const std::string& sortingAlgorithmSelected) {
    std::string title(sortingAlgorithmSelected);
    int index;
    if (title == "bubble")
	index = 0;
    else if (title == "selection")
	index = 1;
    else if (title == "insertion")
	index = 2;
    else if (title == "shell")
	index = 3;
    else if (title == "quick")
	index = 4;
    else if (title == "heap")
	index = 5;
    else if (title == "merge")
	index = 6;
    else if (title == "counting")
	index = 7;
    else if (title == "radix")
	index = 8;
    else if (title == "bucket")
	index = 9;
    
    title[0] = toupper(title[0]);
    title += " Sort                    Time Complexities     ";
    title += "BEST: " + bestTimeComplexities[index] + "     ";
    title += "WORST: " + worstTimeComplexities[index] + "     ";
    title += "AVERAGE: " + averageTimeComplexities[index];
    return title;
}
