#pragma once
#include <cstddef>
#include <initializer_list>

namespace buffers {

template <typename T>
class VLA final {
    private:
    T *data  = nullptr;
    size_t n = 0;

    public: // Construstors
    VLA() = default;

    /// Allocates n_ T's
    /// If (values.size() < n_) and T is default init-able, 
    ///     fills the rest with default values.
    /// If (values.size() < n_) and T isn't default init-able,
    ///     fills the rest with undetermined values. 
    /// If (values.size() > n_),
    ///     ignores the excessive values
    /// In order to not fall into VLA(std::initializer_list<T>) constructor,
    ///     please make sure that either T isnt compatible with size_t, 
    ///     or that you use the regular init (), not uniform init {}
    VLA(size_t n_, std::initializer_list<T> values); 

    /// Allocates exactly values.size() T's and copies them over
    VLA(std::initializer_list<T> values);

    /// Allocates n_ values and default inits them if T is default init-able
    static VLA create(size_t n_);

    public: // Rule of Five
    VLA(const VLA &rhs);
    VLA(VLA &&rhs) noexcept;    
    VLA &operator=(const VLA &rhs);
    VLA &operator=(VLA &&rhs) noexcept; 
    ~VLA();

    public: // Selectors
    T &operator[](size_t i) &;
    const T &operator[](size_t i) const &;
    size_t size() const noexcept;

    public: // Iterators
    using iterator       = T *;
    using const_iterator = const T *;

    iterator       begin()        noexcept;
    iterator       end()          noexcept; 
    const_iterator begin()  const noexcept; 
    const_iterator end()    const noexcept; 
    const_iterator cbegin() const noexcept; 
    const_iterator cend()   const noexcept; 

    private:
    inline void release();
};

}

#include "detail/VLA.tpp"
