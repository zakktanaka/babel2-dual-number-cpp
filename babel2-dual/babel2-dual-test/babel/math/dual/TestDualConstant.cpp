#include <pch.h>
#include <babel/math/dual/dual.hpp>

TEST(DualConstant, Real) {
	using namespace babel::math::dual;

	Dual v = 123;
	EXPECT_EQ(v.real(), 123);

	EXPECT_EQ(Dual(-9.87654).real(), -9.87654);
}

TEST(DualConstant, First) {
	using namespace babel::math::dual;

	Dual v = 123;
	EXPECT_EQ(v.first(0), 0);

	EXPECT_EQ(v.first(1), 0);
	EXPECT_EQ(v.first(100), 0);
	EXPECT_EQ(v.first(-10000), 0);
}

