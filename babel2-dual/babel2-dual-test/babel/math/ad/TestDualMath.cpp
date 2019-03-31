#include <pch.h>
#include <babel/math/ad/Dual.hpp>

using AdContext = babel::math::ad::AdCalculationContext<double>;
using Dual = babel::math::ad::Dual<double>;
namespace math = babel::math::ad;

TEST(TestDualMath, Exp) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 3 };

	auto ans = math::exp(x);
	EXPECT_EQ(math::exp(10), ans.x());
	EXPECT_EQ(math::exp(10), ans.differential(x));
	EXPECT_EQ(0, ans.differential(y));
}

TEST(TestDualMath, Log) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 3 };

	auto ans = math::log(x);
	EXPECT_EQ(math::log(10), ans.x());
	EXPECT_EQ(1.0 / 10, ans.differential(x));
	EXPECT_EQ(0, ans.differential(y));
}

TEST(TestDualMath, Sqrt) {
	AdContext context;

	Dual x{ 10 };
	Dual y{ 3 };

	auto ans = math::sqrt(x);
	EXPECT_EQ(math::sqrt(10), ans.x());
	EXPECT_EQ(0.5 / math::sqrt(10), ans.differential(x));
	EXPECT_EQ(0, ans.differential(y));
}

TEST(TestDualMath, Pow) {
	AdContext context;

	Dual x{ 2 };
	Dual y{ 3 };

	auto a0 = math::pow(x, 3);
	EXPECT_EQ(math::pow(2, 3), a0.x());
	EXPECT_EQ(3 * math::pow(2, 2), a0.differential(x));
	EXPECT_EQ(0, a0.differential(y));

	auto a1 = math::pow(2, y);
	EXPECT_EQ(math::pow(2, 3), a1.x());
	EXPECT_EQ(0, a1.differential(x));
	EXPECT_EQ(math::log(2) * math::pow(2, 3), a1.differential(y));

	auto a2 = math::pow(x, y);
	EXPECT_EQ(math::pow(2, 3), a2.x());
	EXPECT_EQ(3 * math::pow(2, 2), a2.differential(x));
	EXPECT_EQ(math::log(2) * math::pow(2, 3), a1.differential(y));
}

TEST(TestDualMath, Cdf) {
	AdContext context;

	Dual x{ 0.5 };
	Dual y{ 3 };

	auto ans = math::cdf(x);
	EXPECT_EQ(math::cdf(0.5), ans.x());
	EXPECT_EQ(math::pdf(0.5), ans.differential(x));
	EXPECT_EQ(0, ans.differential(y));
}

TEST(TestDualMath, Pdf) {
	AdContext context;

	Dual x{ 0.5 };
	Dual y{ 3 };

	auto ans = math::pdf(x);
	EXPECT_EQ(math::pdf(0.5), ans.x());
	EXPECT_EQ(math::dpdf(0.5), ans.differential(x));
	EXPECT_EQ(0, ans.differential(y));
}
