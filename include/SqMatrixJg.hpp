#pragma once

#include <iostream>
#include <vector>

template <typename T>
class SqMatrixJg {
    size_t n;
    std::vector<std::vector<T>> data{};

    public:

    SqMatrixJg(size_t n_, std::vector<T> &&data_ = T{});

    class ProxyRow {
        std::vector<T> row_data;
        public:
        ProxyRow(std::vector<T> row_data_) : row_data{std::move(row_data_)} {}

        T &operator[](int col) {
            return row_data[static_cast<size_t>(col)];
        }

        const T &operator[](int col) const {
            return row_data[static_cast<size_t>(col)];
        }
    };

    class ConstProxyRow {
        std::vector<T> row_data;
        public:
        ConstProxyRow(std::vector<T> row_data_) : row_data{std::move(row_data_)} {}

        T &operator[](int col) {
            return row_data[static_cast<size_t>(col)];
        }

        const T &operator[](int col) const {
            return row_data[static_cast<size_t>(col)];
        }
    };

    ProxyRow operator[](int row) {
        return ProxyRow(data[static_cast<size_t>(row)]);
    }

    const ConstProxyRow operator[](int row) const {
        return ConstProxyRow(data[static_cast<size_t>(row)]);
    }

    size_t size() const {
        return n;
    }
};

template <typename T>
SqMatrixJg<T>::SqMatrixJg(size_t n_, std::vector<T> &&data_) : n{n_} {
    data.resize(n, std::vector<T>(n, 0));
    size_t sz = data_.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (i * n + j >= sz)
                return;
            data[i][j] = data_[i * n + j];
        }
    }
};