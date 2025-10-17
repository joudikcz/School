#include<vector>
#include<exception>
#include<iostream>
#include<algorithm>
#include <sstream>
#include <fstream>
#include <string>

using std::vector;

class Heap{
    private:
    vector<int> data;
    size_t n; // n-ary tree <=> child amount
    
    size_t parent(size_t index) const {
        if(index == 0){return 0;} // note that heap root has no parent
        return (index - 1) / n;
    }

    void heapify(size_t index){
        size_t largest = index;

        //Iterate through n times (n -> children amount)
        for(size_t i = 0; i < n; i ++){
            size_t child = n*index+ i + 1; //index of the i-th child in n-ary heap
            if(child >= data.size()){ break;} // indices can be out of bounds
            if(data[child] > data[largest]){
                largest = child;
            }
        }
        if(largest != index){
            std::swap(data[index], data[largest]);
            heapify(largest);  // restore heap property on subtree
        }
    }

    void makeHeap(){
        // build heap from bottom to top
        for(int i = data.size() / 2 - 1; i >= 0; i--){
            heapify(i);
        }
    }

    public:
    Heap() = default;

    Heap(const vector<int>& input, size_t N){
        n = N;
        data = input;
        makeHeap();
    }

    Heap(vector<int>&& input, size_t N){
        n = N;
        data = std::move(input);
        makeHeap();
    }

    void insert(const int value){
        size_t currentIndex = data.size();
        data.push_back(value);
        size_t parentIndex = parent(currentIndex);

        // repair heap property by pushing the new number up
        while(currentIndex != 0 and data[currentIndex] > data[parentIndex]){
            std::swap(data[currentIndex], data[parentIndex]);
            currentIndex = parentIndex;
            parentIndex = parent(currentIndex);
        }
    }

    int getMax(){
        if( data.empty() ){
            throw std::out_of_range("Trying to extract item from empty heap");
        }
        int maxValue = data[0];

        data[0] = data.back();
        data.pop_back();
        if( data.size() > 1){
            heapify(0);
        }

        return maxValue;
    }

    void print() const {
        for(const int item : data){
            std::cout << item << " ";
        }
        std::cout << "\n";
    }

    void clear() {
        data.clear();
    }

};

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

void test(char *args[]){
    int Narity = std::stoi(args[1]);
    std::string data_file = args[2];
    
    vector<int> data = readIntegersFromFile(data_file);

    //vector<int> data = {10, 11, 1, 2, 3, 100, 200};
    Heap heap(std::move(data), Narity);
    for(const int item : data){
        heap.insert(item);
    }

    //1.
    heap.print();

    //2.
    heap.getMax();
    heap.print();

    //3.
    heap.insert(42);
    heap.print();

    //4.
    heap.insert(-5);
    heap.print();

    //5.
    heap.getMax();
    heap.print();

    
    //Heap heap2(std::move(data), n);
    //std::cout << "Note that these constructions do not lead to same internal vector.\n";
    //heap2.print();

}


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
    test(argv);
    return 0;
}