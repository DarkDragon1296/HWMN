#pragma once

#include <iostream>
#include <vector>

template <typename T>
class SqMatrixJg {
    size_t n;
    std::vector<std::vector<T>> data;

    public:

    SqMatrixJg(size_t n_, std::vector<T> &&data_ = T{});

    class ProxyRow {
        std::vector<T> row_data;
        public:
        ProxyRow(std::vector<T> row_data_) : row_data{std::move(row_data_)} {}

        T &operator[](int col) {
            return row_data[col];
        }

        const T &operator[](int col) const {
            return row_data[col];
        }
    };

    class ConstProxyRow {
        std::vector<T> row_data;
        public:
        ConstProxyRow(std::vector<T> row_data_) : row_data{std::move(row_data_)} {}

        T &operator[](int col) {
            return *(row_data + col);
        }

        const T &operator[](int col) const {
            return *(row_data + col);
        }
    };

    ProxyRow operator[](int row) {
        return ProxyRow(data[row]);
    }

    const ConstProxyRow operator[](int row) const {
        return ConstProxyRow(data[row]);
    }

    size_t size() const {
        return n;
    }
};

template <typename T>
SqMatrixJg<T>::SqMatrixJg(size_t n_, std::vector<T> &&data_) : n{n_} {
    data.resize(n, std::vector<T>(n, 0));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            data[i][j] = data_[i * n + j];

            if (i * n + j >= n_)
                return;
        }
    }
};