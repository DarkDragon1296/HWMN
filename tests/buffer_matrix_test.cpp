#include "SqMatrixBf.hpp"

#include <gtest/gtest.h>
#include <vector>

TEST(SqMatrixBfTest, IntRecursionDetTest) {
    auto test = [](const SqMatrixBf<int> &mat_value,
                   const int result)
    {
        SqMatrixBf<int> mat(mat_value);
        EXPECT_EQ(mat.det_recursion(), result);
    };

    /* --- TESTS --- */
    test({0, {}}, 0);
}