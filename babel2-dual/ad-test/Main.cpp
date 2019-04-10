#include <iostream>
#include <memory_resource>
#include "hiho/Timer.hpp"

int main() {

	auto timer = hiho::newTimer([]() {return 100; });

	std::cout << timer.value << std::endl;
	std::cout << timer.duration() << std::endl;

	std::pmr::synchronized_pool_resource mem_res;

	std::pmr::list<int> v(&mem_res);

	for (int i = 0; i < 100000; ++i) {
		v.emplace_back(i);
	}

	auto it = std::begin(v);
	while (it != std::end(v)) {
		it = v.erase(it);
	}

	std::cin.ignore();

	return 0;
}