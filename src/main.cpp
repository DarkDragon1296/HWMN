#include "SqMatrix.hpp"
#include "SqMatrixBf.hpp"
#include "SqMatrixJg.hpp"
#include <iostream>
#include <vector>

template <typename T>
void printf_matrix_bf(SqMatrixBf<T> &mat) {
    int n = static_cast<int>(mat.size());
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void printf_matrix_jg(SqMatrixJg<T> &mat) {
    int n = static_cast<int>(mat.size());
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(void) {
    size_t n = 3;

    SqMatrixBf<int> mat1{n, {}};
    SqMatrixBf<int> mat2{n, {}};

    mat1[1][1] = 1;
    mat2[1][1] = 1;

    return 0;
}