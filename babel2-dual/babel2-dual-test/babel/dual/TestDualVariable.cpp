#include "../../pch.h"
#include <babel/dual/dual.hpp>

TEST(DualVarialbe, Real) {
	using namespace babel::dual;

	Dual v0(123, {});
	EXPECT_EQ(v0.real(), 123);

	Dual v1(-9.123, {0,0,1});
	EXPECT_EQ(v1.real(), -9.123);
}

TEST(DualVarialbe, First) {
	using namespace babel::dual;

	Dual v0(123, {});
	EXPECT_EQ(v0.first(0), 0);
	EXPECT_EQ(v0.first(1), 0);

	Dual v1(-9.123, { 0,0,1 });
	EXPECT_EQ(v1.first(0), 0);
	EXPECT_EQ(v1.first(1), 0);
	EXPECT_EQ(v1.first(2), 1);
	EXPECT_EQ(v1.first(3), 0);
}

