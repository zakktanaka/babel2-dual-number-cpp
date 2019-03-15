#include <pch.h>
#include <babel/math/math.hpp>

namespace math = babel::math;
using Real = math::Dual;

namespace {

	enum class CallPut { Call, Put };
	
	Real d1_(const Real& s, const Real& sigma, const Real& k, const Real& r, const Real& t) {
		auto a = math::log(s / k) + (r + sigma * sigma / 2) * t;
		auto b = sigma * math::sqrt(t);
		return a / b;
	}

	Real bs(const Real& s, const Real& sigma, const Real& k, const Real& r, const Real& t, CallPut cp) {
		auto d1 = d1_(s, sigma, k, r, t);
		auto d2 = d1 - sigma * math::sqrt(t);
		if (cp == CallPut::Call) {
			return s * math::cdf(d1) - k * math::exp(-r * t) * math::cdf(d2);
		} else {
			return -s * math::cdf(-d1) + k * math::exp(-r * t) * math::cdf(-d2);
		}
	}
}

// http://www.math.drexel.edu/~pg/fin/VanillaCalculator.html
TEST(DualBlackSholes, CallATM) {
	math::helper::DualHelper<Real> helper;

	Real k(100);
	auto s     = helper.newDual("spot : delta",        100);
	auto sigma = helper.newDual("volatility : vega",   0.2);
	auto r     = helper.newDual("interest rate : rho", 0.05);
	auto t     = helper.newDual("maturity : theta",    3);

	auto ans = bs(s, sigma, k, r, t, CallPut::Call);

	EXPECT_NEAR(20.92437,  ans.real(),   1e-5);
	EXPECT_NEAR(0.72781,   helper.getFirst(ans, "spot : delta"),        1e-5);
	EXPECT_NEAR(57.50016,  helper.getFirst(ans, "volatility : vega"),   1e-5);
	EXPECT_NEAR(155.57138, helper.getFirst(ans, "interest rate : rho"), 1e-4);
	EXPECT_NEAR(4.50953,   helper.getFirst(ans, "maturity : theta"),    1e-5);
	// gamma 0.00958
}

TEST(DualBlackSholes, CallITM) {
	Real k(120);
	Real s    (100,  {1});
	Real sigma(0.2,  {0,1});
	Real r    (0.05, { 0,0,1 });
	Real t    (3,    { 0,0,0,1 });

	auto ans = bs(s, sigma, k, r, t, CallPut::Call);

	EXPECT_NEAR(12.39454,  ans.real(),   1e-5);
	EXPECT_NEAR(0.53184,   ans.first(0), 1e-5);
	EXPECT_NEAR(68.87861,  ans.first(1), 1e-5);
	EXPECT_NEAR(122.36898, ans.first(2), 1e-4);
	EXPECT_NEAR(4.33544,   ans.first(3), 1e-5);
	// gamma 0.01148
}

TEST(DualBlackSholes, PutATM) {
	Real k(100);
	Real s    (100,  {1});
	Real sigma(0.2,  {0,1});
	Real r    (0.05, { 0,0,1 });
	Real t    (3,    { 0,0,0,1 });

	auto ans = bs(s, sigma, k, r, t, CallPut::Put);

	EXPECT_NEAR(6.99517,    ans.real(),   1e-4);
	EXPECT_NEAR(-0.27219,   ans.first(0), 1e-5);
	EXPECT_NEAR(57.50016,   ans.first(1), 1e-5);
	EXPECT_NEAR(-102.64101, ans.first(2), 1e-4);
	EXPECT_NEAR(0.20599,    ans.first(3), 1e-5);
	// gamma 0.00958
}

TEST(DualBlackSholes, PutITM) {
	Real k(120);
	Real s    (100,  {1});
	Real sigma(0.2,  {0,1});
	Real r    (0.05, { 0,0,1 });
	Real t    (3,    { 0,0,0,1 });

	auto ans = bs(s, sigma, k, r, t, CallPut::Put);

	EXPECT_NEAR(15.67950,   ans.real(),   1e-5);
	EXPECT_NEAR(-0.46816,   ans.first(0), 1e-5);
	EXPECT_NEAR(68.87861,   ans.first(1), 1e-5);
	EXPECT_NEAR(-187.48589, ans.first(2), 1e-4);
	EXPECT_NEAR(-0.82881,   ans.first(3), 1e-5);
	// gamma 0.01148
}
