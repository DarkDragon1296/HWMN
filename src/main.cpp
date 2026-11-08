#include "SqMatrixBf.hpp"
#include "SqMatrixJg.hpp"
#include <iostream>

using namespace mat;

namespace {
template <typename T>
std::ostream &operator<<(std::ostream &sink, SqMatrixBf<T> &mat);

template <typename T>
std::ostream &operator<<(std::ostream &sink, SqMatrixJg<T> &mat);
}

int main(void) {
    SqMatrixJg<float> mat2(2, {1.0f, 2.0f,
                               2.0f, 5.0f});

    SqMatrixBf<float> mat3(3, {1.0f, 2.0f, 3.0f,
                               4.0f, 5.0f, 6.0f,
                               7.0f, 8.0f, 9.0f});

    std::cout << mat2 << mat3;

    float x = mat2.det_recursion();
    std::cout << x << std::endl;

    return 0;
}

namespace {
template <typename T>
std::ostream &operator<<(std::ostream &sink, SqMatrixBf<T> &mat) {
    mat.dump(sink);
    return sink;
}

template <typename T>
std::ostream &operator<<(std::ostream &sink, SqMatrixJg<T> &mat) {
    mat.dump(sink);
    return sink;
}
}
