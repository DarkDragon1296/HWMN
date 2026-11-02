#if 0
#pragma once

#include <iostream>

template <class A>
class SqMatrix {
    A mat;

    public:

    SqMatrix(A mat_) : mat{std::move(mat_)} {};
};

#endif