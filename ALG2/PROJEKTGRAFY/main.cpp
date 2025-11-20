/**
 * @file main.cpp
 * @brief Main program for finding graph center
 * 
 * Program loads graph from file and prints its statistics including center vertices,
 * eccentricity, connectivity, vertices and edges count.
 */
#include <chrono>
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
    
    auto start_time = std::chrono::high_resolution_clock::now();
    Graph graph(argv[1]);

    //graph.printVertices();

    graph.printGraphStatistics();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::cout << std::endl;
    std::cout << argv[1] << " took: " << duration.count() << " ms" << std::endl;

    return 0;
}