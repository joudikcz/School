#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


class Z2 {
public:
    int value;
    // Constructor: the +2 factor guarantees positive output of %
    Z2(int v = 0) : value((v % 2 + 2) % 2) {}

    // Overload arithmetic operators for Z2
    Z2 operator+(const Z2& other) const { return Z2(value + other.value); }
    Z2 operator-(const Z2& other) const { return Z2(value - other.value); }
    Z2 operator*(const Z2& other) const { return Z2(value * other.value); }
    Z2 operator/(const Z2& other) const {
        if (other.value == 0) {
            throw std::runtime_error("Division by zero in Z2.");
        }
        return Z2(value); // only possible division is by 1
    }

    Z2& operator+=(const Z2& other) { value = (value + other.value) % 2; return *this; }
    Z2& operator-=(const Z2& other) { value = (value - other.value + 2) % 2; return *this; }
    Z2& operator*=(const Z2& other) { value = (value * other.value) % 2; return *this; }

    bool operator==(const Z2& other) const { return value == other.value; }
    bool operator!=(const Z2& other) const { return value != other.value; }


};

using std::vector;
using ScalarType = Z2;
using Matrix = vector<vector<ScalarType>>;

template<typename T>
void printVec(const vector<T>& vec){
    for (const T& item : vec)
    {
        std::cout << item.value << " ";
    }
    std::cout << "\n";

}

void printMatrix(const Matrix& mat){
    for(const auto& row : mat){

        printVec(row);

    }

}

vector<ScalarType> solveAxb(Matrix A, vector<ScalarType> b){
  
    for ( size_t i = 0; i < A.size(); i++)
    {   

        size_t pivot = i;
        for (size_t k = i; k < A.size(); k++)
        {
            //Najdeme prvni pivot ktery je = 1 a nim pak nulujeme
            if(A[k][i] == 1){
                pivot = k;
                break;
            }
        }

        if(pivot != i){
            std::swap(A[i], A[pivot]);
            std::swap(b[i], b[pivot]);
        }

        for( size_t j = i + 1; j < A.size(); j++){
            //ScalarType temp = A[j][i] / A[i][i];
            //nulovani 1 pod pivotem
            if(A[j][i] == 1){
            for (size_t k = i; k < A.size(); k++)
                {
                    A[j][k] += A[i][k]; // XOR 1 1 -> 0
                }
            b[j] += b[i]; // XOR
            }
        }
    }
    
    //upper triangular -> zpetna subs
    for (int i = A.size() - 1; i >= 0; i--) {
        
        ScalarType sumCorrection = 0;
        for (size_t j = i + 1; j < A.size(); j++){
            sumCorrection += A[i][j] * b[j];

        }
        b[i] = b[i] - sumCorrection;
    }

    return b;
}

Matrix build_A(int n){
    int size = n * n;
    Matrix A(size, vector<ScalarType>(size, 0));

    vector<std::pair<int, int>> directions = {
        {0, 0},
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            int button_index = x + n * y;
            for(auto [dx, dy] : directions){
                int nx = x + dx;
                int ny = y + dy;
                if(nx >= 0 && nx  < n && ny >= 0 && ny  < n){
                    int affected_index = nx + n * ny;
                    A[affected_index][button_index] = 1;
                }

            }


        }
        
    }
    


    return A;
}

int main(int argc, char* argv[1]){
    const int n = std::stoi(argv[1]);
    if(argc != n*n+2){
        std::cerr << "Invalid number of arguments\n";
        return -1;
    }

    vector<ScalarType> rhs;
    for(int i = 0; i < n*n; i++){
        rhs.push_back(std::stoi(argv[i+2]));
    }

    Matrix A = build_A(n);

    auto vectorSolution = solveAxb(A, rhs);
    printVec(vectorSolution);

    return 0;
}