#include <iostream>
#include <memory_resource>
#include "hiho/Ad.hpp"

int main() {

	hiho::ad00(100, 0.2, 100, 0.005, 3, 1000);

	std::cin.ignore();

	return 0;
}