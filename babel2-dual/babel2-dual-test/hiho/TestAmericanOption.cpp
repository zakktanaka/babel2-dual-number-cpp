#include <pch.h>
#include "AmericanOption.hpp"

TEST(AO, Test) {
	auto p = hiho::putAmericanOption(100, 0.2, 100, 0.005, 3, 1000);

	EXPECT_DOUBLE_EQ(13.494113143178293, p.real());
}