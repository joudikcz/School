/**
 * @file graph.h
 * @brief Header file for Graph class
 * 
 * Contains definition of Graph class (undirected graph).
 */
#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <exception>
#include <queue>
#include <climits>

/**
 * @brief Class represents an undirected graph with methods to find its center(s) and other statistics.
 */
class Graph {
private:
    std::vector<std::vector<int>> adjacencyList;    ///< Adjacency list representation of the graph

    int edge_count = 0;             ///< Total number of edges
    bool connected = true;          ///< Flag indicating if the graph is connected
    int minimal_eccentricity = -1;  ///< Minimum eccentricity found in the graph

    /**
     * @brief Reads graph data from file and builds adjacency list
     * @param filename Path to input file containing edge pairs
     * @return Adjacency list 
     */
    std::vector<std::vector<int>> readIntegersFromFile(const std::string& filename);

    /**
     * @brief Calculates the maximal eccentricity of and lower bound distance using BFS
     * @param start Starting vertex index (Where should BFS start)
     * @return Pair containing maximal eccentricity and vector of lower bound distances
     */
    std::pair<int, std::vector<int>> bfsEccentricity(int start);

    /**
     * @brief Preprocess extreme vertices to refine lower bound eccentricities (TLDR Optimalization -> further info inside the fuction)
     * @param centers Vector of current center vertices
     * @param lower_bound_eccentricities Vector of lower bound eccentricities
     * @param minimal_eccentricity Current minimal eccentricity
     * @return Value of the v1 vertex
     */
    size_t preprocessExtremeVertices(std::vector<int>& centers, std::vector<int>& lower_bound_eccentricities, int& minimal_eccentricity);

public:

    /**
     * @brief Constructs graph from file data
     * @param filename Input file containing vertex pairs (edges)
     */
    Graph(const std::string& filename) {
        adjacencyList = readIntegersFromFile(filename);
    }

    /**
     * @brief Finds graph center vertices
     * @return Vector of vertices with minimum eccentricity (TLDR returns graph centers)
     */
    std::vector<int> getGraphCenters();

    /**
     * @brief Displays graph statistics
     * 
     * Outputs vertex count, edge count, connectivity status, 
     * and center vertices with their eccentricity.
     */
    void printGraphStatistics();

    /**
     * @brief Outputs all vertices in the graph
     * 
     * Debug utility to display all vertices.
     */
    void printVertices() const;

};