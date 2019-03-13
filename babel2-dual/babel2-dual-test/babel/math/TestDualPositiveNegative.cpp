#include <pch.h>
#include <babel/math/dual.hpp>

TEST(DualPositiveNegative, Positive) {
	using namespace babel::math;

	Dual v0(123, { 0,1,1 });
	auto ans = +v0;

	EXPECT_EQ(v0.real(),   ans.real()  );
	EXPECT_EQ(v0.first(0), ans.first(0));
	EXPECT_EQ(v0.first(1), ans.first(1));
	EXPECT_EQ(v0.first(2), ans.first(2));
	EXPECT_EQ(v0.first(3), ans.first(3));
}

TEST(DualPositiveNegative, Positive1) {
	using namespace babel::math;

	Dual v0(-123, { 0,1,-1 });
	auto ans = +v0;

	EXPECT_EQ(v0.real(),   ans.real()  );
	EXPECT_EQ(v0.first(0), ans.first(0));
	EXPECT_EQ(v0.first(1), ans.first(1));
	EXPECT_EQ(v0.first(2), ans.first(2));
	EXPECT_EQ(v0.first(3), ans.first(3));
}

TEST(DualPositiveNegative, Negative) {
	using namespace babel::math;

	Dual v0(123, { 0,1,1 });
	auto ans = -v0;

	EXPECT_EQ(-v0.real(),   ans.real()  );
	EXPECT_EQ(-v0.first(0), ans.first(0));
	EXPECT_EQ(-v0.first(1), ans.first(1));
	EXPECT_EQ(-v0.first(2), ans.first(2));
	EXPECT_EQ(-v0.first(3), ans.first(3));
}

TEST(DualPositiveNegative, Negative1) {
	using namespace babel::math;

	Dual v0(-123, { 0,1,-1 });
	auto ans = -v0;

	EXPECT_EQ(-v0.real(),   ans.real()  );
	EXPECT_EQ(-v0.first(0), ans.first(0));
	EXPECT_EQ(-v0.first(1), ans.first(1));
	EXPECT_EQ(-v0.first(2), ans.first(2));
	EXPECT_EQ(-v0.first(3), ans.first(3));
}
