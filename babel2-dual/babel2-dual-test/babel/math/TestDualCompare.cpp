#include <pch.h>
#include <babel/math/dual.hpp>

using Dual = babel::math::Dual<double>;

TEST(DualCompare, Compare) {
	Dual v0(123, { 0,1,1 });
	Dual v1(-9.123, { 0,0,1 });

	EXPECT_FALSE(v0 < v1);
	EXPECT_TRUE (v1 < v0);

	EXPECT_TRUE (v0 > v1);
	EXPECT_FALSE(v1 > v0);

	EXPECT_FALSE(v0 <= v1);
	EXPECT_TRUE (v1 <= v0);
	EXPECT_TRUE (v0 <= v0);

	EXPECT_TRUE (v0 >= v1);
	EXPECT_FALSE(v1 >= v0);
	EXPECT_TRUE (v0 >= v0);
}


TEST(DualCompare, EqualityCompare) {
	Dual v0(123, { 0,1,1 });
	Dual v1(-9.123, { 0,0,1 });

	EXPECT_FALSE(v0 == v1);
	EXPECT_TRUE (v0 == v0);

	EXPECT_TRUE (v0 != v1);
	EXPECT_FALSE(v0 != v0);
}
