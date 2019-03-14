#pragma once

#include <cmath>

#define BABELDEFINE_STD_MATH_UNARY_FUNC(func) \
	inline long double func(const long double& x) noexcept { return std::func(x); } \
	inline      double func(const      double& x) noexcept { return std::func(x); } \
	inline      float  func(const      float & x) noexcept { return std::func(x); }

#define BABELDEFINE_STD_MATH_BINARY_FUNC(func) \
	inline long double func(const long double& x, const long double& y) noexcept { return std::func(x, y); } \
	inline      double func(const      double& x, const      double& y) noexcept { return std::func(x, y); } \
	inline      float  func(const      float & x, const      float & y) noexcept { return std::func(x, y); }


namespace babel {
	namespace math {

		BABELDEFINE_STD_MATH_UNARY_FUNC(exp)
		BABELDEFINE_STD_MATH_UNARY_FUNC(log)
		BABELDEFINE_STD_MATH_UNARY_FUNC(erf)
		BABELDEFINE_STD_MATH_UNARY_FUNC(sqrt)

		BABELDEFINE_STD_MATH_BINARY_FUNC(pow)
	}
}

#undef BABELDEFINE_STD_MATH_UNARY_FUNC
#undef BABELDEFINE_STD_MATH_BINARY_FUNC