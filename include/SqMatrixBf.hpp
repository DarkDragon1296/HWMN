#pragma once

#include <vector> // TODO: write our version

template <typename T>
class SqMatrixBf final {
    size_t n;
    std::vector<T> data;

    public:

    SqMatrixBf(size_t n_, std::vector<T> &&data_ = T{});

    class ProxyRow {
        typename std::vector<T>::iterator row_data;
        public:
        ProxyRow(typename std::vector<T>::iterator row_) : row_data{row_} {}

        T &operator[](size_t col) {
            return *(row_data + static_cast<int>(col));
        }

        const T &operator[](size_t col) const {
            return *(row_data + static_cast<int>(col));
        }
    };

    class ConstProxyRow {
        typename std::vector<T>::const_iterator row_data;
        public:
        ConstProxyRow(typename std::vector<T>::const_iterator row_) :
                      row_data{row_} {}

        T &operator[](size_t col) {
            return *(row_data + static_cast<int>(col));
        }

        const T &operator[](size_t col) const {
            return *(row_data + static_cast<int>(col));
        }
    };

    ProxyRow operator[](size_t row) {
        return ProxyRow(std::next(data.begin(), static_cast<int>(n * row)));
    }

    const ConstProxyRow operator[](size_t row) const {
        return ConstProxyRow(std::next(data.cbegin(),
                                       static_cast<int>(n * row)));
    }

    size_t size() const { /* TODO: move realization */
        return n;
    }

    /* TODO: check SqMatrixBf &method() &; */

    SqMatrixBf operator+(const SqMatrixBf &mat) const;
    SqMatrixBf operator-(const SqMatrixBf &mat) const;
    SqMatrixBf operator*(const T &value) const;
    SqMatrixBf operator/(const T &value) const;

    void operator+=(const SqMatrixBf &mat);
    void operator-=(const SqMatrixBf &mat);
    void operator*=(const T &value);
    void operator/=(const T &value);

    void swap_rows(size_t i, size_t j);
    void swap_cols(size_t i, size_t j);

    void add_row(size_t i, size_t j, T coeff);
    void add_col(size_t i, size_t j, T coeff);
    void sub_row(size_t i, size_t j, T coeff);
    void sub_col(size_t i, size_t j, T coeff);

    void mul_row(size_t row, T value);
    void mul_col(size_t col, T value);
    void div_row(size_t row, T value);
    void div_col(size_t col, T value);

    size_t max_row_elem_index(size_t row, size_t start) const;
    size_t max_col_elem_index(size_t col, size_t start) const;

    SqMatrixBf minor(size_t row, size_t col) const;
    SqMatrixBf mul(const SqMatrixBf &mat) const;
    SqMatrixBf transpose(void) const;
    SqMatrixBf neg(void) const;
    T tr(void) const;
    T det_gauss(void) const;
    T det_recursion(void) const;
    T det_bareiss(void) const;
    T det_lu(void) const;
};

template <typename T>
SqMatrixBf<T> operator*(const T &value, const SqMatrixBf<T> &mat);

#include "SqMatrixBf.tpp"