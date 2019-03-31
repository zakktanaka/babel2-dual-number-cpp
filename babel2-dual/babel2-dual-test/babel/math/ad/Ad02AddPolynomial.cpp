#include <pch.h>
#include <cmath>
#include <chrono>
#include <utility>
#include <vector>
#include <functional>

namespace {

	namespace math {
		size_t indexer = 0;

		struct Number {
			using Term = std::pair<double, Number>;
			using Polynomial = std::vector<Term>;

			size_t index;
			double v;
			Polynomial polynomial;

			Number() :index{ 0 }, v{ 0 }, polynomial{} {}
			Number(double vv) : index{ ++indexer }, v{ vv }, polynomial{}  {}
			Number(double vv, const Polynomial& pol) : index{ ++indexer }, v{ vv }, polynomial{ pol }  {}
			Number(double vv, Polynomial&& pol) : index{ ++indexer }, v{ vv }, polynomial{ pol }  {}
			
			//Number(const Number&) = default;
			//Number(Number&&) noexcept = default;
			//Number& operator=(const Number&) = default;
			//Number& operator=(Number&&) noexcept = default;

			double d(const Number& x) const {
				if (index == x.index) {
					return 1;
				}

				double dx = 0;
				for (auto& term : polynomial) {
					dx += term.first * term.second.d(x);
				}
				return dx;
			}


			Number operator-() const { return Number{ -v }; }
		};
		Number operator+(const Number& l, const Number& r) { return Number{ l.v + r.v }; }
		Number operator-(const Number& l, const Number& r) { return Number{ l.v - r.v }; }
		Number operator*(const Number& l, const Number& r) { return Number{ l.v * r.v }; }
		Number operator/(const Number& l, const Number& r) { return Number{ l.v / r.v }; }
		Number operator+(const Number& l, double r) { return Number{ l.v + r }; }
		Number operator-(const Number& l, double r) { return Number{ l.v - r }; }
		Number operator*(const Number& l, double r) { return Number{ l.v * r }; }
		Number operator/(const Number& l, double r) { return Number{ l.v / r }; }
		Number operator+(double l, const Number& r) { return Number{ l + r.v }; }
		Number operator-(double l, const Number& r) { return Number{ l - r.v }; }
		Number operator*(double l, const Number& r) { return Number{ l * r.v }; }
		Number operator/(double l, const Number& r) { return Number{ l / r.v }; }
		bool operator>(const Number& l, const Number& r) { return l.v > r.v; }
		Number exp(const Number& l) { return Number{ std::exp(l.v) }; }
		Number sqrt(const Number& l) { return Number{ std::sqrt(l.v) }; }
		Number pow(const Number& l, double r) { return Number{ std::pow(l.v, r) }; }

		using std::exp;
		using std::sqrt;
		using std::pow;
	}

	using Real = math::Number;

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

TEST(Ad02, Test) {

	auto f = []() {return putAmericanOption(100, 0.2, 100, 0.005, 3, 1000); };
	Timer t(f);

	EXPECT_DOUBLE_EQ(13.494113143178293, t.ans.v);

	// real = double 17 milli sec
	// real = simple struct 30 milli sec
	EXPECT_LE(50, t.duration());
	EXPECT_GT(60, t.duration());
}