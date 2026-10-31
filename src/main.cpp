#include "SqMatrixBf.hpp"
#include <iostream>
#include <vector>

template <typename T>
void printf_matrix(SqMatrixBf<T> &mat) {
    size_t n = mat.size();
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            std::cout << mat.get_elem(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

int main(void) {
    size_t n = 3;
    SqMatrixBf<int> mat1{n, {1, 2, 3, 4, 5, 6}};
    SqMatrixBf<int> mat2{n, {1, 2, 3, 4, 5, 6}};
    mat1[1][1] = 0;

    printf_matrix(mat1);
    printf_matrix(mat2);

    return 0;
}