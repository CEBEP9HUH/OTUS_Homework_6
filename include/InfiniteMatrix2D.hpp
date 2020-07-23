#pragma once

#include <map>

namespace{
    template<typename T, T default_value>
    class MatrixData{
    private:
        const T _default_value = default_value;
        using _index_t = std::pair<size_t, size_t>;
        std::map<_index_t, T> _matrix;
    public:
        MatrixData() : _matrix{} {};
        MatrixData(const MatrixData&) = default; 
        MatrixData(MatrixData&&) = default; 
        MatrixData& operator=(const MatrixData&) = default; 
        MatrixData& operator=(MatrixData&&) = default; 
        ~MatrixData() = default;

        T get(const _index_t indexes) {
            if(_matrix.find(indexes) != _matrix.end()){
                return _matrix[indexes];
            }
            return _default_value;
        }
        T insert(const _index_t indexes, const T& value){
            if(value != _default_value){
                _matrix[indexes] = value;
            }
            else{
                _matrix.erase(indexes);
            }
            return get(indexes);
        }
        size_t size() const {
            return _matrix.size();
        }
        auto begin(){
            return _matrix.begin();
        }
        auto end(){
            return _matrix.end();
        }
    };

    template<typename T, T default_value>
    class MatrixProxy{
    private:
        using _index_t = std::pair<size_t, size_t>;
        using _data_t = MatrixData<T, default_value>;
        _data_t& _data;
        _index_t _indexes;
    public:
        MatrixProxy(_data_t& data, const size_t row, const size_t col) : _data{data}, _indexes{row, col} {};
        MatrixProxy(const MatrixProxy&) = default; 
        MatrixProxy(MatrixProxy&&) = default; 
        MatrixProxy& operator=(const MatrixProxy&) = default; 
        MatrixProxy& operator=(MatrixProxy&&) = default; 
        ~MatrixProxy() = default;
        bool operator==(const T& value) const {
            return _data.get(_indexes) == value;
        }
        T operator=(const T& value){
            return _data.insert(_indexes, value);
        }
        operator T() const {
            return _data.get(_indexes);
        }
    };

    template<typename T, T default_value>
    class MatrixCol{
    private:
        using _data_t = MatrixData<T, default_value>;
        using _matrix_proxy_t = MatrixProxy<T, default_value>;
        _data_t& _data;
        size_t _own_index;
    public:
        MatrixCol(_data_t& data, const size_t own_index) :   _data(data), 
                                                            _own_index{own_index} {};
        MatrixCol(const MatrixCol&) = default; 
        MatrixCol(MatrixCol&&) = default; 
        MatrixCol& operator=(const MatrixCol&) = default; 
        MatrixCol& operator=(MatrixCol&&) = default; 
        ~MatrixCol() = default;
        _matrix_proxy_t operator[](const size_t index) const {
            return _matrix_proxy_t(_data, _own_index, index);
        }
    };
}

template<typename T, T default_value>
class InfiniteMatrix2D{
private:
    using _data_t = MatrixData<T, default_value>;
    using _col_t = MatrixCol<T, default_value>;
    _data_t _data;
public:
    InfiniteMatrix2D() = default;
    InfiniteMatrix2D(InfiniteMatrix2D&) = default;
    InfiniteMatrix2D(InfiniteMatrix2D&&) = default;
    InfiniteMatrix2D& operator=(InfiniteMatrix2D&) = default;
    InfiniteMatrix2D& operator=(InfiniteMatrix2D&&) = default;
    ~InfiniteMatrix2D() {};
    class iterator{
    private:
        using _init_t = decltype(_data.begin());
        using _iter_t = std::tuple<size_t, size_t, T>;
        _init_t _iter;
    public:
        iterator(_init_t i) : _iter{i} {};
        ~iterator() = default;
        iterator operator++(){ iterator iter = *this; _iter++; return iter;}
        iterator operator++(int i) {_iter++; return *this;}
        _iter_t operator*() const {return std::make_tuple(_iter->first.first, _iter->first.second, _iter->second);}
        _init_t operator->() const {return _iter;}
        bool operator==(const iterator& other) const {return _iter == other._iter;}
        bool operator!=(const iterator& other) const {return !(*this == other);}
    };
    _col_t operator[](const size_t index){
        return _col_t(_data, index);
    }
    size_t size() const{
        return _data.size();
    }
    auto begin(){
        return iterator(_data.begin());
    }
    auto end(){
        return iterator(_data.end());
    }
};