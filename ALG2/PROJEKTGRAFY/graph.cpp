#include "graph.h"

// Based on https://github.com/Korf-tms/Algoritmy-II/blob/main/fun/read_from_file.cpp
// Adjusted to read undirected graph edges and push them back into adjacency list
// Also counts edges
std::vector<std::vector<int>> Graph::readIntegersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> numbersVec;
    
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return numbersVec;
    }

    std::string line;


    while (std::getline(file, line)) {
        std::stringstream lineAsStream(line);
        int v1,v2;
        while (lineAsStream >> v1 >> v2) {
            edge_count++;

            // Resize adjacency list if needed (Highest vertex indexes can be at start of the file which are not allocated yet)
            size_t maxIndex = std::max(v1, v2);
            if (numbersVec.size() <= maxIndex) {
                numbersVec.resize(maxIndex + 1);
            }

            numbersVec[v1].push_back(v2);
            numbersVec[v2].push_back(v1);
        }
    }

    file.close();
    return numbersVec;
}

void Graph::printVertices() const {
    for (size_t i = 0; i < adjacencyList.size(); i++)
    {
        std::cout << i << std::endl;
    }
    
}

void Graph::printGraphStatistics() {
    std::vector<int> centers = getGraphCenters();


    std::cout << "Number of vertices: " << adjacencyList.size() << std::endl;
    std::cout << "Number of edges: " << edge_count << std::endl;
    std::cout << "Connected: " << (connected ? "True" : "False") << std::endl;
    if(centers.size() == 1) {
        std::cout << "Graph center: " << centers[0] << std::endl;
        std::cout << "Graph center eccentricity: " << minimal_eccentricity << std::endl;
    } else {
        std::cout << "Graph center eccentricity: " << minimal_eccentricity << std::endl;
        std::cout << "Graph center: total " << centers.size() << " vertices, see below:" << std::endl;
        for(const auto& center : centers) {
            std::cout << center << std::endl;
        }
    }

}

// Based on Levitin - Introduction to the Design and Analysis of Algorithms:    3.5 Depth-First Search and Breadth-First Search
// Basically BFS implementation to find maximal eccentricity of a start vertex
int Graph::bfsEccentricity(int start) {

    std::vector<bool> visited(adjacencyList.size(), false);
    std::queue<int> queue;
    int max_eccentricity = 0;
    size_t visited_count = 0;

    visited[start] = true;
    queue.push(start);

    while (!queue.empty()) {
        size_t queue_size = queue.size();
        for (size_t i = 0; i < queue_size; i++)
        {
            // Take out the front vertex from the queue
            int current_vertex = queue.front();
            queue.pop();

            // Iterate through all adjacent vertices of our current vertex
            // Add them into the queue if not visited yet
            for(auto neighbour : adjacencyList[current_vertex]){
                if(!visited[neighbour]){
                    visited[neighbour] = true;
                    visited_count++;
                    queue.push(neighbour);
                }
            }
        }
        
        
        if(!queue.empty()){
            max_eccentricity++;
        }
    }

    // If we didn't visit all vertices, the graph is not connected (common sense)
    if(visited_count != adjacencyList.size() - 1){
        connected = false;
    }

    return max_eccentricity;
    
    
}

std::vector<int> Graph::getGraphCenters() {
    std::vector<int> centers;
    minimal_eccentricity = INT_MAX;

    // For each vertex, calculate its eccentricity using BFS
    // Choose the minimal eccentricity vertices as centers
    for(size_t i = 0; i < adjacencyList.size(); i++) {
        int eccentricity = bfsEccentricity(i);
        if(eccentricity < minimal_eccentricity) {
            minimal_eccentricity = eccentricity;
            centers.clear();
            centers.push_back(i);
        } else if(eccentricity == minimal_eccentricity) {
            centers.push_back(i);
        }
    }
    
    return centers;
}

