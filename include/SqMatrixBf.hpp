#pragma once

#include "VLA.hpp"

template <typename T>
class SqMatrixBf final {
    size_t n;
    buffers::VLA<T> data;

    public:

    SqMatrixBf(size_t n_, buffers::VLA<T> &&data_ = T{});

    class ProxyRow {
        typename buffers::VLA<T>::iterator row_data;
        public:
        ProxyRow(typename buffers::VLA<T>::iterator row_) : row_data{row_} {}

        T &operator[](size_t col) {
            return *(row_data + col);
        }

        const T &operator[](size_t col) const {
            return *(row_data + col);
        }
    };

    class ConstProxyRow {
        typename buffers::VLA<T>::const_iterator row_data;
        public:
        ConstProxyRow(typename buffers::VLA<T>::const_iterator row_) 
            : row_data{row_} {}

        T &operator[](size_t col) {
            return *(row_data + col);
        }

        const T &operator[](size_t col) const {
            return *(row_data + col);
        }
    };

    ProxyRow operator[](size_t row) {
        using iter  = typename buffers::VLA<T>::iterator;
        using iter_diff = typename std::iterator_traits<iter>::difference_type;
        return ProxyRow(std::next(data.begin(), 
                                  static_cast<iter_diff>(n * row)));
    }

    const ConstProxyRow operator[](size_t row) const {
        using iter  = typename buffers::VLA<T>::const_iterator;
        using iter_diff = typename std::iterator_traits<iter>::difference_type;
        return ConstProxyRow(std::next(data.cbegin(), 
                                       static_cast<iter_diff>(n * row)));
    }

    size_t size() const; 

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

    T det_gauss    (void) const;
    T det_recursion(void) const;
    T det_bareiss  (void) const;
    T det_lu       (void) const;
    T det_cholesky (void) const;
};

template <typename T>
SqMatrixBf<T> operator*(const T &value, const SqMatrixBf<T> &mat);

#include "detail/SqMatrixBf.tpp"
