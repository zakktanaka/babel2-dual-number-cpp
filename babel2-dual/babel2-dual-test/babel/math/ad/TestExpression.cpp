#include <pch.h>
#include <babel/math/ad/Expression.hpp>

using namespace babel::math::ad::expression;
using Generator  = ExpressionGenerator<double>;

TEST(TestExpression, Test) {
	Generator gen;

	auto a0 = gen(10);
	auto a1 = gen(20, { { 2, a0 } } );
	auto a2 = gen(30, { { 3, a0 }, { 4, a1 } } );

	EXPECT_EQ(11, a2->differential(a0));
}

TEST(TestExpression, Add) {
	Generator gen;

	auto x = gen(10);
	auto y = gen(20);

	auto a0 = add(x, 5.0, gen);
	EXPECT_EQ(10 + 5, a0->x);
	EXPECT_EQ(1, a0->differential(x));
	EXPECT_EQ(0, a0->differential(y));

	auto a1 = add(3.0, y, gen);
	EXPECT_EQ(3 + 20, a1->x);
	EXPECT_EQ(0, a1->differential(x));
	EXPECT_EQ(1, a1->differential(y));

	auto a2 = add(x, y, gen);
	EXPECT_EQ(10 + 20, a2->x);
	EXPECT_EQ(1, a2->differential(x));
	EXPECT_EQ(1, a2->differential(y));
}

TEST(TestExpression, Subtract) {
	Generator gen;

	auto x = gen(10);
	auto y = gen(20);

	auto a0 = subtract(x, 5.0, gen);
	EXPECT_EQ(10 - 5, a0->x);
	EXPECT_EQ(1, a0->differential(x));
	EXPECT_EQ(0, a0->differential(y));

	auto a1 = subtract(3.0, y, gen);
	EXPECT_EQ(3 - 20, a1->x);
	EXPECT_EQ(0, a1->differential(x));
	EXPECT_EQ(-1, a1->differential(y));

	auto a2 = subtract(x, y, gen);
	EXPECT_EQ(10 - 20, a2->x);
	EXPECT_EQ(1, a2->differential(x));
	EXPECT_EQ(-1, a2->differential(y));
}

TEST(TestExpression, Times) {
	Generator gen;

	auto x = gen(10);
	auto y = gen(20);

	auto a0 = times(x, 5.0, gen);
	EXPECT_EQ(10 * 5, a0->x);
	EXPECT_EQ(5, a0->differential(x));
	EXPECT_EQ(0, a0->differential(y));

	auto a1 = times(3.0, y, gen);
	EXPECT_EQ(3 * 20, a1->x);
	EXPECT_EQ(0, a1->differential(x));
	EXPECT_EQ(3, a1->differential(y));

	auto a2 = times(x, y, gen);
	EXPECT_EQ(10 * 20, a2->x);
	EXPECT_EQ(20, a2->differential(x));
	EXPECT_EQ(10, a2->differential(y));
}

TEST(TestExpression, Divide) {
	Generator gen;

	auto x = gen(10);
	auto y = gen(20);

	auto a0 = divide(x, 5.0, gen);
	EXPECT_EQ(10.0 / 5, a0->x);
	EXPECT_EQ(1.0 / 5, a0->differential(x));
	EXPECT_EQ(0, a0->differential(y));

	auto a1 = divide(3.0, y, gen);
	EXPECT_EQ(3.0 / 20, a1->x);
	EXPECT_EQ(0, a1->differential(x));
	EXPECT_EQ(-1.0/400, a1->differential(y));

	auto a2 = divide(x, y, gen);
	EXPECT_EQ(10.0 / 20, a2->x);
	EXPECT_EQ(1.0 / 20, a2->differential(x));
	EXPECT_EQ(-10.0 / 400, a2->differential(y));
}
