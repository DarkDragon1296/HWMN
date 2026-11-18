#include "SqMatrixBf.hpp"
#include "SqMatrixJg.hpp"
#include <gtest/gtest.h>

#define EXPECT_MATRIX(actual, size, ...) \
    expect_matrix(actual, size, __VA_ARGS__, __FILE__, __LINE__)

namespace {

template <typename Matrix>
void expect_matrix(const Matrix &actual, size_t n,
                   std::initializer_list<int> expected,
                   const char* file, size_t line); 
template <typename Matrix>
void matrix_init_suite();
template <typename Matrix>
void matrix_minor_suite();
template <typename Matrix>
void matrix_submatrix_suite();
template <typename Matrix>
void matrix_dump_suite();
template <typename Matrix>
void matrix_det_suite();
template <typename Matrix>
void matrix_row_col_op_suite();
template <typename Matrix>
void matrix_op_suite();

}

TEST(SqMatrixBfTest, ConstructorsAndFactories) { 
    matrix_init_suite<mat::SqMatrixBf<int>>(); 
}
TEST(SqMatrixJgTest, ConstructorsAndFactories) { 
    matrix_init_suite<mat::SqMatrixJg<int>>(); 
}
TEST(SqMatrixBfTest, GenericOperations) { 
    matrix_op_suite<mat::SqMatrixBf<int>>(); 
}
TEST(SqMatrixJgTest, GenericOperations) { 
    matrix_op_suite<mat::SqMatrixJg<int>>(); 
}
TEST(SqMatrixBfTest, RowColOperations) { 
    matrix_row_col_op_suite<mat::SqMatrixBf<int>>(); 
}
TEST(SqMatrixJgTest, RowColOperations) { 
    matrix_row_col_op_suite<mat::SqMatrixJg<int>>(); 
}
TEST(SqMatrixBfTest, Minor) { 
    matrix_minor_suite<mat::SqMatrixBf<int>>(); 
}
TEST(SqMatrixJgTest, Minor) { 
    matrix_minor_suite<mat::SqMatrixJg<int>>(); 
}
TEST(SqMatrixBfTest, Submatrix) { 
    matrix_submatrix_suite<mat::SqMatrixBf<int>>(); 
}
TEST(SqMatrixJgTest, Submatrix) { 
    matrix_submatrix_suite<mat::SqMatrixJg<int>>(); 
}
TEST(SqMatrixBfTest, Dump) { 
    matrix_dump_suite<mat::SqMatrixBf<int>>(); 
}
TEST(SqMatrixJgTest, Dump) { 
    matrix_dump_suite<mat::SqMatrixJg<int>>(); 
}
TEST(SqMatrixBfTest, Determinant) { 
    matrix_det_suite<mat::SqMatrixBf<float>>(); 
}
TEST(SqMatrixJgTest, Determinant) { 
    matrix_det_suite<mat::SqMatrixJg<float>>(); 
}

namespace { //anonymous
        
template <typename Matrix>
void expect_matrix(const Matrix &actual, size_t n,
                   std::initializer_list<int> expected,
                   const char* file, size_t line) {
    ASSERT_EQ(actual.size(), n)
        << "called from " << file << ":" << line;
    auto value = expected.begin();
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j, ++value)
            EXPECT_EQ(actual[i][j], *value) 
                << "at (" << i << ", " << j << ") "
                << "called from " << file << ":" << line;
}

template <typename Matrix>
void matrix_init_suite() {
    {
        Matrix empty;
        EXPECT_EQ(empty.size(), 0);
    }

    {
        Matrix zero(0);
        EXPECT_EQ(zero.size(), 0);
    }

    {
        Matrix partial(2, {1, 2});
        EXPECT_MATRIX(partial, 2, 
                      {1, 2, 
                       0, 0});
        partial[1][0] = 7;
        EXPECT_EQ(partial[1][0], 7);
        const Matrix &constant = partial;
        EXPECT_EQ(constant[0][1], 2);
    }

    {
        std::initializer_list<int> list = {1, 2, 3, 4};
        EXPECT_MATRIX(Matrix(2, list.begin(), list.end()), 
                       2, 
                      {1, 2, 
                       3, 4});
    }

    EXPECT_MATRIX(Matrix::create_scalar(2, 5), 2, 
                  {5, 5, 
                   5, 5});
    EXPECT_MATRIX(Matrix::create_scalar(0, 5), 0, {});

    EXPECT_MATRIX(Matrix::create_eye(3, 4), 3, 
                  {4, 0, 0, 
                   0, 4, 0, 
                   0, 0, 4});
    EXPECT_MATRIX(Matrix::create_eye(0, 4), 0, {});
}

template <typename Matrix>
void matrix_minor_suite() {
    Matrix a(2, {1, 2,
                 3, 4});
    std::optional<Matrix> minor_matrix = a.minor(0, 0);
    ASSERT_EQ(minor_matrix.has_value(), true);
    EXPECT_MATRIX(minor_matrix.value(), 1, {4});

    Matrix m(3, {1, 2, 3,
                 4, 5, 6,
                 7, 8, 9});
    minor_matrix = m.minor(1, 1); 
    ASSERT_EQ(minor_matrix.has_value(), true);
    EXPECT_MATRIX(minor_matrix.value(), 2,
                  {1, 3,
                   7, 9});

    minor_matrix = m.minor(10, 10);
    ASSERT_EQ(minor_matrix.has_value(), false);
}

template <typename Matrix>
void matrix_submatrix_suite() {
    Matrix mat(4, {1 ,  2 , 3 , 4,
                   5 ,  6 , 7 , 8,
                   9 ,  10, 11, 12,
                   13 , 14, 15, 16});

    std::optional<Matrix> sub = mat.submatrix(2, 1, 2);
    ASSERT_EQ(sub.has_value(), true);
    EXPECT_MATRIX(sub.value(), 2, {7, 8, 
                                   11, 12});
    sub = mat.submatrix(3, 2, 2);
    ASSERT_EQ(sub.has_value(), false);

    sub = mat.submatrix(3, 2, 0);
    ASSERT_EQ(sub.has_value(), false);

    sub = mat.submatrix(6, 0, 0);
    ASSERT_EQ(sub.has_value(), false);

    sub = mat.submatrix(0, 0, 0);
    ASSERT_EQ(sub.has_value(), true);
    EXPECT_MATRIX(sub.value(), 0, {});

    sub = mat.submatrix(4, 0, 0);
    ASSERT_EQ(sub.has_value(), true);
    EXPECT_MATRIX(sub.value(), 4, 
                  {1 ,  2 , 3 , 4,
                   5 ,  6 , 7 , 8,
                   9 ,  10, 11, 12,
                   13 , 14, 15, 16});
}

template <typename Matrix>
void matrix_dump_suite() {
    std::ostringstream output;
    Matrix one(1, {9});
    one.dump(output);
    EXPECT_EQ(output.str(), "9 \n");

    output.str("");
    output.clear();

    Matrix big(3, {1, 2, 3,
                   4, 5, 6,
                   7, 8, 9});
    big.dump(output);
    EXPECT_EQ(output.str(), "1 2 3 \n"
                            "4 5 6 \n"
                            "7 8 9 \n");
}

template <typename Matrix>
void matrix_row_col_op_suite() {
    Matrix rows(2, {1, 2, 
                    3, 4});
    EXPECT_EQ(rows.max_row_elem_index(0, 0), 1);
    EXPECT_EQ(rows.max_col_elem_index(0, 0), 1);

    rows.swap_rows(0, 1);
    EXPECT_MATRIX(rows, 2, {3, 4, 
                            1, 2});

    rows.swap_rows(1, 1);
    EXPECT_MATRIX(rows, 2, {3, 4, 
                            1, 2});

    rows.swap_cols(0, 1);
    EXPECT_MATRIX(rows, 2, {4, 3, 
                            2, 1});

    rows.add_row(0, 1, 2);
    EXPECT_MATRIX(rows, 2, {8, 5, 
                            2, 1});

    rows.sub_row(0, 1, 2);
    EXPECT_MATRIX(rows, 2, {4, 3, 
                            2, 1});

    rows.mul_row(1, 3);
    EXPECT_MATRIX(rows, 2, {4, 3,
                            6, 3});

    rows.div_row(1, 3);
    EXPECT_MATRIX(rows, 2, {4, 3, 
                            2, 1});

    rows.add_col(0, 1, 2);
    EXPECT_MATRIX(rows, 2, {10, 3, 
                            4, 1});

    rows.sub_col(0, 1, 2);
    EXPECT_MATRIX(rows, 2, {4, 3, 
                            2, 1});

    rows.mul_col(1, 2);
    EXPECT_MATRIX(rows, 2, {4, 6,
                            2, 2});

    rows.div_col(1, 2);
    EXPECT_MATRIX(rows, 2, {4, 3, 
                            2, 1});
}

template <typename Matrix>
void matrix_op_suite() {
    Matrix a(2, {1, 2, 
                 3, 4});
    Matrix b(2, {5, 6, 
                 7, 8});
    EXPECT_MATRIX(a + b, 2, 
                  {6, 8, 
                   10, 12});
    EXPECT_MATRIX(b - a, 2, 
                  {4, 4, 
                   4, 4});
    EXPECT_MATRIX(a * 2, 2, 
                  {2, 4, 
                   6, 8});
    EXPECT_MATRIX(2.0f * a, 2, // 2.0f to test the template resolution 
                  {2, 4, 
                   6, 8});
    EXPECT_MATRIX((a + b) / 2, 2, 
                  {3, 4, 
                   5, 6});
    a += b;
    EXPECT_MATRIX(a, 2, 
                  {6, 8, 
                   10, 12});
    a -= b;
    EXPECT_MATRIX(a, 2, 
                  {1, 2, 
                   3, 4});
    a *= 3;
    EXPECT_MATRIX(a, 2, 
                  {3, 6, 
                   9, 12});
    a /= 3;
    EXPECT_MATRIX(a, 2, 
                  {1, 2, 
                   3, 4});

    EXPECT_MATRIX(a.mul(b), 2, 
                  {19, 22, 
                   43, 50});

    EXPECT_MATRIX(a.transpose(), 2, 
                  {1, 3, 
                   2, 4});

    EXPECT_MATRIX(a.neg(), 2, 
                  {-1, -2, 
                   -3, -4});

    EXPECT_MATRIX(-a, 2, 
                  {-1, -2, 
                   -3, -4});

    EXPECT_EQ(a.tr(), 5);
}

template <typename Matrix>
void matrix_det_suite() {
    auto test_det = [](const Matrix &mat,
                       const float result) {
        EXPECT_FLOAT_EQ(mat.det_recursion(), result);
        EXPECT_FLOAT_EQ(mat.det_gauss(), result); 
        EXPECT_FLOAT_EQ(mat.det_bareiss(), result);
        EXPECT_FLOAT_EQ(mat.det_lu(), result);
    };

    test_det(Matrix(0, {}), 0);

    test_det(Matrix(1, {0}),   0);
    test_det(Matrix(1, {1}),   1);
    test_det(Matrix(1, {-5}), -5);
    test_det(Matrix(1, {5}),   5);

    test_det(Matrix(2, {0, 0,
                        0, 0}), 0);
    test_det(Matrix(2, {1, 0,
                        0, 0}), 0);
    test_det(Matrix::create_eye(3, 1), 1);
    test_det(Matrix::create_eye(2, 5), 25);
    test_det(Matrix(2, {1, 1,
                        0, 1}), 1);
    test_det(Matrix(2, {1, 1,
                        1, 1}), 0);
    test_det(Matrix(2, {2, 1,
                        4, 3}), 2);
    test_det(Matrix(2, {1, 3,
                        2, 4}), -2);

    test_det(Matrix(3, {1, 2, 3,
                        0, 1, 4,
                        0, 0, 1}), 1);
    test_det(Matrix(3, {1, 2, 3,
                        2, 3, 2,
                        3, 2, 1}), -8);
    test_det(Matrix(3, {1, 2, 3,
                        1, 2, 3,
                        3, 2, 1}), 0);
    test_det(Matrix(5, {6, 4, 3, 11, 12,
                        1, 1, 1, 1,  0,
                        9, 3, 2, -8, 4,
                        5, 2, 1, 0, 0,
                        7, 5, 8, 3, 3}), 1210);
}

}
