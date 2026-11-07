#pragma once

#include <vector>

template <typename T>
class SqMatrixJg final {
    size_t n;
    std::vector<std::vector<T>> data{};

    public:

    SqMatrixJg(size_t n_, std::vector<T> &&data_ = T{});

    std::vector<T> &operator[](size_t row) {
        return data[row];
    }

    const std::vector<T> &operator[](size_t row) const {
        return data[row];
    }

    size_t size() const { /* TODO: move realization */
        return n;
    }

    SqMatrixJg operator+(const SqMatrixJg &mat) const;
    SqMatrixJg operator-(const SqMatrixJg &mat) const;
    SqMatrixJg operator*(const T &value) const;
    SqMatrixJg operator/(const T &value) const;

    void operator+=(const SqMatrixJg &mat);
    void operator-=(const SqMatrixJg &mat);
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
    size_t max_row_elem_index(size_t row) const;
    size_t max_col_elem_index(size_t col) const;

    SqMatrixJg minor(size_t row, size_t col) const;
    SqMatrixJg mul(const SqMatrixJg &mat) const;
    SqMatrixJg transpose(void) const;
    SqMatrixJg neg(void) const;
    T tr(void) const;
    T det_gauss(void) const;
    T det_recursion(void) const;
    T det_bareiss(void) const;
    T det_lu(void) const;
};

#include "SqMatrixJg.tpp"