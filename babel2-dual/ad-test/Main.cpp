#include <iostream>
#include "hiho/Ad.hpp"

int main() {

	hiho::ad00(100, 0.2, 100, 0.005, 3, 1000);
	hiho::ad01(100, 0.2, 100, 0.005, 3, 1000);
	hiho::ad02(100, 0.2, 100, 0.005, 3, 1000);
	hiho::ad03(100, 0.2, 100, 0.005, 3, 10);

	std::cin.ignore();

	return 0;
}