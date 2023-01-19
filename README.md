# Solar-System-Simulation-Interstellar-Theme
- Sorting algorithms visualizer program for the following sorting algorithms: bubble sort, selection sort, insertion sort, shell sort, heap sort, quick sort, merge sort, counting sort, bucket sort, and radix sort. The program sorts an array of positive integers and in real time displays a visual representation of the sorting process using rectangular bars, where the height of each bar corresponds to the integers in the array. The code was written so that each sorting algorithm takes about 25 seconds to complete thus giving a good visual representation of the sorting process.
- Link to Video Demo: https://www.youtube.com/watch?v=2S24N5oIgEQ

# Instructions
- The project was done using C++ and SFML 2.5.1 in Linux (Ubuntu). Follow the instructions on SFML's website for how to install it on Linux. https://www.sfml-dev.org/tutorials/2.5/start-linux.php. A different package manager might have to be used depending on what version of Linux is being used.
- A Makefile is provided to compile the code and create an executable file named SolarSystemSimulation. The Makefile is setup to work for SFML when it has been installed on the standard path in Linux.
- Enter "make" to compile the code and create the executable file.
- To run the program, enter **./SolarSystemSimulation [total time] [time step] < res/solar_system.txt**. The total time represents the total time of the simulation, and time step represents one step of the simulation (some passage of time in the solar system, or one iteration of the window loop). For example, **./SolarSystemSimulation 1000000000 500 < res/solar_system.txt** would run the simulation for 1 billion seconds with each time step being 500 seconds.
- SFML can be used in other environments aside from Linux including Microsoft Visual Studio and Visual Studio Code amongst others. Refer to the website: https://www.sfml-dev.org/index.php. If this program is run in another environment that doesn't use the command line directly, the command line arguments would have to be set manually in the settings.


# Instructions
- The program expects two command line arguments after the executable: **./SortingAlgorithmsVisualizer [sorting-algorithm-name] sort**. 
- Selection sort as an example: **./SortingAlgorithmsVisualizer selection sort**.

# Program Files
- main.cpp - Main program.
- SortingAlgorithms.h/SortingAlgorithms.cpp - Sorting algorithms interface.
- Makefile - For compiling the program.
- artial.ttf - Text font file.
