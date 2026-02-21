#include <gtest/gtest.h>

#include "long_number.hpp"

TEST(LongNumberTest, CreationAndEquality){
	biv::LongNumber a("123");
	biv::LongNumber b("123");
	biv::LongNumber c("124");
	
	ASSERT_TRUE(a == b);
	ASSERT_FALSE(a == c);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}