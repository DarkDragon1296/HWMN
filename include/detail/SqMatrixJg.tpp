#pragma once

#include "SqMatrixJg.hpp"
#include "detail/SqMatrixOp.tpp"

namespace mat {

template <typename T>
SqMatrixJg<T>::SqMatrixJg(size_t n_) 
    : n{n_}, 
      data{buffers::VLA<T>::create(n_ * n_)},
      row_offsets{buffers::VLA<size_t>::create(n_)}
{
    for (size_t i = 0; i < n; i++)
        row_offsets[i] = i * n;
}

template <typename T>
SqMatrixJg<T>::SqMatrixJg(size_t n_, 
                          std::initializer_list<T> values)
    : n{n_}, 
      data(n_ * n_, values),
      row_offsets{buffers::VLA<size_t>::create(n_)}
{
    for (size_t i = 0; i < n; i++)
        row_offsets[i] = i * n;
} 

template <typename T>
SqMatrixJg<T> SqMatrixJg<T>::create_scalar(size_t n_, T value) {
    SqMatrixJg<T> mat;
    mat.data = buffers::VLA<T>::create(n_ * n_, value);
    mat.row_offsets = buffers::VLA<size_t>::create(n_);
    for (size_t i = 0; i < n_; i++)
        mat.row_offsets[i] = i * n_;
    mat.n = n_;
    return mat;
}

template <typename T>
SqMatrixJg<T> create_eye(size_t n_, T identity_value) {
    SqMatrixJg<T> mat(n_);
    for (size_t i = 0; i < n_; i++)
        mat[i][i] = identity_value;

    return mat;
}

template <typename T>
size_t SqMatrixJg<T>::size() const { 
    return n;
}

template <typename T>
void SqMatrixJg<T>::dump(std::ostream &sink) const {
    operations::dump<SqMatrixJg<T>>(*this, sink);
}

template <typename T>
template <bool Constness>
SqMatrixJg<T>::ProxyRow<Constness>::ProxyRow(It row_) : row_data{row_} {}

template <typename T>
template <bool Constness>
decltype(auto) // the return type is deduced (either const T& or T&) 
SqMatrixJg<T>::ProxyRow<Constness>::operator[](size_t col) const {
    return row_data[col];
}

template <typename T>
typename SqMatrixJg<T>::template ProxyRow<false> 
SqMatrixJg<T>::operator[](size_t row) {
    return ProxyRow<false>(data.begin() + row_offsets[row]);
}

template <typename T>
typename SqMatrixJg<T>::template ProxyRow<true> 
SqMatrixJg<T>::operator[](size_t row) const {
    return ProxyRow<true>(data.cbegin() + row_offsets[row]);
}

template <typename T>
SqMatrixJg<T> operator+(SqMatrixJg<T> lhs, const SqMatrixJg<T> &rhs) {
    lhs += rhs;
    return lhs;
}

template <typename T>
SqMatrixJg<T> operator-(SqMatrixJg<T> lhs, const SqMatrixJg<T> &rhs) {
    lhs -= rhs;
    return lhs;
}

template <typename T>
SqMatrixJg<T> operator*(const SqMatrixJg<T> &lhs, const T &rhs) {
    lhs *= rhs;
    return lhs;
}

template <typename T>
SqMatrixJg<T> operator*(const T &lhs, const SqMatrixJg<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
SqMatrixJg<T> operator/(const SqMatrixJg<T> &lhs, const T &rhs) {
    lhs /= rhs;
    return lhs;
}

template <typename T>
void SqMatrixJg<T>::operator+=(const SqMatrixJg &mat) {
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] += mat[i][j];
        }
    }
}

template <typename T>
void SqMatrixJg<T>::operator-=(const SqMatrixJg &mat) {
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] -= mat[i][j];
        }
    }
}

template <typename T>
void SqMatrixJg<T>::operator*=(const T &value) {
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] *= value;
        }
    }
}

template <typename T>
void SqMatrixJg<T>::operator/=(const T &value) {
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] /= value;
        }
    }
}

template <typename T>
void SqMatrixJg<T>::swap_rows(size_t i, size_t j) {
    std::swap(row_offsets[i], row_offsets[j]);
}

template <typename T>
void SqMatrixJg<T>::swap_cols(size_t i, size_t j) {
    operations::swap_cols<SqMatrixJg<T>, T>(*this, i, j);
}

template <typename T>
void SqMatrixJg<T>::add_row(size_t i, size_t j, T coeff) {
    operations::add_row<SqMatrixJg<T>, T>(*this, i, j, coeff);
}

template <typename T>
void SqMatrixJg<T>::add_col(size_t i, size_t j, T coeff) {
    operations::add_col<SqMatrixJg<T>, T>(*this, i, j, coeff);
}

template <typename T>
void SqMatrixJg<T>::sub_row(size_t i, size_t j, T coeff) {
    operations::sub_row<SqMatrixJg<T>, T>(*this, i, j, coeff);
}

template <typename T>
void SqMatrixJg<T>::sub_col(size_t i, size_t j, T coeff) {
    operations::sub_col<SqMatrixJg<T>, T>(*this, i, j, coeff);
}

template <typename T>
void SqMatrixJg<T>::mul_row(size_t row, T value) {
    operations::mul_row(*this, row, value);
}

template <typename T>
void SqMatrixJg<T>::mul_col(size_t col, T value) {
    operations::mul_col(*this, col, value);
}

template <typename T>
void SqMatrixJg<T>::div_row(size_t row, T value) {
    operations::div_row(*this, row, value);
}

template <typename T>
void SqMatrixJg<T>::div_col(size_t col, T value) {
    operations::div_col(*this, col, value);
}

template <typename T>
size_t SqMatrixJg<T>::max_row_elem_index(size_t row, size_t start) const {
    return operations::max_row_elem_index<SqMatrixJg<T>, T>(*this, row, start);
}

template <typename T>
size_t SqMatrixJg<T>::max_col_elem_index(size_t col, size_t start) const {
    return operations::max_col_elem_index<SqMatrixJg<T>, T>(*this, col, start);
}

template <typename T>
SqMatrixJg<T> SqMatrixJg<T>::minor(size_t row, size_t col) const {
    return operations::minor(*this, row, col);
}

template <typename T>
SqMatrixJg<T> SqMatrixJg<T>::mul(const SqMatrixJg<T> &mat) const {
    return operations::mul(*this, mat);
}

template <typename T>
SqMatrixJg<T> SqMatrixJg<T>::transpose(void) const {
    return operations::transpose(*this);
}

template <typename T>
SqMatrixJg<T> SqMatrixJg<T>::neg(void) const {
    return operations::neg(*this);
}

template <typename T>
T SqMatrixJg<T>::tr(void) const {
    return operations::tr<SqMatrixJg<T>, T>(*this);
}

template <typename T>
T SqMatrixJg<T>::det_recursion(void) const {
    return operations::det_recursion<SqMatrixJg<T>, T>(*this);
}

template <typename T>
T SqMatrixJg<T>::det_gauss(void) const {
    return operations::det_gauss<SqMatrixJg<T>, T>(*this);
}

template <typename T>
T SqMatrixJg<T>::det_bareiss(void) const {
    return operations::det_bareiss<SqMatrixJg<T>, T>(*this);
}

template <typename T>
T SqMatrixJg<T>::det_lu(void) const {
    return operations::det_lu<SqMatrixJg<T>, T>(*this);
}
    
template <typename T>
T SqMatrixJg<T>::det_cholesky(void) const {
    return operations::det_cholesky<SqMatrixJg<T>, T>(*this);
}

}
