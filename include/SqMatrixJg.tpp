#pragma once

#include "SqMatrixOp.tpp"

template <typename T>
SqMatrixJg<T>::SqMatrixJg(size_t n_, std::vector<T> &&data_) : n{n_} {
    size_t sz = data_.size();
    data.resize(n, std::vector<T>(n, T{}));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (i * n + j >= sz)
                return;
            data[i][j] = data_[i * n + j];
        }
    }
};

template <typename T>
SqMatrixJg<T> SqMatrixJg<T>::operator+(const SqMatrixJg &mat) const {
    SqMatrixJg<T> res_mat(n, {});
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            res_mat[i][j] = (*this)[i][j] + mat[i][j];
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixJg<T> SqMatrixJg<T>::operator-(const SqMatrixJg &mat) const {
    SqMatrixJg<T> res_mat(n, {});
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            res_mat[i][j] = (*this)[i][j] - mat[i][j];
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixJg<T> SqMatrixJg<T>::operator*(const T &value) const {
    SqMatrixJg<T> res_mat(n, {});
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            res_mat[i][j] = (*this)[i][j] * value;
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixJg<T> operator*(const T &value, const SqMatrixJg<T> &mat) {
    return mat * value;
}

template <typename T>
SqMatrixJg<T> SqMatrixJg<T>::operator/(const T &value) const {
    SqMatrixJg<T> res_mat(n, {});
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            res_mat[i][j] = (*this)[i][j] / value;
        }
    }
    return res_mat;
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
    std::swap((*this)[i], (*this)[j]);
}

template <typename T>
void SqMatrixJg<T>::swap_cols(size_t i, size_t j) {
    T tmp;
    for (int l = 0; l < n; l++) {
        tmp = (*this)[l][i];
        (*this)[l][i] = (*this)[l][j];
        (*this)[l][j] = tmp;
    }
}

template <typename T>
void SqMatrixJg<T>::add_row(size_t i, size_t j, T coeff) {
    operations::add_row(*this, i, j, coeff);
}

template <typename T>
void SqMatrixJg<T>::add_col(size_t i, size_t j, T coeff) {
    operations::add_col(*this, i, j, coeff);
}

template <typename T>
void SqMatrixJg<T>::sub_row(size_t i, size_t j, T coeff) {
    operations::sub_row(*this, i, j, coeff);
}

template <typename T>
void SqMatrixJg<T>::sub_col(size_t i, size_t j, T coeff) {
    operations::sub_col(*this, i, j, coeff);
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
size_t SqMatrixJg<T>::max_row_elem_index(size_t row) const {
    return operations::max_row_elem_index<SqMatrixJg<T>, T>(*this, row);
}

template <typename T>
size_t SqMatrixJg<T>::max_col_elem_index(size_t col) const {
    return operations::max_col_elem_index<SqMatrixJg<T>, T>(*this, col);
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