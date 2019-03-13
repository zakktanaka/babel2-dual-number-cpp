#include <pch.h>
#include <babel/math/dual.hpp>

TEST(DualArithmetic, Plus) {
	using namespace babel::math;

	Dual v0(123, {0,1,1});
	Dual v1(-9.123, { 0,0,1 });

	auto ans = v0 + v1;

	EXPECT_EQ(ans.real(), 123 - 9.123);
	EXPECT_EQ(ans.first(0), 0);
	EXPECT_EQ(ans.first(1), 1);
	EXPECT_EQ(ans.first(2), 2);
	EXPECT_EQ(ans.first(3), 0);
}

TEST(DualArithmetic, Minus) {
	using namespace babel::math;

	Dual v0(123, {0,1,1});
	Dual v1(-9.123, { 0,0,1 });

	auto ans = v0 - v1;

	EXPECT_EQ(ans.real(), 123 + 9.123);
	EXPECT_EQ(ans.first(0), 0);
	EXPECT_EQ(ans.first(1), 1);
	EXPECT_EQ(ans.first(2), 0);
	EXPECT_EQ(ans.first(3), 0);
}

TEST(DualArithmetic, Multi) {
	using namespace babel::math;

	Dual v0(123, { 0,1,1 });
	Dual v1(-9.123, { 0,0,1 });

	auto ans = v0 * v1;

	EXPECT_EQ(ans.real(), 123 * - 9.123);
	EXPECT_EQ(ans.first(0), 0);
	EXPECT_EQ(ans.first(1), -9.123);
	EXPECT_EQ(ans.first(2), 123 - 9.123);
	EXPECT_EQ(ans.first(3), 0);
}

TEST(DualArithmetic, Div) {
	using namespace babel::math;

	Dual v0(123, { 0,1,1 });
	Dual v1(-9.123, { 0,0,1 });

	auto ans = v0 / v1;

	EXPECT_EQ(ans.real(), 123 / -9.123);
	EXPECT_EQ(ans.first(0), 0);
	EXPECT_EQ(ans.first(1), 1 / -9.123);
	EXPECT_EQ(ans.first(2), (-9.123 - 123) / (-9.123 * -9.123));
	EXPECT_EQ(ans.first(3), 0);
}
