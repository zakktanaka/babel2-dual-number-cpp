#include <pch.h>
#include <chrono>
#include <functional>
#include <vector>
#include <memory>

namespace {
	struct Hoge {
		double v;
		Hoge(int vv) : v(vv) {}
		~Hoge(){}
		double add(double x) { return x + v; }
	};

	template<typename T>
	struct Aggregation {
		Hoge h;
		T agg;

		Aggregation(Hoge hh, T ag) : h(hh), agg(ag) {}
		double aggregation(double x) { return h.add(agg.aggregation(x)); }
	};

	template<>
	struct Aggregation<void> {
		Hoge h;
		Aggregation(Hoge hh) : h(hh) {}
		double aggregation(double x) { return h.add(x); }
	};

	auto agg(int h) { return Aggregation<void>{Hoge(h)}; }
	template<typename T>
	auto agg(int h, T t) { return Aggregation<T>{Hoge(h), t}; }

	auto benchmark(const std::function<void()> &func)
	{
		auto start = std::chrono::high_resolution_clock::now();
		func();
		auto end = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	}
}

TEST(SandboxPtr, Performance) {
	const int loop = 10000;
	double ans = 0;

	auto stack = [loop, &ans]() {
		std::vector<Hoge> vs;
		for (int i = 0; i != loop; ++i) {
			vs.emplace_back(Hoge{ i });
		}

		for (auto& v : vs) {
			ans = v.add(ans);
		}
	};

	auto newdel = [loop, &ans]() {
		std::vector<Hoge*> vs;
		for (int i = 0; i != loop; ++i) {
			vs.emplace_back(new Hoge{ i });
		}

		for (auto& v : vs) {
			ans = v->add(ans);
		}

		for (auto& v : vs) {
			delete v;
		}
	};

	auto unique = [loop, &ans]() {
		std::vector<std::unique_ptr<Hoge>> vs;
		for (int i = 0; i != loop; ++i) {
			vs.emplace_back(std::make_unique<Hoge>(i));
		}

		for (auto& v : vs) {
			ans = v->add(ans);
		}
	};

	auto shared = [loop, &ans]() {
		std::vector<std::shared_ptr<Hoge>> vs;
		for (int i = 0; i != loop; ++i) {
			vs.emplace_back(std::make_shared<Hoge>(i));
		}

		for (auto& v : vs) {
			ans = v->add(ans);
		}
	};

	auto expected = loop * (loop - 1) / 2;
	{ ans = 0; EXPECT_EQ(0, benchmark(stack));  EXPECT_EQ(expected, ans); }
	{ ans = 0; EXPECT_EQ(0, benchmark(newdel)); EXPECT_EQ(expected, ans); }
	{ ans = 0; EXPECT_EQ(0, benchmark(unique)); EXPECT_EQ(expected, ans); }
	{ ans = 0; EXPECT_EQ(0, benchmark(shared)); EXPECT_EQ(expected, ans); }
}

TEST(SandboxPtr, Template) {
	Hoge h(0);
	auto a = agg(9, agg(8, agg(7, agg(6, agg(5, agg(4, agg(3, agg(2, agg(1, agg(0))))))))));
	auto x = a.aggregation(0);
}
