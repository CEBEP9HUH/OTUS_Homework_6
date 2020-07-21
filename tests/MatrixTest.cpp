#include "gtest/gtest.h"
#include "InfiniteMatrix2D.hpp"
#include <random>


TEST(VALUES, ADD){
    std::random_device random;
    const int default_ = 42;
    const int repeats = 10;
    InfiniteMatrix2D<int, default_> matrix;
    for(size_t i = 0; i < repeats; ++i){
        ASSERT_EQ(matrix[random()][random()], default_);
    }
    matrix[1][1] = 888;
    ASSERT_EQ(matrix[1][1], 888);
}

TEST(MATRIX, SIZE){
    std::random_device random;
    const int default_ = 42;
    const int repeats = 10;
    InfiniteMatrix2D<int, default_> matrix;
    for(size_t i = 0; i < repeats; ++i){
        matrix[random()][random()] = i;
    }
}

TEST(MATRIX, CLEAR){
    const int default_ = 42;
    const int repeats = 10;
    int size = 0;
    InfiniteMatrix2D<int, default_> matrix;
    for(size_t i = 0; i < repeats; ++i){
        for(size_t j = 0; j < repeats; ++j){
            matrix[i][j] = i;
            ASSERT_EQ(matrix.size(), ++size);
        }
    }
    for(size_t i = 0; i < repeats; ++i){
        for(size_t j = 0; j < repeats; ++j){
            matrix[i][j] = default_;
            ASSERT_EQ(matrix.size(), --size);
        }
    }
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}