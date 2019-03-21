#include <pch.h>
#include "AmericanOption.hpp"

TEST(AO, Test) {
	auto p = hiho::putAmericanOption(100, 0.2, 100, 0.005, 3, 30000);

	EXPECT_DOUBLE_EQ(13.122086669993108, p/*.real()*/);
}