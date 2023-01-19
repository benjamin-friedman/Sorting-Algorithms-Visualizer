# Sorting-Algorithms-Visualizer
- Sorting algorithms visualizer program for the following sorting algorithms: bubble sort, selection sort, insertion sort, shell sort, heap sort, quick sort, merge sort, counting sort, bucket sort, and radix sort. The program sorts an array of positive integers and in real time displays a visual representation of the sorting process using rectangular bars, where the height of each bar corresponds to the integers in the array. The code was written so that each sorting algorithm takes about 25 seconds to complete thus giving a good visual representation of the sorting process.
- Link to Video Demo: https://www.youtube.com/watch?v=2S24N5oIgEQ

# Instructions
- The project was done using C++ and SFML in Linux (Ubuntu). Follow the instructions on SFML's website for how to install it on Linux. https://www.sfml-dev.org/tutorials/2.5/start-linux.php. A different package manager might have to be used depending on what version of Linux is being used.
- A Makefile is provided to compile the code and create an executable file named SortingAlgorithmsVisualizer. The Makefile is setup to work for SFML when it has been installed on the standard path in Linux.
- Enter "make" to compile the code and create the executable file.
- To run the program, enter **./SortingAlgorithmsVisualizer [sorting-algorithm-name] sort**. For example, **./SortingAlgorithmVisualizer heap sort** would run the heap sort visualizer.
- Normally, SFML can be used in other systems aside from Linux. However, this is not the case for this particular project because it uses the usleep function from the <unistd.h> library which is a Linux library. If this program is to be run in another system outside of Linux, the code would have to be modified to use that system's equivalent version. 