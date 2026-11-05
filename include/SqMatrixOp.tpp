#pragma once

namespace operations {

template <typename U>
void sum_rows(U &mat, size_t i, size_t j) {
    size_t n = mat.size();
    for (size_t col = 0; col < n; col++) {
        mat[i][col] += mat[j][col];
    }
}

template <typename U>
void sum_cols(U &mat, size_t i, size_t j) {
    size_t n = mat.size();
    for (size_t row = 0; row < n; row++) {
        mat[row][i] += mat[row][j];
    }
}

template <typename U>
void sub_rows(U &mat, size_t i, size_t j) {
    size_t n = mat.size();
    for (size_t col = 0; col < n; col++) {
        mat[i][col] -= mat[j][col];
    }
}

template <typename U>
void sub_cols(U &mat, size_t i, size_t j) {
    size_t n = mat.size();
    for (size_t row = 0; row < n; row++) {
        mat[row][i] -= mat[row][j];
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
size_t max_row_elem_index(const U &mat, size_t row) {
    size_t n = mat.size();
    size_t index = 0;
    for (size_t col = 1; col < n; col++) {
        T i_value = mat[row][index];
        T e_value = mat[row][col];
        i_value *= i_value >= 0 ? 1 : -1;
        e_value *= e_value >= 0 ? 1 : -1;

        if (i_value > e_value)
            index = col;
    }
    return index;
}

template <typename U, typename T>
size_t max_col_elem_index(const U &mat, size_t col) {
    size_t n = mat.size();
    size_t index = 0;
    for (size_t row = 1; row < n; row++) {
        T i_value = mat[index][col];
        T e_value = mat[row  ][col];
        i_value *= i_value >= 0 ? 1 : -1;
        e_value *= e_value >= 0 ? 1 : -1;

        if (i_value > e_value)
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

#if 0
template <typename T> /* TODO:*/
T SqMatrixBf<T>::det_gauss(void) {
    SqMatrixBf<T> mat = (*this);
    bool minus = false;

    for (int i = 0; i < static_cast<int>(n); i++) {



    }
}
#endif

template <typename U, typename T>
T det_recursion(const U &mat) {
    size_t n = mat.size();

    if (n == 1)
        return mat[0][0];

    U submat{n - 1, {}};
    T res{}, value{};

    for (size_t l = 0; l < n; l++) {
        submat = mat.minor(0, l);
        value = mat[0][l] * mat.det_recursion();
        res += l % 2 ? -value : value;
    }

    return res;
}

}