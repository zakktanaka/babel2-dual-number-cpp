#include <iostream>
#include <memory_resource>

int main() {

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