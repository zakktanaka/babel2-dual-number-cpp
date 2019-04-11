#include "Ad.hpp"

#include <cmath>
#include <vector>

#include <utility>
#include <iostream>
#include <iomanip>
#include <limits>
#include "Timer.hpp"

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


			Number operator-() const {
				Polynomial pol;
				for (auto& term : pol) {
					pol.emplace_back(-term.first, term.second);
				}

				return Number{ -v, std::move(pol) };
			}
		};
		Number operator+(const Number& l, const Number& r) { return Number{ l.v + r.v, {{1, l}, {1, r}} }; }
		Number operator-(const Number& l, const Number& r) { return Number{ l.v - r.v, {{1, l}, {-1, r}} }; }
		Number operator*(const Number& l, const Number& r) { return Number{ l.v * r.v, {{r.v, l}, {l.v, r}} }; }
		Number operator/(const Number& l, const Number& r) {
			auto ll = l.v;
			auto rr = r.v;
			return Number{ l.v / r.v, {{1.0 / rr, l}, {-ll / (rr * rr), r}} };
		}
		Number operator+(const Number& l, double r) { return Number{ l.v + r, {{1, l}} }; }
		Number operator-(const Number& l, double r) { return Number{ l.v - r, {{1, l}} }; }
		Number operator*(const Number& l, double r) { return Number{ l.v * r, {{r, l}} }; }
		Number operator/(const Number& l, double r) { return Number{ l.v / r, {{1.0 / r, l}} }; }
		Number operator+(double l, const Number& r) { return Number{ l + r.v, {{1, r}} }; }
		Number operator-(double l, const Number& r) { return Number{ l - r.v, {{-1, r}} }; }
		Number operator*(double l, const Number& r) { return Number{ l * r.v, {{l, r}} }; }
		Number operator/(double l, const Number& r) { return Number{ l / r.v, {{ -l / (r.v * r.v), r}} }; }
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
}

void hiho::ad08(double s, double sigma, double k, double r, double t, int simulation)
{
	auto timer = hiho::newTimer(
		[&]() { return putAmericanOption(s, sigma, k, r, t, simulation); }
	);

	auto diff = timer.value.v - hiho::american(s, sigma, k, r, t, simulation);
	std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);
	std::cout << "ad08 diff : " << diff << ", time : " << timer.duration() << " msec" << std::endl;
}
