#include "American.hpp"
#include "Ad00.hpp"

#include <iostream>
#include "Timer.hpp"


void hiho::ad00(double s, double sigma, double k, double r, double t, int simulation)
{
	auto timer = hiho::newTimer(
		[&]() { return hiho::american(s, sigma, k, r, t, simulation); }
	);

	std::cout << "ad00 double val : " << timer.value << ", time : " << timer.duration() << " msec" 		<< ", delta : " << (hiho::american(s + 0.0001, sigma, k, r, t, simulation) - hiho::american(s - 0.0001, sigma, k, r, t, simulation)) / 0.0001 /2
		<< ", vega : " << (hiho::american(s, sigma + 0.0001, k, r, t, simulation) - hiho::american(s, sigma - 0.0001, k, r, t, simulation)) / 0.0001 / 2
		<< ", theta : " << (hiho::american(s, sigma, k, r, t + 0.0001, simulation) - hiho::american(s, sigma, k, r, t - 0.0001, simulation)) / 0.0001 / 2
		<< std::endl;
}
