#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <set>

//Homework use map a set

using namespace std;

//Combinations fun from the lesson
vector<vector<int>> combinations(const int n, const int k ){
    vector<vector<int>> res;
    if(k < 0 or k > n){
        return res;
       }
    vector<int> currentComb;
    currentComb.reserve(k);
    for (int i = 0; i < k; i++)
    {
           currentComb.push_back(i);
        }

        while (true) {
            res.push_back(currentComb);
        
            int i = k - 1;
            while(i >= 0 and currentComb[i] == n + i - k){
                i--;
            }
            if(i < 0){ break; }

            currentComb[i] += 1;
            for(size_t j = i + 1; j < currentComb.size(); j++){
                currentComb[j] = currentComb[j-1] + 1;
            }
        }

        return res;
        
    }

//Generates vector of set combinations
vector<set<int>> setCombinations(const set<int>& inputSet, const int k){
    vector<set<int>> result;
    vector<int> inputVec(inputSet.begin(), inputSet.end());
    //All combinations of indicies
    auto combIndices = combinations(inputVec.size(), k);
    //Generates sets based on indicies retrieved from combinations() function
    for (const auto& indices : combIndices)
        {
           set<int> currentSet;
            for (const auto& index : indices)
            {
                currentSet.insert(inputVec[index]);
            }
            result.push_back(currentSet);
        }

    return result;
} 

//Returns boundary edges of given simplexes
vector<vector<int>> boundaryEdges(vector<set<int>>& simplexes){
    map<vector<int>, int> edge_occurences;
    for (auto& simplex : simplexes)
    {
        auto subsets = setCombinations(simplex, simplex.size() - 1);
        for (const auto& subset : subsets)
        {
            //Subsets are type of "set" so sorting is unnecessary atleast I think so
            vector<int> subsetVec(subset.begin(), subset.end());
            edge_occurences[subsetVec]++;
        }
    }

    //Chooses boundary faces that are not shared among the simplexes)
    vector<vector<int>> result_boundaries;
    for (const auto& [boundary_face, count] : edge_occurences)
    {
        if (count == 1)
        {
            result_boundaries.push_back(boundary_face);
        }
    }

    return result_boundaries;
}

//Counts simplexes by their dimension
map<int, int> count_sets_by_dimension(const vector<set<int>>& simplexes){
    map<vector<int>, int> edge_occurences;
    map<int, int> dimension_count;

    for (const auto& simplex : simplexes)
    {
        //Generates all subsets for each simplex
        for (size_t k = 1; k <= simplex.size(); k++)
        {
            auto subsets = setCombinations(simplex, k);
            for (const auto& subset : subsets)
            {
            //Subsets are type of "set" so sorting is unnecessary atleast I think so
            vector<int> subsetVec(subset.begin(), subset.end());
            edge_occurences[subsetVec]++;
        }
        }
    }
    
    for (const auto& [boundary_face, count] : edge_occurences)
    {
        int dim = boundary_face.size() - 1;
        dimension_count[dim]++;
    }

    return dimension_count;
}


//Reads simplexes from file, each simplex is equal to one line in the file
vector<set<int>> readSimplexesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<set<int>> simplexes;

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return simplexes;
    }

    std::string line;

    // change if to while to read the whole file
    while (std::getline(file, line)) {
        std::stringstream lineAsStream(line);
        int num;
        set<int> simplex;
        while (lineAsStream >> num) {  // NOTE: this assumes that the input file has the data we want
            simplex.insert(num);
        }
        simplexes.push_back(simplex);
    }

    file.close();
    return simplexes;
}

//Boundaries output. Its kinda funny how examplary output is not equal to tests.
void boundariesOutput(const vector<vector<int>>& boundaries){
    if(boundaries.empty()){
        cout << "Boundary:" << endl;
        cout << "is empty" << endl;
    } else {
        for (const auto& edge : boundaries)
        {
            for (size_t i = 0; i < edge.size(); i++)
            {
                cout << edge[i] << (i < edge.size() - 1 ? " " : "");
            }
            cout << endl;
        }
    }
}



void statisticsOutput(const vector<set<int>>& simplexes){
    
    int chi = 0;
    map<int, int> simplicies_count = count_sets_by_dimension(simplexes);
    for (const auto&[dimension, count] : simplicies_count)
    {
        switch (dimension)
        {
        case 0:
            cout << "Vertices: " << count << endl;
            break;
        case 1:
            cout << "Edges: " << count << endl;
            break;
        case 2:
            cout << "Triangles: " << count << endl;
            break;
        case 3:
            cout << "Tetrahedrons: " << count << endl;
            break;
        default:
            break;
        }

        if(dimension % 2 == 0){
            chi += count;
        } else {
            chi -= count;
        }

    }
    cout << "chi: "<< chi << endl << endl;

}


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){

    if(argc != 2){
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }

    auto simplexes = readSimplexesFromFile(argv[1]);
    statisticsOutput(simplexes);

    auto boundaries = boundaryEdges(simplexes);
    boundariesOutput(boundaries);

    return 0;
}