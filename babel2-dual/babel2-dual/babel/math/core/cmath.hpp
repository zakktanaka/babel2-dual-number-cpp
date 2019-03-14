#pragma once

#include <cmath>

#define BABELDEFINE_STD_MATH_UNARY_FUNC(func) \
	inline long double func(const long double& x) noexcept { return std::func(x); } \
	inline      double func(const      double& x) noexcept { return std::func(x); } \
	inline      float  func(const      float & x) noexcept { return std::func(x); }

namespace babel {
	namespace math {

		BABELDEFINE_STD_MATH_UNARY_FUNC(exp)
		BABELDEFINE_STD_MATH_UNARY_FUNC(log)
		BABELDEFINE_STD_MATH_UNARY_FUNC(erf)
		BABELDEFINE_STD_MATH_UNARY_FUNC(sqrt)

	}
}

#undef BABELDEFINE_STD_MATH_UNARY_FUNC