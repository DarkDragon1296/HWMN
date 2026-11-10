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

    SqMatrixJg<float> mat3(4, {-2.0f, -1.0f, -1.0f, -4.0f,
                               -1.0f, -2.0f, -1.0f, -6.0f,
                               -1.0f, -1.0f,  2.0f,  4.0f,
                                2.0f,  1.0f, -3.0f, -8.0f});

    std::cout << mat2 << mat3;

#if 0 //disable
    float x = mat3.det_dodgson();
    std::cout << x << std::endl;
#endif

    std::optional<SqMatrixJg<float>> sub1 = mat3.submatrix(2, 1, 2);
    if (sub1.has_value()) {
        std::cout << sub1.value();
    } else {
        std::cout << "Impossible to construct submatrix" << std::endl;
    }

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
