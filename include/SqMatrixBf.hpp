#pragma once

#include <iostream>
#include <vector> // TODO: write our version

template <typename T>
class SqMatrixBf {
    size_t n;
    std::vector<T> data;

    public:

    SqMatrixBf(size_t n_, std::vector<T> &&data_ = T{});

#if 0
    SqMatrixBf(const SqMatrixBf &rhs) = default;
    SqMatrixBf(SqMatrixBf &&rhs) noexcept;
    SqMatrixBf &operator=(const SqMatrixBf &rhs) = default;
    SqMatrixBf &operator=(SqMatrixBf &&rhs) noexcept;
    ~SqMatrixBf();
#endif

    class ProxyRow {
        typename std::vector<T>::iterator row_data;
        public:
        ProxyRow(typename std::vector<T>::iterator row_) : row_data{row_} {}

        T &operator[](int col) {
            return *(row_data + col);
        }

        const T &operator[](int col) const {
            return *(row_data + col);
        }
    };

    class ConstProxyRow {
        typename std::vector<T>::const_iterator row_data;
        public:
        ConstProxyRow(typename std::vector<T>::const_iterator row_) :
                      row_data{row_} {}

        T &operator[](int col) {
            return *(row_data + col);
        }

        const T &operator[](int col) const {
            return *(row_data + col);
        }
    };

    ProxyRow operator[](int row) {
        return ProxyRow(std::next(data.begin(), static_cast<int>(n) * row));
    }

    const ConstProxyRow operator[](int row) const {
        return ConstProxyRow(std::next(data.cbegin(),
                                       static_cast<int>(n) * row));
    }

    size_t size() const {
        return n;
    }

    SqMatrixBf operator+(const SqMatrixBf &mat) const;
    SqMatrixBf operator-(const SqMatrixBf &mat) const;
    SqMatrixBf operator*(const SqMatrixBf &mat) const;
    SqMatrixBf operator*(const T &value) const;
    void operator+=(const SqMatrixBf &mat);
    void operator-=(const SqMatrixBf &mat);
    void operator*=(const SqMatrixBf &mat);
    void operator*=(const T &value);

    SqMatrixBf transpose(void);
    SqMatrixBf neg(void);
    SqMatrixBf inverse(void);

    void swap_rows(int i, int j);
    void swap_cols(int i, int j);
};

#include "SqMatrixBf.tpp"