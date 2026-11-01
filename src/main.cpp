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
    SqMatrixBf<int> mat1{n, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    SqMatrixBf<int> mat2{n, {1, 1, 1, 1, 0, 0, 1, 0, 0}};
    SqMatrixBf<int> mat3{n, {}}, mat4{n, {}};

    printf_matrix(mat1);
    mat1 = mat2;
    printf_matrix(mat1);

    return 0;
}