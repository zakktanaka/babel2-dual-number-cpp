#include <pch.h>
#include <babel/math/dual.hpp>
#include <babel/math/core/constant.hpp>

using Dual = babel::math::Dual<double>;

TEST(DualDistribution, Cdf) {
	namespace math = babel::math;

	Dual v(0, { 0, 1, 2, });
	auto ans = math::cdf(v);

	EXPECT_EQ(0.5, ans.real());
	EXPECT_EQ(0,   ans.first(0));
	EXPECT_EQ(1.0 / math::sqrt(2.0 * math::Pi<double>::value),     ans.first(1));
	EXPECT_EQ(1.0 / math::sqrt(2.0 * math::Pi<double>::value) * 2, ans.first(2));
	EXPECT_EQ(0, ans.first(4));
}

TEST(DualDistribution, Cdf1) {
	namespace math = babel::math;

	Dual v(2, { 0, 1, 2, });
	auto ans = math::cdf(v);

	EXPECT_NEAR(0.977249868051821, ans.real(), 1e-14);
	EXPECT_NEAR(0, ans.first(0), 1e-14);
	EXPECT_NEAR(0.053990966513188, ans.first(1), 1e-14);
	EXPECT_NEAR(0.053990966513188 * 2, ans.first(2), 1e-14);
	EXPECT_NEAR(0, ans.first(4), 1e-14);
}
