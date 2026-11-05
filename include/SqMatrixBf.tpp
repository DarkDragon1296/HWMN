#pragma once

template <typename T>
SqMatrixBf<T>::SqMatrixBf(size_t n_, std::vector<T> &&data_) :
                          n{n_}, data{std::move(data_)}
{
    data.resize(n * n);
};

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::operator+(const SqMatrixBf &mat) const {
    SqMatrixBf<T> res_mat(n, {});
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
            res_mat[i][j] = (*this)[i][j] + mat[i][j];
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::operator-(const SqMatrixBf &mat) const {
    SqMatrixBf<T> res_mat(n, {});
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
            res_mat[i][j] = (*this)[i][j] - mat[i][j];
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::operator*(const T &value) const {
    SqMatrixBf<T> res_mat(n, {});
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
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
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
            res_mat[i][j] = (*this)[i][j] / value;
        }
    }
    return res_mat;
}

template <typename T>
void SqMatrixBf<T>::operator+=(const SqMatrixBf &mat) {
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
            (*this)[i][j] += mat[i][j];
        }
    }
}

template <typename T>
void SqMatrixBf<T>::operator-=(const SqMatrixBf &mat) {
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
            (*this)[i][j] -= mat[i][j];
        }
    }
}

template <typename T>
void SqMatrixBf<T>::operator*=(const T &value) {
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
            (*this)[i][j] *= value;
        }
    }
}

template <typename T>
void SqMatrixBf<T>::operator/=(const T &value) {
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
            (*this)[i][j] /= value;
        }
    }
}

template <typename T>
void SqMatrixBf<T>::swap_rows(int i, int j) {
    T tmp;
    for (int l = 0; l < static_cast<int>(n); l++) {
        tmp = (*this)[i][l];
        (*this)[i][l] = (*this)[j][l];
        (*this)[j][l] = tmp;
    }
}

template <typename T>
void SqMatrixBf<T>::swap_cols(int i, int j) {
    T tmp;
    for (int l = 0; l < static_cast<int>(n); l++) {
        tmp = (*this)[l][i];
        (*this)[l][i] = (*this)[l][j];
        (*this)[l][j] = tmp;
    }
}

template <typename T>
void SqMatrixBf<T>::sum_rows(int i, int j) {
    for (int col = 0; col < static_cast<int>(n); col++) {
        (*this)[i][col] += (*this)[j][col];
    }
}

template <typename T>
void SqMatrixBf<T>::sum_cols(int i, int j) {
    for (int row = 0; row < static_cast<int>(n); row++) {
        (*this)[row][i] += (*this)[row][j];
    }
}

template <typename T>
void SqMatrixBf<T>::sub_rows(int i, int j) {
    for (int col = 0; col < static_cast<int>(n); col++) {
        (*this)[i][col] -= (*this)[j][col];
    }
}

template <typename T>
void SqMatrixBf<T>::sub_cols(int i, int j) {
    for (int row = 0; row < static_cast<int>(n); row++) {
        (*this)[row][i] -= (*this)[row][j];
    }
}

template <typename T>
void SqMatrixBf<T>::mul_row(int row, T value) {
    for (int col = 0; col < static_cast<int>(n); col++) {
        (*this)[row][col] *= value;
    }
}

template <typename T>
void SqMatrixBf<T>::mul_col(int col, T value) {
    for (int row = 0; row < static_cast<int>(n); row++) {
        (*this)[row][col] *= value;
    }
}

template <typename T>
void SqMatrixBf<T>::div_row(int row, T value) {
    for (int col = 0; col < static_cast<int>(n); col++) {
        (*this)[row][col] /= value;
    }
}

template <typename T>
void SqMatrixBf<T>::div_col(int col, T value) {
    for (int row = 0; row < static_cast<int>(n); row++) {
        (*this)[row][col] /= value;
    }
}

template <typename T>
int SqMatrixBf<T>::max_row_elem_index(int row) const {
    int index = 0;
    for (int col = 1; col < static_cast<int>(n); col++) {
        T i_value = (*this)[row][index];
        T e_value = (*this)[row][col];
        i_value *= i_value >= 0 ? 1 : -1;
        e_value *= e_value >= 0 ? 1 : -1;

        if (i_value > e_value)
            index = col;
    }
    return index;
}

template <typename T>
int SqMatrixBf<T>::max_col_elem_index(int col) const {
    int index = 0;
    for (int row = 1; row < static_cast<int>(n); row++) {
        T i_value = (*this)[index][col];
        T e_value = (*this)[row  ][col];
        i_value *= i_value >= 0 ? 1 : -1;
        e_value *= e_value >= 0 ? 1 : -1;

        if (i_value > e_value)
            index = row;
    }
    return index;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::minor(int row, int col) const {
    SqMatrixBf res_mat{n - 1, {}};
    int sz = static_cast<int>(n);

    for (int i = 0; i < sz - 1; i++) {
        for (int j = 0; j < sz - 1; j++) {
            int is_col_skip = j >= col;
            int is_row_skip = i >= row;
            res_mat[i][j] = (*this)[i + is_row_skip][j + is_col_skip];
        }
    }

    return res_mat;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::mul(const SqMatrixBf<T> &mat) const {
    SqMatrixBf<T> res_mat(n, {});
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
            for (int l = 0; l < static_cast<int>(n); l++) {
                res_mat[i][j] += (*this)[i][l] * mat[l][j];
            }
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::transpose(void) const {
    SqMatrixBf<T> res_mat(n, {});
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
            res_mat[i][j] = (*this)[j][i];
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::neg(void) const {
    SqMatrixBf<T> res_mat(n, {});
    res_mat = (*this) * (-1);
    return res_mat;
}

template <typename T>
T SqMatrixBf<T>::tr(void) {
    T tr{};
    for (int i = 0; i < static_cast<int>(n); i++)
        tr += (*this)[i][i];
    return tr;
}

template <typename T> /* TODO:*/
T SqMatrixBf<T>::det_gauss(void) {
    SqMatrixBf<T> mat = (*this);
    bool minus = false;

    for (int i = 0; i < static_cast<int>(n); i++) {



    }
}

template <typename T>
T SqMatrixBf<T>::det_recursion(void) {
    int sz = static_cast<int>(n);

    if (sz == 1)
        return (*this)[0][0];

    SqMatrixBf<T> mat{n - 1, {}};
    T res{}, value{};

    for (int l = 0; l < sz; l++) {
        mat = minor(0, l);
        value = (*this)[0][l] * mat.det_recursion();
        res += l % 2 ? -value : value;
    }

    return res;
}