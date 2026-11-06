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
    SqMatrixBf<int> mat{3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};

    int x = mat.det_gauss();
    std::cout << x;

    return 0;
}