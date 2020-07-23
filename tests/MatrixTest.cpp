#include "gtest/gtest.h"
#include "InfiniteMatrix2D.hpp"
#include <random>
#include <map>


TEST(VALUES, ADD){
    std::random_device random;
    const int default_ = 42;
    const int repeats = 10;
    InfiniteMatrix2D<int, default_> matrix;
    std::map<std::pair<size_t, size_t>, int> results;
    for(size_t i = 0; i < repeats; ++i){
        ASSERT_EQ(matrix[random()][random()], default_);
    }
    for(size_t i = 0; i < repeats; ++i){
        for(size_t j = 0; j < repeats; ++j){
            size_t row = random();
            size_t col = random();
            matrix[row][col] = random();
            results[std::make_pair(row,col)] = matrix[row][col];
        }
    }
    for(auto iter : results){
        ASSERT_EQ(matrix[iter.first.first][iter.first.second], iter.second);
    }
}

TEST(MATRIX, SIZE){
    std::random_device random;
    const int default_ = 42;
    const int repeats = 10;
    InfiniteMatrix2D<int, default_> matrix;
    for(size_t i = 0; i < repeats; ++i){
        matrix[random()][random()] = i;
    }
    ASSERT_EQ(matrix.size(), repeats);
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

TEST(MATRIX, ITERATORS){
    const int default_ = 42;
    const int repeats = 10;
    std::random_device random;
    InfiniteMatrix2D<int, default_> matrix;
    std::map<std::pair<size_t, size_t>, int> results;
    for(size_t i = 0; i < repeats; ++i){
        for(size_t j = 0; j < repeats; ++j){
            size_t row = random();
            size_t col = random();
            matrix[row][col] = random();
            results[std::make_pair(row,col)] = matrix[row][col];
        }
    }
    auto _iter = results.begin();
    for(auto elem : matrix){
        size_t a,b;
        int c;
        std::tie(a,b,c) = elem;
        ASSERT_EQ(a, _iter->first.first);
        ASSERT_EQ(b, _iter->first.second);
        ASSERT_EQ(c, _iter->second);
        ++_iter;
    }
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}