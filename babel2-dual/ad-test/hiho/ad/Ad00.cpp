#include "American.hpp"
#include "Ad00.hpp"

#include <iostream>
#include "Timer.hpp"


void hiho::ad00(double s, double sigma, double k, double r, double t, int simulation)
{
	auto timer = hiho::newTimer(
		[&]() { return hiho::american(s, sigma, k, r, t, simulation); }
	);

	std::cout << "ad00 double val : " << timer.value << ", time : " << timer.duration() << " msec" << std::endl;
}
