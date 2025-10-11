#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
using ScalarType = double;
using Matrix = vector<vector<ScalarType>>;

template<typename T>
void printVec(const vector<T>& vec){
    for (const T& item : vec)
    {
        std::cout << item << " ";
    }
    std::cout << "\n";

}

void printMatrix(const Matrix& mat){
    for(const auto& row : mat){

        printVec(row);

    }

}

vector<ScalarType> solveAxb(Matrix A, vector<ScalarType> b){
    Matrix L(A.size(), vector<ScalarType>(A.size(), 0));
    for (size_t k = 0; k < L.size(); k++)
    {
        L[k][k] = 1;
    }
    
    for ( size_t i = 1; i < A.size(); i++)
    {   
        size_t pivot = i;
        ScalarType pivotValue = std::abs(A[i][i]);
        for (size_t k = i + 1; k < A.size(); k++)
        {
            if(pivotValue < std::abs(A[k][i])){
                pivot = k;
                pivotValue = std::abs(A[k][i]);
            }
        }
        if(pivot != i){
            std::swap(A[i], A[pivot]);
            std::swap(b[i], b[pivot]);
        }

        for( size_t j = i + 1; j < A.size(); j++){
            ScalarType temp = A[j][i] / A[i][i];
            for (size_t k = i; k < A.size(); k++)
            {
                A[j][k] -= temp * A[i][k];
            }
            b[j] -= temp * b[i];

        }
    }
    
    //Solve with upper triangular
    for (int i = A.size()-1; i >= 0; i--)
    {
        ScalarType sumCorrection = 0;
        for (size_t j = i; j < A.size(); j++)
        {
            sumCorrection += A[i][j] * b[j];
        }
        b[i] = (b[i] - sumCorrection) / A[i][i];
        
    }
    


    return b;
}



int main(){
    Matrix mat = {{1, 2},
                   {2, 1}};
    vector<ScalarType> rhs = {1,1};

    auto x = solveAxb(mat, rhs);
    printVec(x);

    return 0;
}