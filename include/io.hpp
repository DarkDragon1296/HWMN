#pragma once

#include "SqMatrixBf.hpp"
#include "SqMatrixJg.hpp"

namespace io {

using Bfs = buffers::VLA<mat::SqMatrixBf<double>>;
using Jgs = buffers::VLA<mat::SqMatrixJg<double>>;

struct Input {
    Bfs bfs;
    Jgs jgs;
};

std::optional<Input> read_input(std::istream &source);
std::istream &operator>>(std::istream &source, buffers::VLA<double> &vla);
bool read_vla(std::istream &source, buffers::VLA<double> &vla);

template <typename T>
std::ostream &operator<<(std::ostream &sink, mat::SqMatrixBf<T> &mat);

template <typename T>
std::ostream &operator<<(std::ostream &sink, mat::SqMatrixJg<T> &mat);

}

#include "detail/io.tpp"
