#include <pch.h>
#include <babel/math/dual.hpp>

TEST(DualMath, Exp) {
	using namespace babel::math;

	Dual v(2, { 0, 1, 2, });
	auto ans = exp(v);

	EXPECT_EQ(std::exp(2),     ans.real());
	EXPECT_EQ(0,               ans.first(0));
	EXPECT_EQ(std::exp(2),     ans.first(1));
	EXPECT_EQ(std::exp(2) * 2, ans.first(2));
	EXPECT_EQ(0,               ans.first(4));
}

TEST(DualMath, Log) {
	using namespace babel::math;

	Dual v(2, { 0, 1, 2, });
	auto ans = log(v);

	EXPECT_EQ(std::log(2), ans.real());
	EXPECT_EQ(0,           ans.first(0));
	EXPECT_EQ(1.0 / 2,     ans.first(1));
	EXPECT_EQ(1.0 / 2 * 2, ans.first(2));
	EXPECT_EQ(0,           ans.first(4));
}
