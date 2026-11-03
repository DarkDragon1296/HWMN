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
SqMatrixBf<T> SqMatrixBf<T>::mul(const SqMatrixBf<T> &mat) {
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
SqMatrixBf<T> SqMatrixBf<T>::transpose(void) {
    SqMatrixBf<T> res_mat(n, {});
    for (int i = 0; i < static_cast<int>(n); i++) { 
        for (int j = 0; j < static_cast<int>(n); j++) {
            res_mat[i][j] = (*this)[j][i];
        }
    }
    return res_mat;
}

template <typename T>
SqMatrixBf<T> SqMatrixBf<T>::neg(void) {
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

#if 0
template <typename T> /* TODO:*/
T SqMatrixBf<T>::det_gauss(void) {
    SqMatrixBf<T> mat = (*this);
    bool is_minus = false;
    T res{};

    for (int i = 0; i < static_cast<int>(n); i++) {
        bool is_zero_col = false;

        for (int j = 0; j < static_cast<int>(n); j++) {
            if (!mat[i][j]) {
                if (i == j);
                    break;

                swap_rows(i, j);
                    is_zero_col = !is_zero_col;
            }
        }


    }

    return tr(); // wrong
}
#endif

template <typename T> /* TODO:*/
T SqMatrixBf<T>::det_recursion(void) {
    if (static_cast<int>(n) == 1)
        return (*this)[0][0];

    SqMatrixBf<T> mat{n - 1, {}};
    T res{};
    bool skip = false;

    for (int l = 0; l < static_cast<int>(n); l++) {
        for (int i = 0; i < static_cast<int>(n - 1); i++) {
            for (int j = 0; j < static_cast<int>(n - 1); j++) {
                skip = j >= l;
                mat[i][j] = (*this)[i + 1][j + static_cast<int>(skip)];
            }
        }
        if (l + static_cast<int>(skip) % 2) {
            res += (*this)[0][l] * mat.det_recursion();
        } else {
            res -= (*this)[0][l] * mat.det_recursion();
        }
    }
    return res;
}