#pragma once

#include "constant.hpp"
#include "cmath.hpp"

namespace babel {
	namespace math {

		inline long double cdf(const long double& x) {
			const static auto p = long double(1) / sqrt(long double(2));
			return (long double(1) + erf(x * p)) / 2;
		}
		inline double cdf(const double& x) { return static_cast<double>(cdf(long double(x))); }
		inline float  cdf(const float&  x) { return static_cast<float> (cdf(long double(x))); }

		inline long double pdf(const long double& x) {
			const static auto p = long double(1) / sqrt(long double(2) * pi<long double>);
			return p * exp(- x * x / 2);
		}
		inline double pdf(const double& x) { return static_cast<double>(pdf(long double(x))); }
		inline float  pdf(const float&  x) { return static_cast<float> (pdf(long double(x))); }

		inline long double dpdf(const long double& x) {
			const static auto p = - long double(1) / sqrt(long double(2) * pi<long double>);
			return p * x * exp(-x * x / 2);
		}
		inline double dpdf(const double& x) { return static_cast<double>(dpdf(long double(x))); }
		inline float  dpdf(const float&  x) { return static_cast<float> (dpdf(long double(x))); }
	}
}