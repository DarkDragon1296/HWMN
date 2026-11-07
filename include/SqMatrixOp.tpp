#pragma once

#include <cmath>
#include <limits>
#include <type_traits>

namespace operations {

template <typename T>
bool is_zero(T value) {
    if (std::is_integral_v<T>)
        return value == 0;

    if (std::is_floating_point_v<T>)
        return std::abs(value) <= std::numeric_limits<T>::epsilon();

    return false;
}

template <typename U, typename T>
void add_row(U &mat, size_t i, size_t j, T coeff) {
    size_t n = mat.size();
    for (size_t col = 0; col < n; col++) {
        mat[i][col] += coeff * mat[j][col];
    }
}

template <typename U, typename T>
void add_col(U &mat, size_t i, size_t j, T coeff) {
    size_t n = mat.size();
    for (size_t row = 0; row < n; row++) {
        mat[row][i] += coeff * mat[row][j];
    }
}

template <typename U, typename T>
void sub_row(U &mat, size_t i, size_t j, T coeff) {
    size_t n = mat.size();
    for (size_t col = 0; col < n; col++) {
        mat[i][col] -= coeff * mat[j][col];
    }
}

template <typename U, typename T>
void sub_col(U &mat, size_t i, size_t j, T coeff) {
    size_t n = mat.size();
    for (size_t row = 0; row < n; row++) {
        mat[row][i] -= coeff * mat[row][j];
    }
}

template <typename U, typename T>
void mul_row(U &mat, size_t row, T value) {
    size_t n = mat.size();
    for (size_t col = 0; col < n; col++) {
        mat[row][col] *= value;
    }
}

template <typename U, typename T>
void mul_col(U &mat, size_t col, T value) {
    size_t n = mat.size();
    for (size_t row = 0; row < n; row++) {
        mat[row][col] *= value;
    }
}

template <typename U, typename T>
void div_row(U &mat, size_t row, T value) {
    size_t n = mat.size();
    for (size_t col = 0; col < n; col++) {
        mat[row][col] /= value;
    }
}

template <typename U, typename T>
void div_col(U &mat, size_t col, T value) {
    size_t n = mat.size();
    for (size_t row = 0; row < n; row++) {
        mat[row][col] /= value;
    }
}

template <typename U, typename T>
size_t max_row_elem_index(const U &mat, size_t row, size_t start) {
    size_t n = mat.size();
    size_t index = start;
    for (size_t col = start + 1; col < n; col++) {
        if (std::abs(mat[row][col]) > std::abs(mat[row][index]))
            index = col;
    }
    return index;
}

template <typename U, typename T>
size_t max_col_elem_index(const U &mat, size_t col, size_t start) {
    size_t n = mat.size();
    size_t index = start;
    for (size_t row = start + 1; row < n; row++) {
        if (std::abs(mat[row][col]) > std::abs(mat[index][col]))
            index = row;
    }
    return index;
}

template <typename U>
U minor(const U &mat, size_t row, size_t col) {
    size_t n = mat.size();
    U res_mat{n - 1, {}};

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
    U res_mat(n, {});

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
    U res_mat(n, {});
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
    U res_mat(n, {});
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

    if (n == 0)
        return T{};

    if (n == 1)
        return mat[0][0];

    U submat{n - 1, {}};
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

}