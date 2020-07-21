#include <iostream>
#include <random>
#include "InfiniteMatrix2D.hpp"

int main(){
    const int default_ = 42;
    InfiniteMatrix2D<int, default_> matrix;
    //const int size = 10;    
    matrix[1][1] = 5;
    std::cout << "Size: " << matrix.size() << std::endl;
    matrix[1][2] = 6;
    std::cout << "Size: " << matrix.size() << std::endl;
    matrix[1][3] = 7;
    std::cout << "Size: " << matrix.size() << std::endl;
    matrix[1][1] = default_;
    std::cout << "Size: " << matrix.size() << std::endl;
    matrix[1][2] = default_;
    std::cout << "Size: " << matrix.size() << std::endl;

    for(auto i : matrix){
        
    }
    return 0;
}