#include <pch.h>
#include <babel/math/math.hpp>

TEST(SandboxMath, Pi) {
	EXPECT_NEAR(3.14159265358979000000, babel::math::pi<double>, 1e-14);
}

TEST(SandboxMath, E) {
	EXPECT_NEAR(2.71828182845905000000, babel::math::e<double>,  1e-14);
}

TEST(SandboxMath, Cmath) {
	EXPECT_NEAR(std::exp(1.23),  babel::math::exp(1.23),  1e-14);
	EXPECT_NEAR(std::log(1.23),  babel::math::log(1.23),  1e-14);
	EXPECT_NEAR(std::erf(1.23),  babel::math::erf(1.23),  1e-14);
	EXPECT_NEAR(std::sqrt(1.23), babel::math::sqrt(1.23), 1e-14);
}
