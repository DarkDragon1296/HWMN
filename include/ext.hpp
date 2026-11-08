#pragma once

// C++ 20 feature (reinventing the wheel)
namespace ext {
template <typename T>
struct identity_type { using type = T; };

template <typename T>
using identity_type_t = typename identity_type<T>::type;
}
