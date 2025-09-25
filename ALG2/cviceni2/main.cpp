#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>

using namespace std;

std::vector<int> readIntegersFromFile(const std::string& filename);
void test(std::string filename);
//Binary search looks if the number occured in data, if it does then it returns true else false
bool binarySearch(vector<int>& data, int number);

int main(int argc, char* argv[]){
    if(argc < 3){
        cerr << "Not enough args" << endl;
        return 1;
    }

    string data_file = argv[1];
    string numbers_file = argv[2];

    auto data = readIntegersFromFile(data_file);
    auto numbers = readIntegersFromFile(numbers_file);
    //test(data_file);
    //test(numbers_file);

    sort(data.begin(), data.end());
    //for (auto d : data) {
    //    cout << d << endl;
    //}
    
    
    size_t number_amount = numbers.size();
    //cout << endl << number_amount << endl;
    vector<bool> numbers_existence_flag(number_amount, false);    

    //Iterate through with each number -> set its flag to true if found inside the data
    for (size_t i = 0; i < number_amount; i++) {
        numbers_existence_flag[i] = binarySearch(data, numbers[i]);
    }
    
    
    for (size_t i = 0; i < number_amount; i++) {
        cout << numbers[i] << ": " << (numbers_existence_flag[i] ? "T" : "F") << endl; 
    } 

    return 0;
}

bool binarySearch(vector<int>& data, int number){
    if(number > data.back()){
        return false;
    }

    int left = 0;
    int right = data.size() - 1;
    while (left <= right) {
        int m = left + floor((right - left) / 2);
        if(data[m] < number){
            left = m + 1;
        }else if(data[m] > number){
            right = m - 1;
        }else{
            return true;
        }
    }

    return false;
}

std::vector<int> readIntegersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<int> numbersVec;

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return numbersVec;
    }

    std::string line;

    // change if to while to read the whole file
    if (std::getline(file, line)) {
        std::stringstream lineAsStream(line);
        int num;
        while (lineAsStream >> num) {  // NOTE: this assumes that the input file has the data we want
            numbersVec.push_back(num);
        }
    }

    file.close();
    return numbersVec;
}

void test(std::string filename){
    std::vector<int> numbers;

    numbers = readIntegersFromFile(filename);

    for(const auto& item : numbers){
        std::cout << item << " ";
    }
    std::cout << "\n";
}
