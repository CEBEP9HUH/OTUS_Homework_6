#pragma once

#include <map>
#include <set>

namespace{
    template<typename T, T default_value>
    class InfiniteVector{
    private:   
        T _default_value = default_value;
        std::pair<size_t, T> _tmp;
        bool _tmpSaved = true;
        std::map<size_t, T> _array;
        void saveTmp(){
            if(!_tmpSaved){
                if(_tmp.second != _default_value){
                    _array[_tmp.first] = _tmp.second;
                }
                else{
                    _array.erase(_tmp.first);
                }
                _tmp.second = _default_value;
                _tmpSaved = true;
            }
        }
    public:
        InfiniteVector() : _tmp{0, _default_value} {};
        ~InfiniteVector(){};
        T& operator[](const size_t index){
            saveTmp();
            _tmpSaved = false;
            if(_array.find(index) != _array.end()){
                _tmp.second = _array[index];
            }
            _tmp.first = index;
            return _tmp.second;
        }
        size_t size(){
            saveTmp();
            return _array.size();
        }
    };
}

template<typename T, T default_value>
class InfiniteMatrix2D{
private:
    T _default_value = default_value;
    using InfVec = InfiniteVector<T, default_value>;
    std::map<size_t, InfVec> _array;
public:
    InfiniteMatrix2D() {};
    InfiniteMatrix2D(InfiniteMatrix2D& /* other */) {};
    InfiniteMatrix2D(InfiniteMatrix2D&& /* other */) {};
    InfiniteMatrix2D& operator=(InfiniteMatrix2D& /* other */) {};
    InfiniteMatrix2D& operator=(InfiniteMatrix2D&& /* other */) {};
    ~InfiniteMatrix2D() {};

    InfVec& operator[](const size_t index){
        _array.emplace(std::make_pair(index, InfVec()));
        return _array[index];
    }
    size_t size(){
        size_t res = 0;
        for(auto& arr : _array){
            res += arr.second.size();
        }
        return res;
    }
};