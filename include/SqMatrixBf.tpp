#pragma once

template <typename T>
SqMatrixBf<T>::SqMatrixBf(size_t n_, std::vector<T> &&data_) :
                          n{n_}, data{std::move(data_)}
{
    data.resize(n * n);
};

#if 0
template <typename T>
SqMatrixBf<T>::SqMatrixBf(SqMatrixBf &&rhs) noexcept : n{rhs.n},
                                                       data{std::move(rhs.data)}
{
    rhs.n = 0;
}

template <typename T>
SqMatrixBf<T> &SqMatrixBf<T>::operator=(SqMatrixBf &&rhs) noexcept {
    if (this == &rhs)
        return *this;

    n = rhs.n;
    data.clear();
    data = std::move(rhs.data);

    return *this;
}

template <typename T>
SqMatrixBf<T>::~SqMatrixBf() {
    data.clear();
    std::vector<T>().swap(data);
}
#endif

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
SqMatrixBf<T> SqMatrixBf<T>::operator*(const SqMatrixBf &mat) const {
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

template <typename T> // TODO: fix proplem of x * mat
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

template <typename T> // TODO: fix =
void SqMatrixBf<T>::operator*=(const SqMatrixBf &mat) {
    SqMatrixBf<T> res_mat(n, {});

    res_mat = (*this) * mat;
    (*this) = res_mat;
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
SqMatrixBf<T> SqMatrixBf<T>::inverse(void) {
    SqMatrixBf<T> res_mat(n, {});
    /* TODO: */
    return res_mat;
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