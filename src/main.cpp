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
    SqMatrixJg<int> mat{2, {}};
    SqMatrixJg<int> submat{1, {}};

//    submat = mat.minor(0, 0);
    std::cout << mat[0][0] << mat[0][1] << mat[1][0] << mat[1][1] << std::endl;
    printf_matrix_jg(mat);
//    printf_matrix_jg(submat);
    return 0;
}