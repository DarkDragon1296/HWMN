#pragma once

#include "SqMatrixOp.tpp"

template <typename T>
SqMatrixBf<T>::SqMatrixBf(size_t n_, std::vector<T> &&data_) :
                          n{n_}, data{std::move(data_)}
{
    data.resize(n * n);
};

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::operator+(const SqMatrixBf &mat) const {
    SqMatrixBf<T> res_mat(n, {});
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            res_mat[i][j] = (*this)[i][j] + mat[i][j];
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::operator-(const SqMatrixBf &mat) const {
    SqMatrixBf<T> res_mat(n, {});
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            res_mat[i][j] = (*this)[i][j] - mat[i][j];
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::operator*(const T &value) const {
    SqMatrixBf<T> res_mat(n, {});
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            res_mat[i][j] = (*this)[i][j] * value;
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixBf<T> operator*(const T &value, const SqMatrixBf<T> &mat) {
    return mat * value;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::operator/(const T &value) const {
    SqMatrixBf<T> res_mat(n, {});
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            res_mat[i][j] = (*this)[i][j] / value;
        }
    }
    return res_mat;
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
    T tmp;
    for (int l = 0; l < n; l++) {
        tmp = (*this)[l][i];
        (*this)[l][i] = (*this)[l][j];
        (*this)[l][j] = tmp;
    }
}

template <typename T>
void SqMatrixBf<T>::sum_rows(size_t i, size_t j) {
    operations::sum_rows(*this, i, j);
}

template <typename T>
void SqMatrixBf<T>::sum_cols(size_t i, size_t j) {
    operations::sum_cols(*this, i, j);
}

template <typename T>
void SqMatrixBf<T>::sub_rows(size_t i, size_t j) {
    operations::sub_rows(*this, i, j);
}

template <typename T>
void SqMatrixBf<T>::sub_cols(size_t i, size_t j) {
    operations::sub_cols(*this, i, j);
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
size_t SqMatrixBf<T>::max_row_elem_index(size_t row) const {
    return operations::max_row_elem_index<SqMatrixBf<T>, T>(*this, row);
}

template <typename T>
size_t SqMatrixBf<T>::max_col_elem_index(size_t col) const {
    return operations::max_col_elem_index<SqMatrixBf<T>, T>(*this, col);
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
T SqMatrixBf<T>::tr(void) {
    return operations::tr<SqMatrixBf<T>, T>(*this);
}

template <typename T>
T SqMatrixBf<T>::det_recursion(void) const {
    return operations::det_recursion<SqMatrixBf<T>, T>(*this);
}