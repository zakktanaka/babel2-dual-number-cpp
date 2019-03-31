#include <pch.h>
#include <babel/math/ad/Dual.hpp>

namespace math = babel::math::ad;
using     Real = math::Dual<double>;

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
TEST(TestAdDualBlackSholes, CallATM) {
	math::AdCalculationContext<double> context;

	Real k(100);
	Real s(100);
	Real sigma(0.2);
	Real r(0.05);
	Real t(3);

	auto ans = bs(s, sigma, k, r, t, CallPut::Call);

	EXPECT_NEAR(20.92437,  ans.x(), 1e-5);
	EXPECT_NEAR(0.72781,   ans.differential(s),    1e-5);
	EXPECT_NEAR(57.50016, ans.differential(sigma), 1e-5);
	EXPECT_NEAR(155.57138, ans.differential(r),    1e-4);
	EXPECT_NEAR(4.50953, ans.differential(t),      1e-5);
	//EXPECT_NEAR(0.00958,   helper.getSecond(ans, "spot : delta"),       1e-5); //gamma
}
