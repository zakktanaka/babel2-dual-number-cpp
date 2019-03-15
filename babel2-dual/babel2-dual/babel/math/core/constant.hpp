#pragma once

#define BABEL_MATH_DEFINE_CONST(name, val) \
template<typename T> struct name { };                                              \
template<> struct name<long double> { static constexpr long double value = val; }; \
template<> struct name     <double> { static constexpr      double value = static_cast<double>(name<long double>::value); }; \
template<> struct name     <float>  { static constexpr      float  value = static_cast<float> (name<long double>::value); }

namespace babel {
	namespace math {

		BABEL_MATH_DEFINE_CONST(Pi, 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679);

		BABEL_MATH_DEFINE_CONST(E, 2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274);

	}
}

#undef BABEL_MATH_DEFINE_CONST