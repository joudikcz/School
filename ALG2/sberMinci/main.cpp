#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::vector<int>> readIntegersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> numbersVec;
    

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return numbersVec;
    }

    std::string line;

    // change if to while to read the whole file
    while (std::getline(file, line)) {
        std::stringstream lineAsStream(line);
        std::vector<int> currentLineVec;
        int num;
        while (lineAsStream >> num) {  // NOTE: this assumes that the input file has the data we want
            currentLineVec.push_back(num);
        }
        numbersVec.push_back(currentLineVec);
    }

    file.close();
    return numbersVec;
}

// Introduction to the Design and Analysis of Algorithms on page 288 (Example 3).
int robotCoinCollection(const std::vector<std::vector<int>>& C){
    int n = C.size();
    int m = C[0].size();
    std::vector<std::vector<int>> F(n, std::vector<int>(m, 0));

    F[0][0] = C[0][0];

    // First row
    for(int j = 1; j < m; j++){
        F[0][j] = F[0][j - 1] + C[0][j];
    }
    
    // Rest of the rows
    for(int i = 1; i < n; i++){
        F[i][0] = F[i - 1][0] + C[i][0];
        for (int j = 1; j < m; j++){
            F[i][j] = std::max(F[i - 1][j], F[i][j - 1]) + C[i][j];
        }
        
    }
    
    return F[n - 1][m - 1];
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    
    if(argc != 2){
        std::cout << "Invalid number of arguments provided." << std::endl;
        return 1;
    }
    
    std::vector<std::vector<int>> coinDesk = readIntegersFromFile(argv[1]);

    int maxCoinsCollected = robotCoinCollection(coinDesk);
    std::cout << maxCoinsCollected << std::endl;
    return 0;
}