#include <pch.h>
#include <cmath>
#include <chrono>
#include <functional>

namespace {

	namespace math {
		using std::exp;
		using std::sqrt;
		using std::pow;
	}

	using Real = double;

	inline Real putAmericanOption(const Real& s, const Real& sigma, const Real& k, const Real& r, const Real& t, int simulation) {

		auto dt = t / simulation;
		auto up = math::exp(sigma * math::sqrt(dt));

		auto p0 = (up - math::exp(-r * dt)) / (up * up - 1);
		auto p1 = math::exp(-r * dt) - p0;

		std::vector<Real> p;
		for (int i = 0; i != simulation; ++i) {
			auto pp = k - s * math::pow(up, 2.0 * i - simulation);
			pp = pp > 0.0 ? pp : 0.0;
			p.push_back(pp);
		}

		for (int j = simulation - 1; j != 0; --j) {
			for (int i = 0; i != j; ++i) {
				p[i] = p0 * p[i + 1] + p1 * p[i];    // binomial value
				auto exercise = k - s * math::pow(up, 2.0 * i - j);  // exercise value
				p[i] = p[i] > exercise ? p[i] : exercise;
			}
		}

		return p[0];
	}

	struct Timer {
		using Clock = std::chrono::system_clock;
		using TimePoint = std::chrono::time_point<Clock>;

		TimePoint start;
		TimePoint end;
		Real      ans;
		Timer(std::function<Real()> f) {
			start = Clock::now();
			ans = f();
			end = Clock::now();
		}

		long long duration() {
			return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		}
	};
}

TEST(Ad00, Test) {

	auto f = []() {return putAmericanOption(100, 0.2, 100, 0.005, 3, 1000); };
	Timer t(f);

	EXPECT_DOUBLE_EQ(13.494113143178293, t.ans);

	// real = double 17 milli sec
	// real = simple struct 30 milli sec
	EXPECT_LE(10, t.duration());
	EXPECT_GT(20, t.duration());
}