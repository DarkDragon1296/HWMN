#include <gtest/gtest.h>
#include "VLA.hpp"

using namespace buffers;

#define EXPECT_VLA(actual, ...) \
    expect_vla(actual, __VA_ARGS__, __FILE__, __LINE__)

namespace {
template <typename T>
void expect_vla(const VLA<T> &actual,
                std::initializer_list<T> expected,
                const char* file, size_t line); 

struct DefaultInitializable{
    int a = 5;
    bool operator==(const DefaultInitializable& rhs) const {
        return a == rhs.a;
    }
};
}

TEST(VLATest, ConstructorsAndFactories) {
    {
        VLA<int> default_ctored;
        EXPECT_EQ(default_ctored.size(), 0U);
        EXPECT_EQ(default_ctored.begin(), default_ctored.end());
    }

    {
        VLA<int> exact{1, 2, 3};
        EXPECT_VLA(exact, {1, 2, 3});
        exact[1] = 5;
        EXPECT_VLA(exact, {1, 5, 3});
    }

    {
        VLA<int> partial(4, {7, 8});
        EXPECT_VLA(partial, {7, 8, 0, 0});
    }

    {
        VLA<int> excess(2, {4, 5, 6});
        EXPECT_VLA(excess, {4, 5});
    }

    {
        std::initializer_list<int> list = {5, 6, 7, 8, 9, 10, 11, 12};
        VLA<int> adaptive{list};
        EXPECT_VLA(adaptive, list);
    }

    {
        auto filled = VLA<int>::create(3, 11);
        EXPECT_VLA(filled, {11, 11, 11});
    }

    {
        EXPECT_EQ(VLA<int>::create(0, 11).size(), 0);
    }

    {
        auto default_filled = VLA<int>::create(4);
        EXPECT_VLA(default_filled, {0, 0, 0, 0});
    }

    {
        auto default_filled_struct = VLA<DefaultInitializable>::create(3);
        EXPECT_VLA(default_filled_struct, {{}, {}, {}});
    }
}

TEST(VLATest, Iterators) {
    VLA<int> exact(4, {1, 2, 3, 4});
    EXPECT_EQ(std::distance(exact.begin(), exact.end()), 4);
    auto it = exact.begin();
    for (size_t i = 0; i < exact.size(); ++i, ++it)
        EXPECT_EQ(exact[i], *it);

    const auto &constant = exact;
    EXPECT_EQ(constant.begin(), constant.cbegin());
    EXPECT_EQ(constant.end(), constant.cend());
}

TEST(VLATest, CopyMoveAndAssignments) {
    VLA<int> source{1, 2, 3};
    {
        VLA<int> copy(source);
        EXPECT_VLA(copy, {1, 2, 3});
        copy[0] = 9;
        EXPECT_EQ(source[0], 1);
        EXPECT_EQ(copy[0], 9);
        copy = copy;
        EXPECT_VLA(copy, {9, 2, 3});
    }

    {
        VLA<int> assigned{7, 5};
        assigned = source;
        EXPECT_VLA(assigned, {1, 2, 3}); 
        assigned = VLA<int>{};
        EXPECT_EQ(assigned.size(), 0);
    }

    {
        VLA<int> same_size{4, 4, 4};
        same_size = source;
        EXPECT_VLA(same_size, {1, 2, 3});
    }

    {
        VLA<int> moved(std::move(source));
        EXPECT_VLA(moved, {1, 2, 3});
        EXPECT_EQ(source.size(), 0);

        VLA<int> move_assigned{34, 56};
        move_assigned = std::move(moved);
        EXPECT_VLA(move_assigned, {1, 2, 3});
        EXPECT_EQ(moved.size(), 0U);
    }
}

namespace {
template <typename T>
void expect_vla(const VLA<T> &actual, 
                std::initializer_list<T> expected,
                const char* file, size_t line) {
    ASSERT_EQ(actual.size(), expected.size()) 
        << "called from " << file << ":" << line;
    auto value = expected.begin();
    for (size_t i = 0, n = actual.size(); i < n; ++i, ++value)
        EXPECT_EQ(actual[i], *value) 
            << "at (" << i << ")\n"
            << "called from " << file << ":" << line;
}
}
