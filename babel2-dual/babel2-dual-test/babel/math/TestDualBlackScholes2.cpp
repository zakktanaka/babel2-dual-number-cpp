#include <pch.h>
#include <babel/math/math.hpp>

namespace math = babel::math;
using     Real = math::Dual<math::Dual<double>>;

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
		}
		else {
			return -s * math::cdf(-d1) + k * math::exp(-r * t) * math::cdf(-d2);
		}
	}
}

// http://www.math.drexel.edu/~pg/fin/VanillaCalculator.html
TEST(DualBlackSholes2, CallATM) {
	math::helper::DualHelper<Real> helper;

	Real k(100);
	auto s = helper.newDual("spot : delta", 100);
	auto sigma = helper.newDual("volatility : vega", 0.2);
	auto r = helper.newDual("interest rate : rho", 0.05);
	auto t = helper.newDual("maturity : theta", 3);

	auto ans = bs(s, sigma, k, r, t, CallPut::Call);

	EXPECT_NEAR(20.92437,  helper.getReal(ans), 1e-5);
	EXPECT_NEAR(0.72781,   helper.getFirst(ans, "spot : delta"),        1e-5);
	EXPECT_NEAR(57.50016,  helper.getFirst(ans, "volatility : vega"),   1e-5);
	EXPECT_NEAR(155.57138, helper.getFirst(ans, "interest rate : rho"), 1e-4);
	EXPECT_NEAR(4.50953,   helper.getFirst(ans, "maturity : theta"),    1e-5);
	EXPECT_NEAR(0.00958,   helper.getSecond(ans, "spot : delta"),       1e-5); //gamma
}
