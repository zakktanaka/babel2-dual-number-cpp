#include <pch.h>
#include <babel/math/ad/Dual.hpp>

using AdContext = babel::math::ad::AdCalculationContext<double>;
using Dual      = babel::math::ad::Dual<double>;

TEST(TestDualArithmetic, Add) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 20 };

	x += 30;
	EXPECT_EQ(10 + 30, x.x());

	x += y;
	EXPECT_EQ(10 + 20 + 30, x.x());
}