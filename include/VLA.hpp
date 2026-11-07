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
    VLA(std::initializer_list<T> values);
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
