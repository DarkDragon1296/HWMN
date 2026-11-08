#pragma once

#include "VLA.hpp"
#include <ostream>

namespace mat {

template <typename T>
class SqMatrixJg final {
    private:
    size_t n = 0;
    buffers::VLA<T> data;
    buffers::VLA<size_t> row_offsets;

    public:
    SqMatrixJg() = default;
    explicit SqMatrixJg(size_t n_);
    SqMatrixJg(size_t n_, std::initializer_list<T> values);
    static SqMatrixJg create_scalar(size_t n_, T value);
    static SqMatrixJg create_eye(size_t n_, T identity_value);

    template <bool Constness>
    class ProxyRow {
        using It = std::conditional_t<Constness, 
                                      typename buffers::VLA<T>::const_iterator,
                                      typename buffers::VLA<T>::iterator>;
        It row_data;
        public:
        ProxyRow(It row_);
        decltype(auto) operator[](size_t col) const;
    };

    ProxyRow<false> operator[](size_t row);
    ProxyRow<true>  operator[](size_t row) const;

    size_t size() const; 

    void dump(std::ostream& sink) const;

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

    size_t max_row_elem_index(size_t row, size_t start) const;
    size_t max_col_elem_index(size_t col, size_t start) const;

    SqMatrixJg minor(size_t row, size_t col) const;
    SqMatrixJg mul(const SqMatrixJg &mat) const;
    SqMatrixJg transpose(void) const;
    SqMatrixJg neg(void) const;
    T tr(void) const;

    T det_gauss    (void) const;
    T det_recursion(void) const;
    T det_bareiss  (void) const;
    T det_lu       (void) const;
    T det_cholesky (void) const;
};

template <typename T>
SqMatrixJg<T> operator+(const SqMatrixJg<T> lhs, const SqMatrixJg<T> &rhs);

template <typename T>
SqMatrixJg<T> operator-(const SqMatrixJg<T> lhs, const SqMatrixJg<T> &rhs);

template <typename T>
SqMatrixJg<T> operator*(const SqMatrixJg<T> lhs, const T &rhs);

template <typename T>
SqMatrixJg<T> operator*(const T &lhs, const SqMatrixJg<T> rhs);

template <typename T>
SqMatrixJg<T> operator/(const SqMatrixJg<T> lhs, const T &rhs);

}

#include "detail/SqMatrixJg.tpp"
