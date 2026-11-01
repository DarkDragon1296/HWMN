#include "SqMatrixBf.hpp"
#include <iostream>
#include <vector>

template <typename T>
void printf_matrix(SqMatrixBf<T> &mat) {
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
    SqMatrixBf<int> mat1{n, {1, 2, 3, 4, 5, 6}};
    SqMatrixBf<int> mat2{n, {2, 3, 4, 5, 6, 7}};

    mat1 *= 2;

    printf_matrix(mat1);
    printf_matrix(mat2);

    return 0;
}