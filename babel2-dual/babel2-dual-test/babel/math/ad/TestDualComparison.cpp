#include <pch.h>
#include <babel/math/ad/Dual.hpp>

using AdContext = babel::math::ad::AdCalculationContext<double>;
using Dual = babel::math::ad::Dual<double>;

TEST(TestDualComparison, Equal) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 10 };
	Dual z{ 20 };

	EXPECT_TRUE(x == y);
	EXPECT_TRUE(x == 10);
	EXPECT_TRUE(10 == y);

	EXPECT_FALSE(x == z);
	EXPECT_FALSE(x == 20);
	EXPECT_FALSE(20 == y);
}

TEST(TestDualComparison, NotEqual) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 20 };
	Dual z{ 10 };

	EXPECT_TRUE(x != y);
	EXPECT_TRUE(x != 20);
	EXPECT_TRUE(10 != y);

	EXPECT_FALSE(x != z);
	EXPECT_FALSE(x != 10);
	EXPECT_FALSE(20 != y);
}

TEST(TestDualComparison, Less) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 20 };
	Dual z{ 0 };

	EXPECT_TRUE(x < y);
	EXPECT_TRUE(x < 20);
	EXPECT_TRUE(10 < y);

	EXPECT_FALSE(x < z);
	EXPECT_FALSE(x < 0);
	EXPECT_FALSE(30 < y);
}

TEST(TestDualComparison, More) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 5 };
	Dual z{ 20 };

	EXPECT_TRUE(x > y);
	EXPECT_TRUE(x > 5);
	EXPECT_TRUE(10 > y);

	EXPECT_FALSE(x > z);
	EXPECT_FALSE(x > 20);
	EXPECT_FALSE(0 > y);
}

TEST(TestDualComparison, LessEqual) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 20 };
	Dual z{ 0 };
	Dual w{ 10 };

	EXPECT_TRUE(x <= y);
	EXPECT_TRUE(x <= 20);
	EXPECT_TRUE(10 <= y);

	EXPECT_TRUE(x <= w);
	EXPECT_TRUE(x <= 10);
	EXPECT_TRUE(20 <= y);

	EXPECT_FALSE(x <= z);
	EXPECT_FALSE(x <= 0);
	EXPECT_FALSE(30 <= y);
}

TEST(TestDualComparison, MoreEqual) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 5 };
	Dual z{ 20 };
	Dual w{ 10 };

	EXPECT_TRUE(x >= y);
	EXPECT_TRUE(x >= 5);
	EXPECT_TRUE(10 >= y);

	EXPECT_TRUE(x >= w);
	EXPECT_TRUE(x >= 10);
	EXPECT_TRUE(5 >= y);

	EXPECT_FALSE(x >= z);
	EXPECT_FALSE(x >= 20);
	EXPECT_FALSE(0 >= y);
}
