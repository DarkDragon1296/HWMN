#pragma once

#include <iostream>
#include <vector> // TODO: write our version

template <typename T>
class SqMatrixBf {
    size_t n;
    std::vector<T> data;

    public:

    SqMatrixBf(size_t n_, std::vector<T> &&data_ = T{});

    T get_elem(size_t i, size_t j) const {
        return data[i * n + j];
    }

    size_t size() const {
        return n;
    }

    class RowProxy {
        typename std::vector<T>::iterator row_data;
        public:
        RowProxy(typename std::vector<T>::iterator row_) : row_data{row_} {}

        T &operator[](size_t col) {
            return *(row_data + col);
        }

        const T &operator[](size_t col) const {
            return *(row_data + col);
        }
    };

    RowProxy operator[](size_t row) {
        return RowProxy(data.begin() + n * row);
    }
#if 0
    SqMatrixBf operator+(const SqMatrixBf& mat) const {
        SqMatrixBf<T> res_mat(n, {});

        for (size_t i = 0; i < n; i++) { 
            for (size_t j = 0; j < n; j++) {
                res_mat[i][j] = (*this)[i][j] + mat[i][j];
            }
        }

        return res_mat;
    }

    void operator+=(const SqMatrixBf& mat) {
        for (size_t i = 0; i < n; i++) { 
            for (size_t j = 0; j < n; j++) {
                set_elem(i, j, get_elem(i, j) + mat.get_elem(i, j));
            }
        }
    }
#endif
};

template <typename T>
SqMatrixBf<T>::SqMatrixBf(size_t n_, std::vector<T> &&data_) :
                          n{n_}, data{std::move(data_)}
{
        data.resize(n * n);
};