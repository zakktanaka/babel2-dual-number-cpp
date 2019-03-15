#include <pch.h>
#include <babel/math/dual.hpp>
#include <babel/math/core/constant.hpp>

TEST(DualDistribution, Cdf) {
	namespace math = babel::math;

	math::Dual v(0, { 0, 1, 2, });
	auto ans = math::cdf(v);

	EXPECT_EQ(0.5, ans.real());
	EXPECT_EQ(0,   ans.first(0));
	EXPECT_EQ(math::sqrt(2.0 * math::Pi<math::dual::RealType>::value),     ans.first(1));
	EXPECT_EQ(math::sqrt(2.0 * math::Pi<math::dual::RealType>::value) * 2, ans.first(2));
	EXPECT_EQ(0, ans.first(4));
}
