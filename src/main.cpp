#include <iostream>
#include <vector>

template <typename T>
class MatrixBf {
    size_t n;
    std::vector<T> data;

    public:

    MatrixBf(size_t n_, std::vector<T> &&data_ = T{}) :
        n{n_}, data{std::move(data_)}
    {
        data.resize(n * n);
    };

    T get_elem(size_t i, size_t j) {
        return data[i * n + j];
    }
};

int main(void) {
    size_t n = 3;
    MatrixBf<int> mat{n, {1, 2, 3, 4, 5, 6}};

    for (size_t i = 0; i < n * n; i++)
        std::cout << mat.get_elem(i / n, i % n) << " " << std::endl;

    return 0;
}