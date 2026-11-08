#include "SqMatrixBf.hpp"
#include "SqMatrixJg.hpp"
#include <iostream>

using namespace mat;

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
    SqMatrixJg<float> mat2(2, {1.0f, 2.0f,
                               2.0f, 5.0f});
    printf_matrix_jg(mat2);

    SqMatrixBf<float> mat3(3, {1.0f, 2.0f, 3.0f,
                               4.0f, 5.0f, 6.0f,
                               7.0f, 8.0f, 9.0f});
    printf_matrix_bf(mat3);

    float x = mat2.det_recursion();
    std::cout << x << std::endl;

    return 0;
}
