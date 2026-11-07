#include "SqMatrixBf.hpp"
#include "SqMatrixJg.hpp"
#include <gtest/gtest.h>
#include <vector>

TEST(SqMatrixBfRecursionTest, IntRecursionDetTest) {
    auto test = [](const SqMatrixBf<int> &mat_value,
                   const int result)
    {
        SqMatrixBf<int> mat(mat_value);
        EXPECT_EQ(mat.det_recursion(), result);
    };

    /* --- TESTS --- */
    test({0, {}}, 0);

    test({1, { 0}},  0);
    test({1, { 1}},  1);
    test({1, {-5}}, -5);
    test({1, { 5}},  5);

    test({2, {0, 0,
              0, 0}}, 0);
    test({2, {1, 0,
              0, 0}}, 0);
    test({2, {1, 0,
              0, 1}}, 1);
    test({2, {1, 1,
              0, 1}}, 1);
    test({2, {1, 1,
              1, 1}}, 0);
    test({2, {2, 1,
              4, 3}}, 2);
    test({2, {1, 3,
              2, 4}},-2);

    test({3, {1, 0, 0,
              0, 1, 0,
              0, 0, 1}}, 1);
    test({3, {1, 2, 3,
              0, 1, 4,
              0, 0, 1}}, 1);
    test({3, {1, 2, 3,
              2, 3, 2,
              3, 2, 1}}, -8);

#if 0
    test({11, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}}, 1);
    #endif
}

TEST(SqMatrixBfGaussTest, FloatRecursionDetTest) {
    auto test = [](const SqMatrixBf<float> &mat_value,
                   const float result)
    {
        SqMatrixBf<float> mat(mat_value);
        EXPECT_FLOAT_EQ(mat.det_gauss(), result);
    };

    /* --- TESTS --- */
    test({0, {}}, 0);

    test({1, { 0}},  0);
    test({1, { 1}},  1);
    test({1, {-5}}, -5);
    test({1, { 5}},  5);

    test({2, {0, 0,
              0, 0}}, 0);
    test({2, {1, 0,
              0, 0}}, 0);
    test({2, {1, 0,
              0, 1}}, 1);
    test({2, {1, 1,
              0, 1}}, 1);
    test({2, {1, 1,
              1, 1}}, 0);
    test({2, {2, 1,
              4, 3}}, 2);
    test({2, {1, 3,
              2, 4}},-2);

    test({3, {1, 0, 0,
              0, 1, 0,
              0, 0, 1}}, 1);
    test({3, {1, 2, 3,
              0, 1, 4,
              0, 0, 1}}, 1);
    test({3, {1, 2, 3,
              2, 3, 2,
              3, 2, 1}}, -8);
}

TEST(SqMatrixBfBareissTest, FloatRecursionDetTest) {
    auto test = [](const SqMatrixBf<float> &mat_value,
                   const float result)
    {
        SqMatrixBf<float> mat(mat_value);
        EXPECT_FLOAT_EQ(mat.det_bareiss(), result);
    };

    /* --- TESTS --- */
    test({0, {}}, 0);

    test({1, { 0}},  0);
    test({1, { 1}},  1);
    test({1, {-5}}, -5);
    test({1, { 5}},  5);

    test({2, {0, 0,
              0, 0}}, 0);
    test({2, {1, 0,
              0, 0}}, 0);
    test({2, {1, 0,
              0, 1}}, 1);
    test({2, {1, 1,
              0, 1}}, 1);
    test({2, {1, 1,
              1, 1}}, 0);
    test({2, {2, 1,
              4, 3}}, 2);
    test({2, {1, 3,
              2, 4}},-2);

    test({3, {1, 0, 0,
              0, 1, 0,
              0, 0, 1}}, 1);
    test({3, {1, 2, 3,
              0, 1, 4,
              0, 0, 1}}, 1);
    test({3, {1, 2, 3,
              2, 3, 2,
              3, 2, 1}}, -8);
}