#include <iostream>
#include <vector>

template <typename T> // TODO: Big 5
class SqMatrixBf {
    size_t n;
    std::vector<T> data;

    public:

    SqMatrixBf(size_t n_, std::vector<T> &&data_ = T{}) :
        n{n_}, data{std::move(data_)}
    {
        data.resize(n * n);
    };


    T get_elem(size_t i, size_t j) const {
        return data[i * n + j];
    }

    size_t size() const {
        return n;
    }

    void set_elem(size_t i, size_t j, T value) {
        data[i * n + j] = value;
    }

#if 0
    T &operator[](size_t i, size_t j) {
        return data[i * n + j];
    }
#endif

    SqMatrixBf operator+(const SqMatrixBf& mat) const {
        SqMatrixBf<T> res_mat(n, {});

        for (size_t i = 0; i < n; i++) { 
            for (size_t j = 0; j < n; j++) {
                res_mat.set_elem(i, j, get_elem(i, j) + mat.get_elem(i, j));
            }
        }

        return res_mat;
    }

    void operator+=(const SqMatrixBf& mat) {
        for (size_t i = 0; i < n; i++) { 
            for (size_t j = 0; j < n; j++) {
                set_elem(i, j, get_elem(i, j) + mat.get_elem(i, j));
            }
        }
    }
};

template <typename T>
void printf_matrix(SqMatrixBf<T> &mat) {
    size_t n = mat.size();
    for (size_t i = 0; i < n; i++) { 
        for (size_t j = 0; j < n; j++) {
            std::cout << mat.get_elem(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

int main(void) {
    size_t n = 3;
    SqMatrixBf<int> mat1{n, {1, 2, 3, 4, 5, 6}};
    SqMatrixBf<int> mat2{n, {1, 2, 3, 4, 5, 6}};
    SqMatrixBf<int> mat3 = mat1 + mat2;

    mat3 += mat1 + mat2;

    printf_matrix(mat3);
    printf_matrix(mat1);

    return 0;
}