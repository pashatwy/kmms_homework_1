#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "shell_sorting.hpp"

TEST(ShellSortTest, AnyElementsCount) {
    std::vector<int> actual = {1, 8, 2, 5, 3, 11};
    gpi::shell_sort(actual); 
    std::vector<int> expected = {1, 5, 3, 2, 8, 11};

    ASSERT_EQ(expected.size(), actual.size())
        << "Разные размеры ожидаемого и отсортированного массивов";

    for (int i = 0; i < actual.size(); i++) {
        ASSERT_EQ(expected[i], actual[i]) 
            << "Массив ожидаемый и отсортированный отличаются в элементе с индексом "
            << i;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}