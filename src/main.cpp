#include <iostream>
#include <random>
#include "InfiniteMatrix2D.hpp"

int main(){
    const int default_ = 0;
    const size_t size = 9;
    InfiniteMatrix2D<int, default_> matrix;
    for(size_t i = 0; i<=size; ++i){
        matrix[i][i] = i;
        matrix[i][size-i] = i;
    }
    for(size_t i = 1; i<=size-1; ++i){
        for(size_t j = 1; j<=size-1; ++j){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << matrix.size() << "\n";
    for(auto it : matrix){
        size_t a, b;
        int c;
        std::tie(a,b,c) = it;
        std::cout << a << b << c << std::endl;
    }
    return 0;
}