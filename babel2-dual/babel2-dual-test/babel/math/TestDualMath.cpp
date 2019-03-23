#include <pch.h>
#include <babel/math/dual.hpp>

using Dual = babel::math::Dual<double>;

TEST(DualMath, Exp) {
	Dual v(2, { 0, 1, 2, });
	auto ans = exp(v);

	EXPECT_EQ(std::exp(2),     ans.real());
	EXPECT_EQ(0,               ans.first(0));
	EXPECT_EQ(std::exp(2),     ans.first(1));
	EXPECT_EQ(std::exp(2) * 2, ans.first(2));
	EXPECT_EQ(0,               ans.first(4));
}

TEST(DualMath, Log) {
	Dual v(2, { 0, 1, 2, });
	auto ans = log(v);

	EXPECT_EQ(std::log(2), ans.real());
	EXPECT_EQ(0,           ans.first(0));
	EXPECT_EQ(1.0 / 2,     ans.first(1));
	EXPECT_EQ(1.0 / 2 * 2, ans.first(2));
	EXPECT_EQ(0,           ans.first(4));
}

TEST(DualMath, Sqrt) {
	Dual v(2, { 0, 1, 2, });
	auto ans = sqrt(v);

	EXPECT_EQ(std::sqrt(2),           ans.real());
	EXPECT_EQ(0,                      ans.first(0));
	EXPECT_EQ(0.5 / std::sqrt(2),     ans.first(1));
	EXPECT_EQ(0.5 / std::sqrt(2) * 2, ans.first(2));
	EXPECT_EQ(0,                      ans.first(3));
}

TEST(DualMath, Pow) {
	Dual v(2, { 0, 1, 2, });
	auto ans = pow(v, 2.0);

	EXPECT_EQ(std::pow(2, 2), ans.real());
	EXPECT_EQ(0,              ans.first(0));
	EXPECT_EQ(2 * 2,          ans.first(1));
	EXPECT_EQ(2 * 2 * 2,      ans.first(2));
	EXPECT_EQ(0,              ans.first(3));
}

//TEST(DualMath, Pow1) {
//	Dual v(2, { 0, 1, 2, });
//	auto ans = pow(v, -0.1);
//
//	EXPECT_EQ(std::pow(2, -0.1), ans.real());
//	EXPECT_EQ(0,                 ans.first(0));
//	EXPECT_EQ(-0.1 * std::pow(2, -1.1),     ans.first(1));
//	EXPECT_EQ(-0.1 * std::pow(2, -1.1) * 2, ans.first(2));
//	EXPECT_EQ(0,                 ans.first(3));
//}
