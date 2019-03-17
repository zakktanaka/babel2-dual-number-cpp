#include <pch.h>
#include <babel/math/math.hpp>

namespace math = babel::math;
using Dual_ = math::Dual<double>;
using DDual = math::Dual<math::Dual<double>>;

TEST(DDual, Test) {
	DDual a{ Dual_{2, {1}}, {Dual_{1}} };

	{
		auto ans = math::log(a);
		EXPECT_EQ(math::log(2.0), ans.real().real());
		EXPECT_EQ(1.0 / 2, ans.first(0).real());
		EXPECT_EQ(-1.0 / 4, ans.first(0).first(0));
	}
}
