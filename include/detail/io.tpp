#pragma once
#include "io.hpp"

namespace io {

template <typename T>
std::ostream &operator<<(std::ostream &sink, mat::SqMatrixBf<T> &mat) {
    mat.dump(sink);
    return sink;
}

template <typename T>
std::ostream &operator<<(std::ostream &sink, mat::SqMatrixJg<T> &mat) {
    mat.dump(sink);
    return sink;
}

}
