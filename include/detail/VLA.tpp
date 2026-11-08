#pragma once
#include "VLA.hpp"
#include <algorithm>

namespace buffers {

template <typename T>
VLA<T>::VLA(size_t n_, std::initializer_list<T> values) 
    : data{n_ ? new T[n_]{} : nullptr}, 
      n{n_} 
{
    std::copy(values.begin(),
              values.size() <= n ? values.end() : values.begin() + n,
              data);
}

template <typename T>
VLA<T>::VLA(std::initializer_list<T> values) 
    : data{values.size() ? new T[values.size()]{} : nullptr}, 
      n{values.size()} 
{
    std::copy(values.begin(), values.end(), data);    
}

template <typename T>
VLA<T> VLA<T>::create(size_t n_, T value) {
    VLA vla;
    if (!n_)
        return vla;

    vla.data = new T[n_]{value};
    vla.n = n_;
    return vla;
}

template <typename T>
VLA<T>::VLA(const VLA &rhs) 
    : data{rhs.n ? new T[rhs.n] : nullptr},
      n{rhs.n}
{
    std::copy(rhs.data, rhs.data + rhs.n, data);
}

template <typename T>
VLA<T>::VLA(VLA &&rhs) noexcept 
    : data{rhs.data},
      n{rhs.n}
{
    rhs.data = nullptr;
    rhs.n    = 0;
}

template <typename T>
VLA<T> &VLA<T>::operator=(const VLA &rhs) {
    if (this == &rhs)
        return *this;

    if (rhs.n != n) {
        if (rhs.n == 0) {
            release();
            data = nullptr;
            n = 0;
        } else {
            T *temp = new T[rhs.n];
            std::copy(rhs.data, rhs.data + rhs.n, temp);
            release();
            data = temp;
            n = rhs.n;
        }
    } else {
        std::copy(rhs.data, rhs.data + rhs.n, data);
    }

    return *this;
}

template <typename T>
VLA<T> &VLA<T>::operator=(VLA &&rhs) noexcept {
    if (this == &rhs)
        return *this;

    release();
    data = rhs.data;
    rhs.data = nullptr;
    n = rhs.n;
    rhs.n = 0;

    return *this;
}

template <typename T>
VLA<T>::~VLA() {
    release();
}

template <typename T>
T &VLA<T>::operator[](size_t i) & { 
    return data[i]; 
}

template <typename T>
const T &VLA<T>::operator[](size_t i) const & { 
    return data[i]; 
}

template <typename T>
size_t VLA<T>::size() const noexcept { 
    return n; 
}

template <typename T>
typename VLA<T>::iterator VLA<T>::begin() noexcept { 
    return data; 
}
template <typename T>
typename VLA<T>::iterator VLA<T>::end()   noexcept { 
    return data + n; 
}
template <typename T>
typename VLA<T>::const_iterator VLA<T>::begin() const noexcept { 
    return data;
}
template <typename T>
typename VLA<T>::const_iterator VLA<T>::end()   const noexcept { 
    return data + n;
}
template <typename T>
typename VLA<T>::const_iterator VLA<T>::cbegin() const noexcept { 
    return data; 
}
template <typename T>
typename VLA<T>::const_iterator VLA<T>::cend()   const noexcept { 
    return data + n;
}

template <typename T>
inline void VLA<T>::release() {
    delete[] data;
}

}
