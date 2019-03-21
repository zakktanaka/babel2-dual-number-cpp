#pragma once

#include <babel/math/math.hpp>
#include <vector>

namespace hiho {
	using Real = double; //babel::math::Dual<double>;

	inline Real putAmericanOption(const Real& s, const Real& sigma, const Real& k, const Real& r, const Real& t, int simulation) {
		namespace math = babel::math;
		
		auto dt = t / simulation;
		auto up = math::exp(sigma * math::sqrt(dt));

		auto p0 = (up - math::exp(-r * dt)) / (up * up - 1);
		auto p1 = math::exp(-r * dt) - p0;

		std::vector<Real> p;
		for (int i = 0; i != simulation; ++i) {
			auto pp = k - s * math::pow(up, Real(2 * i - simulation));
			pp = pp > 0 ? pp : 0;
			p.push_back(pp);
		}

		for (int j = simulation-1; j != 0; --j) {
			for (int i = 0; i != j; ++i) {
				p[i] = p0 * p[i + 1] + p1 * p[i];    // binomial value
				auto exercise = k - s * math::pow( up, Real(2 * i - j));  // exercise value
				p[i] = p[i] > exercise ? p[i] : exercise;
			}
		}

		return p[0];
	}
}