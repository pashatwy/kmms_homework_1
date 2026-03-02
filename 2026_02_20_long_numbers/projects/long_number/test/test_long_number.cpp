#include <gtest/gtest.h>

#include "long_number.hpp"

class LongNumberTest : public testing::Test {
	public:
		biv::LongNumber 
			z1{"-1"}, z2{"-2"},z6{"-6"}, z7{"-7"}, z10{"-10"}, z1234{"-1234"}, z1244{"-1244"},
			
			n1{"1"}, n2{"2"}, n3{"3"}, n7{"7"}, n10{"10"}, n12{"12"}, n99{"99"}, n100{"100"}, n1234{"1234"}, n1246{"1246"},
			
			z1_copy{"-1"}, z0{"0"}, n1_copy{"1"}, n12_copy{"12"};
};

TEST_F(LongNumberTest, Equality){
	ASSERT_TRUE(z1 == z1_copy) << "-1 == -1";
	ASSERT_TRUE(n12 == n12_copy) << "12 == 12";
	ASSERT_FALSE(z1 == n1) << "-1 == 1";
	ASSERT_FALSE(z1234 == n1234) << "-1234 == 1234";
}

TEST_F(LongNumberTest, NoEquality){
	ASSERT_TRUE(z1 != n1) << "-1 != 1";
	ASSERT_TRUE(n12 != n1234) << "12 != 1234";
	ASSERT_FALSE(z1 != z1_copy) << "-1 != -1";
	ASSERT_FALSE(n1 != n1_copy) << "1 != 1";
}

TEST_F(LongNumberTest, More){
	ASSERT_TRUE(z1 > z10) << "-1 > -10";
	ASSERT_TRUE(n1 > z1234) << "1 > -1234";
	ASSERT_FALSE(z10 > n12) << "-10 > 12";
	ASSERT_FALSE(n1 > n1234) << "1 > 1234";
}

TEST_F(LongNumberTest, Less){
	ASSERT_TRUE(z10 < z1) << "-10 < -1";
	ASSERT_TRUE(z1234 < n1234) << "-1234 < 1234";
	ASSERT_FALSE(n1234 < n1) << "1234 < 1";
	ASSERT_FALSE(n1 < z1) << "1 < -1";
}

TEST_F(LongNumberTest, Summ){
	EXPECT_EQ(z1244, z1234 + z10) << "-1234 + (-10) = -1244 | два минуса";
	EXPECT_EQ(n1246, n12 + n1234) << "12 + 1234 = 1246 | два плюса";
	EXPECT_EQ(n100, n1_copy + n99) << "1 + 99 = 100 | переход к новой длине";
	EXPECT_EQ(z0, z1234 + n1234) << "-1234 + 1234 = 0 | разные знаки";
}

TEST_F(LongNumberTest, Subtraction){
	EXPECT_EQ(n1234, n1246 - n12) << "1246 - 12 = 1234 | два плюса";
	EXPECT_EQ(z1234, z1244 - z10) << "-1244 - (-10) = -1234 | два минуса, первый меньше второго";
	EXPECT_EQ(n1234, z10 - z1244) << "-10 - (-1244) = 1234 | два минуса, первый больше второго";
	EXPECT_EQ(n10, z1234 - z1244) << "-1234 - (-1244) = 10 | два минуса, первый меньше второго";
	EXPECT_EQ(n100, n99 - z1) << "99 - (-1) = 100 разные знаки, новая длина";
}
TEST_F(LongNumberTest, Multiplication){
	EXPECT_EQ(n12_copy, n12 * n1) << "12 * 1 = 12";
	EXPECT_EQ(n1234, z1 * z1234) << "-1 * (-1234) = 1234";
	EXPECT_EQ(z0, z0* n1234) << "0 * 1234 = 0";
	EXPECT_EQ(z6, z2 * n3) << "-2 * 3 = -6";
}

TEST_F(LongNumberTest, Division){
	EXPECT_EQ(n12_copy, n12 / n1) << "12 / 1 = 12";
	EXPECT_EQ(n12, n1234 / n100) << "1234 / 100 = 12";
	EXPECT_EQ(z10, n10 / z1) << "10 / (-1) = -10 ";
	EXPECT_EQ(z2, z7 / n3) << "-7 / 3 = -2";
	EXPECT_EQ(n2, n7 / n3) << "7 / 3 = 2";	
}

TEST_F(LongNumberTest, DivisionWithRemainder){
	EXPECT_EQ(n1_copy, n1 % n10) << "1 % 10 = 1";
	EXPECT_EQ(z0, n12 % n12_copy) << "12 % 12 = 0";
	EXPECT_EQ(z1, z7 % n3) << "-7 % 3 = -1";
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}