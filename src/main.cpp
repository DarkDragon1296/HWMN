#include "SqMatrixBf.hpp"
#include "SqMatrixJg.hpp"
#include <iostream>
#include <vector>

template <typename T>
void printf_matrix_bf(SqMatrixBf<T> &mat) {
    size_t n = mat.size();
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void printf_matrix_jg(SqMatrixJg<T> &mat) {
    size_t n = mat.size();
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(void) {
    SqMatrixJg<int> mat{3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    SqMatrixJg<int> submat{2, {}};

    submat = mat.minor(0, 0);
    submat[0][0] = 1;
    printf_matrix_jg(mat);
    printf_matrix_jg(submat);

    SqMatrixBf<int> mat1{3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    SqMatrixBf<int> submat1{2, {}};

    submat1 = mat1.minor(0, 0);
    printf_matrix_bf(mat1);
    printf_matrix_bf(submat1);
    return 0;
}