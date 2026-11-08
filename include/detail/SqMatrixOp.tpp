#pragma once

#include <cmath>
#include <type_traits>

namespace mat {
namespace operations {

static const double FLOAT_CMP_PRECISION = 1e-6;

template <typename T>
bool is_zero(T value) {
    return std::is_floating_point_v<T> 
           ? std::abs(value) <= FLOAT_CMP_PRECISION
           : value == T{};
}

template <typename U, typename T>
void swap_cols(U &mat, size_t i, size_t j) {
    T tmp;
    for (int l = 0, n = mat.size(); l < n; l++) {
        tmp = mat[l][i];
        mat[l][i] = mat[l][j];
        mat[l][j] = tmp;
    }
}

template <typename U, typename T>
void add_row(U &mat, size_t i, size_t j, T coeff) {
    for (size_t col = 0, n = mat.size(); col < n; col++)
        mat[i][col] += coeff * mat[j][col];
}

template <typename U, typename T>
void add_col(U &mat, size_t i, size_t j, T coeff) {
    for (size_t row = 0, n = mat.size(); row < n; row++)
        mat[row][i] += coeff * mat[row][j];
}

template <typename U, typename T>
void sub_row(U &mat, size_t i, size_t j, T coeff) {
    for (size_t col = 0, n = mat.size(); col < n; col++)
        mat[i][col] -= coeff * mat[j][col];
}

template <typename U, typename T>
void sub_col(U &mat, size_t i, size_t j, T coeff) {
    for (size_t row = 0, n = mat.size(); row < n; row++)
        mat[row][i] -= coeff * mat[row][j];
}

template <typename U, typename T>
void mul_row(U &mat, size_t row, T value) {
    for (size_t col = 0, n = mat.size(); col < n; col++)
        mat[row][col] *= value;
}

template <typename U, typename T>
void mul_col(U &mat, size_t col, T value) {
    for (size_t row = 0, n = mat.size(); row < n; row++)
        mat[row][col] *= value;
}

template <typename U, typename T>
void div_row(U &mat, size_t row, T value) {
    for (size_t col = 0, n = mat.size(); col < n; col++)
        mat[row][col] /= value;
}

template <typename U, typename T>
void div_col(U &mat, size_t col, T value) {
    for (size_t row = 0, n = mat.size(); row < n; row++)
        mat[row][col] /= value;
}

template <typename U, typename T>
size_t max_row_elem_index(const U &mat, size_t row, size_t start) {
    size_t index = start;
    for (size_t col = start + 1, n = mat.size(); col < n; col++) {
        if (std::abs(mat[row][col]) > std::abs(mat[row][index]))
            index = col;
    }
    return index;
}

template <typename U, typename T>
size_t max_col_elem_index(const U &mat, size_t col, size_t start) {
    size_t index = start;
    for (size_t row = start + 1, n = mat.size(); row < n; row++) {
        if (std::abs(mat[row][col]) > std::abs(mat[index][col]))
            index = row;
    }
    return index;
}

template <typename U>
U minor(const U &mat, size_t row, size_t col) {
    size_t n = mat.size();
    U res_mat(n - 1);

    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - 1; j++) {
            size_t is_col_skip = j >= col;
            size_t is_row_skip = i >= row;
            res_mat[i][j] = mat[i + is_row_skip][j + is_col_skip];
        }
    }

    return res_mat;
}

template <typename U>
U mul(const U &mat1, const U &mat2) {
    size_t n = mat1.size();
    U res_mat(n);

    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            for (size_t l = 0; l < n; l++) {
                res_mat[i][j] += mat1[i][l] * mat2[l][j];
            }
        }
    }
    return res_mat;
}

template <typename U>
U transpose(const U &mat) {
    size_t n = mat.size();
    U res_mat(n);
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            res_mat[i][j] = mat[j][i];
        }
    }
    return res_mat;
}

template <typename U>
U neg(const U &mat) {
    size_t n = mat.size();
    U res_mat(n);
    res_mat = mat * (-1);
    return res_mat;
}

template <typename U, typename T>
T tr(const U &mat) {
    size_t n = mat.size();
    T tr{};
    for (size_t i = 0; i < n; i++)
        tr += mat[i][i];
    return tr;
}

template <typename U, typename T>
T det_recursion(const U &mat) {
    size_t n = mat.size();

    if (n == 1)
        return mat[0][0];
    if (n == 0)
        return T{};

    U submat(n - 1);
    T res{}, value{};
    for (size_t l = 0; l < n; l++) {
        submat = mat.minor(0, l);
        value = mat[0][l] * submat.det_recursion();
        res += l % 2 ? -value : value;
    }

    return res;
}

template <typename U, typename T>
T det_gauss(const U &src) {
    U mat = src;
    size_t n = mat.size();
    bool minus = false;

    if (n == 0)
        return T{};

    for (size_t i = 0; i < n; i++) {
        size_t max_index = mat.max_col_elem_index(i, i);

        if (is_zero(mat[max_index][i]))
            return T{};

        if (max_index != i) {
            mat.swap_rows(i, max_index);
            minus = !minus;
        }

        for (size_t j = i + 1; j < n; j++)
            mat.sub_row(j, i, mat[j][i] / mat[i][i]);
    }

    T res = mat[0][0];
    for (size_t i = 1; i < n; i++)
        res *= mat[i][i];

    res = minus ? -res : res;

    return res;
}

template <typename U, typename T>
T det_bareiss(const U &src) {
    U mat = src;
    size_t n = mat.size();
    bool minus = false;

    if (n == 0)
        return T{};

    for (size_t k = 0; k < n - 1; k++) {
        if (k != 0 && is_zero(mat[k][k])) {
            size_t max_index = mat.max_col_elem_index(k, k);
            if (max_index == k)
                return T{};

            mat.swap_rows(k, max_index);
            minus = !minus;
        }

        for (size_t i = k + 1; i < n; i++) {
            for (size_t j = k + 1; j < n; j++) {
                if(k == 0) {
                    mat[i][j] = (mat[i][j] * mat[0][0] - mat[i][0] * mat[0][j]);
                } else {
                    mat[i][j] = (mat[i][j] * mat[k][k] - mat[i][k] * mat[k][j])
                              / mat[k - 1][k - 1];
                }
            }
        }
    }

    T res = minus ? -mat[n - 1][n - 1] : mat[n - 1][n - 1];
    return res;
}

template <typename U, typename T>
T det_lu(const U &src) {
    size_t n = src.size();
    U l_mat(n), u_mat(n);

    if (n == 0)
        return T{};

    for (size_t i = 0; i < n; i++)
        l_mat[i][i] = static_cast<T>(1);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (i <= j) {
                u_mat[i][j] = src[i][j];
                for (size_t k = 1; k <= i; k++)
                    u_mat[i][j] -= l_mat[i][k - 1] * u_mat[k - 1][j];
            } else {
                l_mat[i][j] = src[i][j];
                for (size_t k = 1; k <= j; k++)
                    l_mat[i][j] -= l_mat[i][k - 1] * u_mat[k - 1][j];
                l_mat[i][j] /= u_mat[j][j];
            }

            if (i == j && is_zero(u_mat[i][i]))
                return T{};
        }
    }

    T res = u_mat[0][0];
    for (size_t i = 1; i < n; i++)
        res *= u_mat[i][i];

    return res;
}

template <typename U, typename T>
T det_cholesky(const U &src) {
    size_t n = src.size();
    U l_mat(n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (j > i) {
                continue;
            } else if (!i && !j) {
                l_mat[0][0] = std::sqrt(src[0][0]);
            } else if (!j) {
                l_mat[i][0] = src[i][0] / l_mat[0][0];
            } else if (i == j) {
                l_mat[i][i] = src[i][i];
                for (size_t k = 0; k <= i - 1; k++)
                    l_mat[i][i] -= src[i][k] * src[i][k];
                l_mat[i][i] = std::sqrt(l_mat[i][i]);

                if (is_zero(l_mat[i][i]))
                    return T{};
            } else {
                l_mat[i][j] = src[i][j];
                for (size_t k = 0; k <= j - 1; k++)
                    l_mat[i][j] -= src[i][k] * src[j][k];
                l_mat[i][j] /= l_mat[j][j];
            }
        }
    }

    T res = l_mat[0][0];
    for (size_t i = 1; i < n; i++)
        res *= l_mat[i][i];
    res *= res;

    return res;
}

} // namespace operations
} // namespace mat
