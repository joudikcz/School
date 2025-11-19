/**
 * @file main.cpp
 * @brief Main program for finding graph center
 * 
 * Program loads graph from file and prints its statistics including center vertices,
 * eccentricity, connectivity, vertices and edges count.
 */

#include <iostream>
#include "graph.h"

/**
 * @brief Main function of the program
 * @param argc Number of arguments in the command-line - expects 2
 * @param argv Array of string arguments in the command-line - expects filename with graph
 * @return Exit status code
 */
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    
    if(argc != 2){
        std::cout << "Invalid number of arguments provided." << std::endl;
        return 1;
    }
    
    Graph graph(argv[1]);

    //graph.printVertices();

    graph.printGraphStatistics();

    return 0;
}