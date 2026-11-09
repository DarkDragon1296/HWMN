#include "SqMatrixBf.hpp"
#include "SqMatrixJg.hpp"
#include <gtest/gtest.h>

namespace {

template <typename Matrix>
void expect_matrix(const Matrix &actual, size_t n,
                   std::initializer_list<int> expected) {
    ASSERT_EQ(actual.size(), n);
    auto value = expected.begin();
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j, ++value)
            EXPECT_EQ(actual[i][j], *value) << "at (" << i << ", " << j << ")";
}

template <typename Matrix>
void matrix_suite() {
    Matrix empty;
    EXPECT_EQ(empty.size(), 0U);
    Matrix zero(0);
    EXPECT_EQ(zero.size(), 0U);

    Matrix partial(2, {1, 2});
    expect_matrix(partial, 2, {1, 2, 0, 0});
    partial[1][0] = 7;
    EXPECT_EQ(partial[1][0], 7);
    const Matrix &constant = partial;
    EXPECT_EQ(constant[0][1], 2);

    auto scalar = Matrix::create_scalar(2, 5);
    expect_matrix(scalar, 2, {5, 5, 5, 5});
    expect_matrix(Matrix::create_scalar(0, 5), 0, {});
    expect_matrix(Matrix::create_eye(3, 4), 3, {4, 0, 0, 0, 4, 0, 0, 0, 4});
    expect_matrix(Matrix::create_eye(0, 4), 0, {});

    Matrix a(2, {1, 2, 3, 4});
    Matrix b(2, {5, 6, 7, 8});
    expect_matrix(a + b, 2, {6, 8, 10, 12});
    expect_matrix(b - a, 2, {4, 4, 4, 4});
    expect_matrix(a * 2, 2, {2, 4, 6, 8});
    expect_matrix(2 * a, 2, {2, 4, 6, 8});
    expect_matrix(b / 2, 2, {2, 3, 3, 4});
    a += b;
    expect_matrix(a, 2, {6, 8, 10, 12});
    a -= b;
    a *= 3;
    a /= 3;
    expect_matrix(a, 2, {1, 2, 3, 4});
    expect_matrix(a.mul(b), 2, {19, 22, 43, 50});
    expect_matrix(a.transpose(), 2, {1, 3, 2, 4});
    expect_matrix(a.neg(), 2, {-1, -2, -3, -4});
    EXPECT_EQ(a.tr(), 5);
    expect_matrix(a.minor(0, 0), 1, {4});
    EXPECT_EQ(a.max_row_elem_index(0, 0), 1U);
    EXPECT_EQ(a.max_col_elem_index(0, 0), 1U);

    Matrix rows(2, {1, 2, 3, 4});
    rows.swap_rows(0, 1);
    expect_matrix(rows, 2, {3, 4, 1, 2});
    rows.swap_rows(1, 1);
    rows.swap_cols(0, 1);
    expect_matrix(rows, 2, {4, 3, 2, 1});
    rows.add_row(0, 1, 2);
    expect_matrix(rows, 2, {8, 5, 2, 1});
    rows.sub_row(0, 1, 2);
    expect_matrix(rows, 2, {4, 3, 2, 1});
    rows.mul_row(1, 3);
    rows.div_row(1, 3);
    rows.add_col(0, 1, 2);
    expect_matrix(rows, 2, {10, 3, 4, 1});
    rows.sub_col(0, 1, 2);
    expect_matrix(rows, 2, {4, 3, 2, 1});
    rows.mul_col(1, 2);
    rows.div_col(1, 2);
    expect_matrix(rows, 2, {4, 3, 2, 1});

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

    auto test_det = [](const Matrix &mat,
                       const float result)
    {
        EXPECT_EQ(mat.det_recursion(), result);
        EXPECT_EQ(mat.det_gauss(), result); // TODO: det_gauss seems to be broken!
        EXPECT_EQ(mat.det_bareiss(), result);
        EXPECT_EQ(mat.det_lu(), result);
    };

    /* --- TESTS --- */
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
                        2, 4}),-2);

    test_det(Matrix(3, {1, 2, 3,
                        0, 1, 4,
                        0, 0, 1}), 1);
    test_det(Matrix(3, {1, 2, 3,
                        2, 3, 2,
                        3, 2, 1}), -8);
}

TEST(SqMatrixBfTest, PublicOperations) { matrix_suite<mat::SqMatrixBf<int>>(); }
TEST(SqMatrixJgTest, PublicOperations) { matrix_suite<mat::SqMatrixJg<int>>(); }

} // namespace
