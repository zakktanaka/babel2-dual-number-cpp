#include <pch.h>
#include <babel/math/ad/Expression.hpp>

using Generator  = babel::math::ad::expression::ExpressionGenerator<double>;

TEST(TestExpression, Test) {
	Generator gen;

	auto a0 = gen.generate(10);
	auto a1 = gen.generate(20, { { 2, a0 } } );
	auto a2 = gen.generate(30, { { 3, a0 }, { 4, a1 } } );

	EXPECT_EQ(11, a2->differential(a0));
}