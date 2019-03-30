#include <pch.h>
#include <babel/math/ad/Dual.hpp>

using AdContext = babel::math::ad::AdCalculationContext<double>;
using Dual      = babel::math::ad::Dual<double>;

TEST(TestDualArithmetic, UnaryAdd) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 20 };

	auto r = x;
	r += 30;
	EXPECT_EQ(10 + 30, r.x());
	EXPECT_EQ(1, r.differential(x));
	EXPECT_EQ(0, r.differential(y));

	r += y;
	EXPECT_EQ(10 + 20 + 30, r.x());
	EXPECT_EQ(1, r.differential(x));
	EXPECT_EQ(1, r.differential(y));
}

TEST(TestDualArithmetic, UnarySubtract) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 20 };

	auto r = x;
	r -= 30;
	EXPECT_EQ(10 - 30, r.x());
	EXPECT_EQ(1, r.differential(x));
	EXPECT_EQ(0, r.differential(y));

	r -= y;
	EXPECT_EQ(10 - 20 - 30, r.x());
	EXPECT_EQ(1, r.differential(x));
	EXPECT_EQ(-1, r.differential(y));
}

TEST(TestDualArithmetic, UnaryTimes) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 20 };

	auto r = x;
	r *= 30;
	EXPECT_EQ(10 * 30, r.x());
	EXPECT_EQ(30, r.differential(x));
	EXPECT_EQ(0, r.differential(y));

	r *= y;
	EXPECT_EQ(10 * 20 * 30, r.x());
	EXPECT_EQ(20 * 30, r.differential(x));
	EXPECT_EQ(10 * 30, r.differential(y));
}

TEST(TestDualArithmetic, UnaryDivide) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 20 };

	auto r = x;
	r /= 30;
	EXPECT_EQ(10.0 / 30, r.x());
	EXPECT_EQ(1.0/30, r.differential(x));
	EXPECT_EQ(0, r.differential(y));

	r /= y;
	EXPECT_EQ(10.0 / 20 / 30, r.x());
	EXPECT_EQ(1.0 / 20 / 30, r.differential(x));
	EXPECT_DOUBLE_EQ(-10.0 / (20*20) / 30, r.differential(y));
}

TEST(TestDualArithmetic, OtherUnary) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 0 };

	++x;
	EXPECT_EQ(10 + 1, x.x());
	EXPECT_EQ(1, x.differential(x));
	EXPECT_EQ(0, x.differential(y));
	--x;
	EXPECT_EQ(10, x.x());
	EXPECT_EQ(1, x.differential(x));
	EXPECT_EQ(0, x.differential(y));

	auto pp = x++;
	EXPECT_EQ(10, pp.x());
	EXPECT_EQ(0, pp.differential(x));
	EXPECT_EQ(0, pp.differential(y));
	EXPECT_EQ(10 + 1, x.x());
	EXPECT_EQ(1, x.differential(x));
	EXPECT_EQ(0, x.differential(y));

	auto pm = x--;
	EXPECT_EQ(10 + 1, pm.x());
	EXPECT_EQ(0, pm.differential(x));
	EXPECT_EQ(0, pm.differential(y));
	EXPECT_EQ(10, x.x());
	EXPECT_EQ(1, x.differential(x));
	EXPECT_EQ(0, x.differential(y));

	auto p = +x;
	EXPECT_EQ(10, p.x());
	EXPECT_EQ(1, x.differential(x));
	EXPECT_EQ(0, x.differential(y));
	auto m = -x;
	EXPECT_EQ(-10, m.x());
	EXPECT_EQ(-1, m.differential(x));
	EXPECT_EQ(0, m.differential(y));
}
