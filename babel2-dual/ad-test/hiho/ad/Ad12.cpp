#include "Ad12.hpp"

#include <cmath>

#include <list>
#include <vector>
#include <utility>
#include <unordered_map>
#include <type_traits>

#include <limits>
#include <iomanip>
#include <iostream>

#include "American.hpp"
#include "Timer.hpp"

namespace {

	namespace math {

		using ValueType = double;
		using Cache = std::unordered_map<const void*, ValueType>;

		struct Expression {
			using Term = std::pair<ValueType, Expression*>;
			using Polynomial = std::vector<Term>;

			static std::list<Expression> expressions;

			static Expression* newExpression() {
				expressions.emplace_back(Expression{});
				return &*std::rbegin(expressions);
			}

			Polynomial polynomial;

			ValueType d(Expression* other, Cache& cache) const {
				if (this == other) { return 1; }

				const void*  x = &*this;
				auto it = cache.find(x);
				if (it != std::end(cache)) {
					return it->second;
				}

				ValueType dx = 0;
				for (auto& term : polynomial) {
					if (term.second != 0) {
						auto a = term.first;
						auto e = term.second;
						dx += a * e->d(other, cache);
					}
				}
				cache.emplace(x, dx);
				return dx;
			}
		};

		std::list<Expression> Expression::expressions = {};

		struct  INumber {
			using Term = typename Expression::Term;

			virtual ~INumber() {}
			virtual ValueType v() = 0;
			virtual bool next() = 0;
			virtual Term term() = 0;
		};

		struct Number : public INumber {
			using Polynomial = typename Expression::Polynomial;
			using Iterator = Polynomial::const_iterator;

			ValueType v_;
			Expression* expression;
			Iterator current;

			Number(ValueType vv) : v_(vv), expression(Expression::newExpression()) {
				expression->polynomial.emplace_back(1, expression);
				current = std::end(expression->polynomial);
			}

			ValueType v() override { return v_; }
			bool next() override { 
				if (current == std::end(expression->polynomial)) {
					current = std::begin(expression->polynomial);
				} else {
					++current;
				}
				return current != std::end(expression->polynomial); 
			}

			Term term() override { return *current; }
			//Number operator-() const { return Number{ -v, -1, *this }; }
		};
		Number operator+(INumber& l, INumber& r) { return Number{ l.v() + r.v(),  }; }
		//Number operator+(const Number& l, const Number& r) { return Number{ l.v + r.v, 1, l, 1, r, }; }
		//Number operator-(const Number& l, const Number& r) { return Number{ l.v - r.v, 1, l, -1, r, }; }
		//Number operator*(const Number& l, const Number& r) { return Number{ l.v * r.v, r.v, l, l.v, r, }; }
		//Number operator/(const Number& l, const Number& r) {
		//	auto ll = l.v;
		//	auto rr = r.v;
		//	return Number{ l.v / r.v, 1.0 / rr, l, -ll / (rr * rr), r, };
		//}
		//Number operator+(const Number& l, ValueType r) { return Number{ l.v + r, 1, l, }; }
		//Number operator-(const Number& l, ValueType r) { return Number{ l.v - r, 1, l, }; }
		//Number operator*(const Number& l, ValueType r) { return Number{ l.v * r, r, l, }; }
		//Number operator/(const Number& l, ValueType r) { return Number{ l.v / r, 1.0 / r, l, }; }
		//Number operator+(ValueType l, const Number& r) { return Number{ l + r.v, 1, r, }; }
		//Number operator-(ValueType l, const Number& r) { return Number{ l - r.v, -1, r, }; }
		//Number operator*(ValueType l, const Number& r) { return Number{ l * r.v, l, r, }; }
		//Number operator/(ValueType l, const Number& r) { return Number{ l / r.v, -l / (r.v * r.v), r, }; }
		//bool operator>(const Number& l, const Number& r) { return l.v > r.v; }
		//Number exp(const Number& l) {
		//	auto ll = std::exp(l.v);
		//	return Number{ ll, ll, l, };
		//}
		//Number sqrt(const Number& l) {
		//	auto ll = std::sqrt(l.v);
		//	return Number{ ll, ll, l, };
		//}
		//Number pow(const Number& l, ValueType r) {
		//	auto ll = std::pow(l.v, r);
		//	return Number{ ll, r * ll / l.v, l, };
		//}

		using std::exp;
		using std::sqrt;
		using std::pow;
	}

	using Real = math::Number;

	//inline Real putAmericanOption(const Real& s, const Real& sigma, const Real& k, const Real& r, const Real& t, int simulation) {

	//	auto dt = t / simulation;
	//	auto up = math::exp(sigma * math::sqrt(dt));

	//	auto p0 = (up - math::exp(-r * dt)) / (up * up - 1);
	//	auto p1 = math::exp(-r * dt) - p0;

	//	std::vector<Real> p;
	//	for (int i = 0; i != simulation; ++i) {
	//		auto pp = k - s * math::pow(up, 2.0 * i - simulation);
	//		pp = pp > 0.0 ? pp : 0.0;
	//		p.push_back(pp);
	//	}

	//	for (int j = simulation - 1; j != 0; --j) {
	//		for (int i = 0; i != j; ++i) {
	//			p[i] = p0 * p[i + 1] + p1 * p[i];    // binomial value
	//			auto exercise = k - s * math::pow(up, 2.0 * i - j);  // exercise value
	//			p[i] = p[i] > exercise ? p[i] : exercise;
	//		}
	//	}

	//	return p[0];
	//}

}

void hiho::ad12(double s, double sigma, double k, double r, double t, int simulation)
{
	//{
	//	Real ss{ s };
	//	auto timer = hiho::newTimer(
	//		[&]() { return putAmericanOption(ss, sigma, k, r, t, simulation); }
	//	);
	//	math::Expression::compressions();

	//	auto diff = timer.value.v - hiho::american(s, sigma, k, r, t, simulation);
	//	std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);
	//	std::cout << "ad11 diff : " << diff << ", time : " << timer.duration() << " msec, delta : " << timer.value.d(ss) << std::endl;
	//}

	Real ll{ 1.23 };
	Real rr{ 2.46 };

	auto lr = ll + rr;
		std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);
		std::cout << "ad11 diff : " << lr.v() << ", time : " << std::endl;
}
