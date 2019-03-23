#include <pch.h>
#include <memory>
#include <vector>
#include <functional>

namespace {
	struct Base {
		virtual double x() = 0;
	};

	struct Const : public Base {
		double x_;
		Const(double x) : x_(x) {}
		double x() override { return x_; }
	};

	struct V0 {
		std::shared_ptr<Base> v_;
		V0(const double& v) : v_(std::make_shared<Const>(v)) {}
	};

	struct V1 {
		std::function<Base*()> v_;
		V1(Const v) : v_([v](){return (Base*)&v; }) {}
	};


	int loop = 10000;
}

TEST(SandboxPerformance, Double) {
	std::vector<double> vs;
	for (int i = 0; i < loop; ++i) {
		vs.emplace_back(i);
	}

	double x = 0;
	for (auto& v : vs) {
		x += v;
	}
	EXPECT_EQ(loop * (loop - 1) / 2, x);
}

TEST(SandboxPerformance, SharedPtr) {
	std::vector<V0> vs;
	for (int i = 0; i < loop; ++i) {
		vs.emplace_back(V0(i));
	}

	double x = 0;
	for (auto& v : vs) {
		x += v.v_->x();
	}
	EXPECT_EQ(loop * (loop - 1) / 2, x);
}

TEST(SandboxPerformance, Lambda) {
	std::vector<V1> vs;
	for (int i = 0; i < loop; ++i) {
		vs.emplace_back(V1(i));
	}

	double x = 0;
	for (auto& v : vs) {
		x += v.v_()->x();
	}
	EXPECT_EQ(loop * (loop - 1) / 2, x);
}

TEST(SandboxPerformance, Const) {
	std::vector<Const> vs;
	for (int i = 0; i < loop; ++i) {
		vs.emplace_back(i);
	}

	double x = 0;
	for (auto& v : vs) {
		x += v.x();
	}
	EXPECT_EQ(loop * (loop - 1) / 2, x);
}
