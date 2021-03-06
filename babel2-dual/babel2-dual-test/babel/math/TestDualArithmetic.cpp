#include <pch.h>
#include <babel/math/dual.hpp>

using Dual = babel::math::Dual<double>;

TEST(DualArithmetic, Plus) {
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
	Dual v0(123, { 0,1,1 });
	Dual v1(-9.123, { 0,0,1 });

	auto ans = v0 / v1;

	EXPECT_EQ(ans.real(), 123 / -9.123);
	EXPECT_EQ(ans.first(0), 0);
	EXPECT_EQ(ans.first(1), 1 / -9.123);
	EXPECT_EQ(ans.first(2), (-9.123 - 123) / (-9.123 * -9.123));
	EXPECT_EQ(ans.first(3), 0);
}

TEST(DualArithmetic, CompoundAssignmentPlus) {
	Dual v(123, { 0,1,1 });
	v += Dual(-9.123, { 0,0,1 });

	EXPECT_EQ(v.real(), 123 - 9.123);
	EXPECT_EQ(v.first(0), 0);
	EXPECT_EQ(v.first(1), 1);
	EXPECT_EQ(v.first(2), 2);
	EXPECT_EQ(v.first(3), 0);
}

TEST(DualArithmetic, CompoundAssignmentMinus) {
	Dual v(123, { 0,1,1 });
	v -= Dual(-9.123, { 0,0,1 });

	EXPECT_EQ(v.real(), 123 + 9.123);
	EXPECT_EQ(v.first(0), 0);
	EXPECT_EQ(v.first(1), 1);
	EXPECT_EQ(v.first(2), 0);
	EXPECT_EQ(v.first(3), 0);
}

TEST(DualArithmetic, CompoundAssignmentMulti) {
	Dual v(123, { 0,1,1 });
	v *= Dual(-9.123, { 0,0,1 });

	EXPECT_EQ(v.real(), 123 * -9.123);
	EXPECT_EQ(v.first(0), 0);
	EXPECT_EQ(v.first(1), -9.123);
	EXPECT_EQ(v.first(2), 123 - 9.123);
	EXPECT_EQ(v.first(3), 0);
}

TEST(DualArithmetic, CompoundAssignmentDiv) {
	Dual v(123, { 0,1,1 });
	v /= Dual(-9.123, { 0,0,1 });

	EXPECT_EQ(v.real(), 123 / -9.123);
	EXPECT_EQ(v.first(0), 0);
	EXPECT_EQ(v.first(1), 1 / -9.123);
	EXPECT_EQ(v.first(2), (-9.123 - 123) / (-9.123 * -9.123));
	EXPECT_EQ(v.first(3), 0);
}

TEST(DualArithmetic, PrefixIncrement) {
	Dual v(123, { 0,1,1 });
	++v;

	EXPECT_EQ(v.real(), 123 + 1);
	EXPECT_EQ(v.first(0), 0);
	EXPECT_EQ(v.first(1), 1);
	EXPECT_EQ(v.first(2), 1);
	EXPECT_EQ(v.first(3), 0);
}

TEST(DualArithmetic, PrefixDecrement) {
	Dual v(123, { 0,1,1 });
	--v;

	EXPECT_EQ(v.real(), 123 - 1);
	EXPECT_EQ(v.first(0), 0);
	EXPECT_EQ(v.first(1), 1);
	EXPECT_EQ(v.first(2), 1);
	EXPECT_EQ(v.first(3), 0);
}

TEST(DualArithmetic, PostfixIncrement) {
	Dual v(123, { 0,1,1 });
	auto p = v++;

	EXPECT_EQ(p.real(), 123);
	EXPECT_EQ(p.first(0), 0);
	EXPECT_EQ(p.first(1), 1);
	EXPECT_EQ(p.first(2), 1);
	EXPECT_EQ(p.first(3), 0);

	EXPECT_EQ(v.real(), 123 + 1);
	EXPECT_EQ(v.first(0), 0);
	EXPECT_EQ(v.first(1), 1);
	EXPECT_EQ(v.first(2), 1);
	EXPECT_EQ(v.first(3), 0);
}

TEST(DualArithmetic, PostfixDecrement) {
	Dual v(123, { 0,1,1 });
	auto p = v--;

	EXPECT_EQ(p.real(), 123);
	EXPECT_EQ(p.first(0), 0);
	EXPECT_EQ(p.first(1), 1);
	EXPECT_EQ(p.first(2), 1);
	EXPECT_EQ(p.first(3), 0);

	EXPECT_EQ(v.real(), 123 - 1);
	EXPECT_EQ(v.first(0), 0);
	EXPECT_EQ(v.first(1), 1);
	EXPECT_EQ(v.first(2), 1);
	EXPECT_EQ(v.first(3), 0);
}
