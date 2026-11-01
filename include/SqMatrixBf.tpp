#pragma once

template <typename T>
SqMatrixBf<T>::SqMatrixBf(size_t n_, std::vector<T> &&data_) :
                          n{n_}, data{std::move(data_)}
{
    data.resize(n * n);
};

template <typename T>
SqMatrixBf<T>::SqMatrixBf(SqMatrixBf &&rhs) noexcept :
                          data{std::move(rhs.data)}, n{rhs.n}
{
    rhs.n = 0;
}

template <typename T>
SqMatrixBf<T> &SqMatrixBf<T>::operator=(SqMatrixBf &&rhs) noexcept {
    if (this == &rhs)
        return *this;

    data.clear();
    data = std::move(rhs.data);
    n = rhs.n;

    return *this;
}

template <typename T>
SqMatrixBf<T>::~SqMatrixBf() {
    data.clear();
    std::vector<T>().swap(data);
}

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
            for (int k = 0; k < static_cast<int>(n); k++) {
                res_mat[i][j] += (*this)[i][k] * mat[k][j];
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
    (*this) = mat;
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
void SqMatrixBf<T>::transpose(void) {
    T tmp;
    for (int i = 0; i < static_cast<int>(n) - 1; i++) { 
        for (int j = i + 1; j < static_cast<int>(n); j++) {
            tmp = (*this)[i][j];
            (*this)[i][j] = (*this)[j][i];
            (*this)[j][i] = tmp;
        }
    }
}