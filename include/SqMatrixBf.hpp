#pragma once

#include <iostream>
#include <vector> // TODO: write our version

template <typename T>
class SqMatrixBf {
    size_t n;
    std::vector<T> data;

    public:

    SqMatrixBf(size_t n_, std::vector<T> &&data_ = T{});

    size_t size() const {
        return n;
    }

    class RowProxy {
        typename std::vector<T>::iterator row_data;
        public:
        RowProxy(typename std::vector<T>::iterator row_) : row_data{row_} {}

        T &operator[](int col) {
            return *(row_data + col);
        }

        const T &operator[](int col) const {
            return *(row_data + col);
        }
    };

    class ConstRowProxy {
        typename std::vector<T>::const_iterator row_data;
        public:
        ConstRowProxy(typename std::vector<T>::const_iterator row_) :
                      row_data{row_} {}

        T &operator[](int col) {
            return *(row_data + col);
        }

        const T &operator[](int col) const {
            return *(row_data + col);
        }
    };

    RowProxy operator[](int row) {
        return RowProxy(std::next(data.begin(), static_cast<int>(n) * row));
    }

    const ConstRowProxy operator[](int row) const {
        return ConstRowProxy(std::next(data.cbegin(),
                                       static_cast<int>(n) * row));
    }

    SqMatrixBf operator+(const SqMatrixBf &mat) const;
    SqMatrixBf operator-(const SqMatrixBf &mat) const;
    SqMatrixBf operator*(const SqMatrixBf &mat) const;
    SqMatrixBf operator*(const T &value) const;
    void operator+=(const SqMatrixBf &mat);
    void operator-=(const SqMatrixBf &mat);
    void operator*=(const SqMatrixBf &mat);
    void operator*=(const T &value);
};

#include "SqMatrixBf.tpp"