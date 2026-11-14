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

// Do not look here! Look at the tests instead, this is just for our own usage
int main(void) {
    SqMatrixJg<float> mat2(2, {1.0f, 2.0f,
                               2.0f, 5.0f});

    SqMatrixJg<float> mat3(4, {-2.0f, -1.0f, -1.0f, -4.0f,
                               -1.0f, -2.0f, -1.0f, -6.0f,
                               -1.0f, -1.0f,  2.0f,  4.0f,
                                2.0f,  1.0f, -3.0f, -8.0f});

#if 0 //disable
    float x = mat3.det_dodgson();
    std::cout << x << std::endl;
#endif

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
