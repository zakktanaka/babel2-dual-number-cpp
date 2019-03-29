#include <pch.h>
#include <babel/math/ad/expression/Expression.hpp>
#include <babel/math/ad/expression/ExpressionPool.hpp>

using namespace babel::math::ad::expression;
using Pool = ExpressionPool<double>;
using E    = typename Pool::ExpressionType;

TEST(TestExpressionPool, Test) {
	Pool pool;
	auto a0 = pool.pool( E{ 10 });
	auto a1 = pool.pool(E{ 20, { { 2, *a0 } } });
	auto a2 = pool.pool(E{ 30, { { 3, *a0 }, { 4, *a1 } } });

	EXPECT_EQ(11, a2->differential(*a0));
}
