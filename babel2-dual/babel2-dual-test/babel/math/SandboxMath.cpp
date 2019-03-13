#include <pch.h>
#include <babel/math/math.hpp>

TEST(SandboxMath, Pi) {
	EXPECT_NEAR(3.14159265358979000000, babel::math::pi, 1e-14);
}

TEST(SandboxMath, E) {
	EXPECT_NEAR(2.71828182845905000000, babel::math::e, 1e-14);
}
