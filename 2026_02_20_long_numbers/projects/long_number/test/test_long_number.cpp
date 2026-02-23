#include <gtest/gtest.h>

#include "long_number.hpp"

class LongNumberTest : public testing::Test {
	public:
		biv::LongNumber 
			z1{"-1"}, z1_copy{"-1"},  z10{"-10"}, z1234{"-1234"},
			
			n1{"1"}, n1_copy{"1"}, n12{"12"}, n12_copy{"12"}, n1234{"1234"},
			
			z0{"0"}, n1246{"1246"}, z1244{"-1244"}, n99{"99"}, n100{"100"}, n10{"10"};
};

TEST_F(LongNumberTest, Equality){
	ASSERT_TRUE(z1 == z1_copy);
	ASSERT_TRUE(n12 == n12_copy);
	ASSERT_FALSE(z1 == n1);
	ASSERT_FALSE(z1234 == n1234);
}

TEST_F(LongNumberTest, NoEquality){
	ASSERT_TRUE(z1 != n1);
	ASSERT_TRUE(n12 != n1234);
	ASSERT_FALSE(z1 != z1_copy);
	ASSERT_FALSE(n1 != n1_copy);
}

TEST_F(LongNumberTest, more){
	ASSERT_TRUE(z1 > z10);
	ASSERT_TRUE(n1 > z1234);
	ASSERT_FALSE(z10 > n12);
	ASSERT_FALSE(n1 > n1234);
}

TEST_F(LongNumberTest, less){
	ASSERT_TRUE(z10 < z1);
	ASSERT_TRUE(z1234 < n1234);
	ASSERT_FALSE(n1234 < n1);
	ASSERT_FALSE(n1 < z1);
}

TEST_F(LongNumberTest, summ){
	EXPECT_EQ(z1244, z1234 + z10) << "-1234 + (-10) = -1244 | два минуса";
	EXPECT_EQ(n1246, n12 + n1234) << "12 + 1234 = 1246 | два плюса";
	EXPECT_EQ(n100, n1_copy + n99) << "1 + 99 = 100 | переход к новой длине";
	EXPECT_EQ(z0, z1234 + n1234) << "-1234 + 1234 = 0 | разные знаки";
}

TEST_F(LongNumberTest, subtraction){
	EXPECT_EQ(n1234, n1246 - n12) << "1246 - 12 = 1234 | два плюса";
	EXPECT_EQ(z1234, z1244 - z10) << "-1244 - (-10) = -1234 | два минуса, первый меньше второго";
	EXPECT_EQ(n1234, z10 - z1244) << "-10 - (-1244) = 1234 | два минуса, первый больше второго";
	EXPECT_EQ(n10, z1234 - z1244) << "-1234 - (-1244) = 10 | два минуса, первый меньше второго";
	EXPECT_EQ(n100, n99 - z1) << "99 - (-1) = 100 разные знаки, новая длина";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}