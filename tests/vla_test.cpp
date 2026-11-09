#include <gtest/gtest.h>
#include "VLA.hpp"

TEST(VLATest, ConstructorsFactoriesAndIterators) {
    buffers::VLA<int> empty;
    EXPECT_EQ(empty.size(), 0U);
    EXPECT_EQ(empty.begin(), empty.end());
    buffers::VLA<int> exact{1, 2, 3};
    EXPECT_EQ(exact.size(), 3U);
    EXPECT_EQ(exact[0], 1);
    EXPECT_EQ(exact[2], 3);
    buffers::VLA<int> partial(4, {7, 8});
    EXPECT_EQ(partial[0], 7);
    EXPECT_EQ(partial[1], 8);
    EXPECT_EQ(partial[2], 0);
    EXPECT_EQ(partial[3], 0);
    buffers::VLA<int> excess(2, {4, 5, 6});
    EXPECT_EQ(excess[0], 4);
    EXPECT_EQ(excess[1], 5);
    auto filled = buffers::VLA<int>::create(3, 11);
    for (int value : filled)
        EXPECT_EQ(value, 11);
    EXPECT_EQ(buffers::VLA<int>::create(0, 11).size(), 0U);

    const auto &constant = exact;
    EXPECT_EQ(constant.begin(), constant.cbegin());
    EXPECT_EQ(constant.end(), constant.cend());
    EXPECT_EQ(std::distance(exact.cbegin(), exact.cend()), 3);
}

TEST(VLATest, CopyMoveAndAssignments) {
    buffers::VLA<int> source{1, 2, 3};
    buffers::VLA<int> copy(source);
    copy[0] = 9;
    EXPECT_EQ(source[0], 1);
    EXPECT_EQ(copy[0], 9);
    copy = copy;
    EXPECT_EQ(copy[2], 3);

    buffers::VLA<int> assigned{8};
    assigned = source;
    EXPECT_EQ(assigned.size(), 3U);
    EXPECT_EQ(assigned[2], 3);
    buffers::VLA<int> same_size{4, 4, 4};
    same_size = source;
    EXPECT_EQ(same_size[1], 2);
    assigned = buffers::VLA<int>{};
    EXPECT_EQ(assigned.size(), 0U);

    buffers::VLA<int> moved(std::move(source));
    EXPECT_EQ(moved.size(), 3U);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(source.size(), 0U);
    buffers::VLA<int> move_assigned{6};
    move_assigned = std::move(moved);
    EXPECT_EQ(move_assigned.size(), 3U);
    EXPECT_EQ(move_assigned[2], 3);
    EXPECT_EQ(moved.size(), 0U);
}