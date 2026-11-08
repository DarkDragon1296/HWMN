#pragma once

#include "SqMatrixBf.hpp"
#include "detail/SqMatrixOp.tpp"

namespace mat {

template <typename T>
SqMatrixBf<T>::SqMatrixBf(size_t n_) 
    : n{n_}, 
      data{buffers::VLA<T>::create(n_ * n_)} {}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::create_scalar(size_t n_, T value) {
    SqMatrixBf<T> mat;
    mat.data = buffers::VLA<T>::create(n_ * n_, value);
    mat.n = n_;
    return mat;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::create_eye(size_t n_, T identity_value) {
    SqMatrixBf<T> mat(n_);
    for (size_t i = 0; i < n_; i++)
        mat[i][i] = identity_value;

    return mat;
}

template <typename T>
SqMatrixBf<T>::SqMatrixBf(size_t n_, 
                          std::initializer_list<T> values)
    : n{n_}, 
      data(n_ * n_, values) {} // Fun fact! () matter here specifically

template <typename T>
size_t SqMatrixBf<T>::size() const { 
    return n;
}

template <typename T>
void SqMatrixBf<T>::dump(std::ostream &sink) const {
    operations::dump<SqMatrixBf<T>>(*this, sink);
}

template <typename T>
template <bool Constness>
SqMatrixBf<T>::ProxyRow<Constness>::ProxyRow(It row_) : row_data{row_} {}

template <typename T>
template <bool Constness>
decltype(auto) // the return type is deduced (either const T& or T&) 
SqMatrixBf<T>::ProxyRow<Constness>::operator[](size_t col) const {
    return row_data[col];
}

template <typename T>
typename SqMatrixBf<T>::template ProxyRow<false> 
SqMatrixBf<T>::operator[](size_t row) {
    return ProxyRow<false>(data.begin() + n * row);
}

template <typename T>
typename SqMatrixBf<T>::template ProxyRow<true> 
SqMatrixBf<T>::operator[](size_t row) const {
    return ProxyRow<true>(data.cbegin() + n * row);
}

template <typename T>
SqMatrixBf<T> operator+(SqMatrixBf<T> lhs, const SqMatrixBf<T> &rhs) {
    lhs += rhs;
    return lhs;
}

template <typename T>
SqMatrixBf<T> operator-(SqMatrixBf<T> lhs, const SqMatrixBf<T> &rhs) {
    lhs -= rhs;
    return lhs;
}

template <typename T>
SqMatrixBf<T> operator*(const SqMatrixBf<T> &lhs, const T &rhs) {
    lhs *= rhs;
    return lhs;
}

template <typename T>
SqMatrixBf<T> operator*(const T &lhs, const SqMatrixBf<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
SqMatrixBf<T> operator/(const SqMatrixBf<T> &lhs, const T &rhs) {
    lhs /= rhs;
    return lhs;
}

template <typename T>
void SqMatrixBf<T>::operator+=(const SqMatrixBf &mat) {
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] += mat[i][j];
        }
    }
}

template <typename T>
void SqMatrixBf<T>::operator-=(const SqMatrixBf &mat) {
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] -= mat[i][j];
        }
    }
}

template <typename T>
void SqMatrixBf<T>::operator*=(const T &value) {
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] *= value;
        }
    }
}

template <typename T>
void SqMatrixBf<T>::operator/=(const T &value) {
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] /= value;
        }
    }
}

template <typename T>
void SqMatrixBf<T>::swap_rows(size_t i, size_t j) {
    T tmp;
    for (size_t l = 0; l < n; l++) {
        tmp = (*this)[i][l];
        (*this)[i][l] = (*this)[j][l];
        (*this)[j][l] = tmp;
    }
}

template <typename T>
void SqMatrixBf<T>::swap_cols(size_t i, size_t j) {
    operations::swap_cols<SqMatrixBf<T>, T>(*this, i, j);
}

template <typename T>
void SqMatrixBf<T>::add_row(size_t i, size_t j, T coeff) {
    operations::add_row<SqMatrixBf<T>, T>(*this, i, j, coeff);
}

template <typename T>
void SqMatrixBf<T>::add_col(size_t i, size_t j, T coeff) {
    operations::add_col<SqMatrixBf<T>, T>(*this, i, j, coeff);
}

template <typename T>
void SqMatrixBf<T>::sub_row(size_t i, size_t j, T coeff) {
    operations::sub_row<SqMatrixBf<T>, T>(*this, i, j, coeff);
}

template <typename T>
void SqMatrixBf<T>::sub_col(size_t i, size_t j, T coeff) {
    operations::sub_col<SqMatrixBf<T>, T>(*this, i, j, coeff);
}

template <typename T>
void SqMatrixBf<T>::mul_row(size_t row, T value) {
    operations::mul_row(*this, row, value);
}

template <typename T>
void SqMatrixBf<T>::mul_col(size_t col, T value) {
    operations::mul_col(*this, col, value);
}

template <typename T>
void SqMatrixBf<T>::div_row(size_t row, T value) {
    operations::div_row(*this, row, value);
}

template <typename T>
void SqMatrixBf<T>::div_col(size_t col, T value) {
    operations::div_col(*this, col, value);
}

template <typename T>
size_t SqMatrixBf<T>::max_row_elem_index(size_t row, size_t start) const {
    return operations::max_row_elem_index<SqMatrixBf<T>, T>(*this, row, start);
}

template <typename T>
size_t SqMatrixBf<T>::max_col_elem_index(size_t col, size_t start) const {
    return operations::max_col_elem_index<SqMatrixBf<T>, T>(*this, col, start);
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::minor(size_t row, size_t col) const {
    return operations::minor(*this, row, col);
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::mul(const SqMatrixBf<T> &mat) const {
    return operations::mul(*this, mat);
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::transpose(void) const {
    return operations::transpose(*this);
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::neg(void) const {
    return operations::neg(*this);
}

template <typename T>
T SqMatrixBf<T>::tr(void) const {
    return operations::tr<SqMatrixBf<T>, T>(*this);
}

template <typename T>
T SqMatrixBf<T>::det_recursion(void) const {
    return operations::det_recursion<SqMatrixBf<T>, T>(*this);
}

template <typename T>
T SqMatrixBf<T>::det_gauss(void) const {
    return operations::det_gauss<SqMatrixBf<T>, T>(*this);
}

template <typename T>
T SqMatrixBf<T>::det_bareiss(void) const {
    return operations::det_bareiss<SqMatrixBf<T>, T>(*this);
}

template <typename T>
T SqMatrixBf<T>::det_lu(void) const {
    return operations::det_lu<SqMatrixBf<T>, T>(*this);
}
    
template <typename T>
T SqMatrixBf<T>::det_cholesky(void) const {
    return operations::det_cholesky<SqMatrixBf<T>, T>(*this);
}

}
