#include <pch.h>
#include <cmath>
#include <chrono>
#include <utility>
#include <array>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>
#include <unordered_map>

namespace {
	namespace math {

		using ValueType = double;
		using Cache = std::unordered_map<const void*, ValueType>;

		struct Expression {
			using Term = std::pair<ValueType, Expression*>;
			using Polynomial = std::vector<Term>;

			static std::list<Expression> expressions;

			static Expression* newExpression() {
				static Expression e{ 0, {} };
				return &e;
			}
			static Expression* newExpression(const Polynomial& pol) {
				expressions.emplace_back(Expression{ 0, pol });
				return &*std::rbegin(expressions);
			}
			static Expression* newExpression(Polynomial&& pol) {
				expressions.emplace_back(Expression{ 0, pol });
				return &*std::rbegin(expressions);
			}

			static void compressions() {
				for (auto& ex : expressions) {
					ex.polynomial = ex.compression();
				}
			}

			size_t reference;
			Polynomial polynomial;

			void ref() { ++reference; }
			void dref() { --reference; }

			Polynomial compression() {
				Polynomial ps;
				for (auto& term : polynomial) {
					auto a = term.first;
					auto e = term.second;

					if (e->reference != 0) {
						auto it = std::find_if(std::begin(ps), std::end(ps), [e](const Term& t) {return t.second == e; });
						if (it == std::end(ps)) {
							ps.emplace_back(term);
						} else {
							it->first += a;
						}
					} else {
						for (auto& tt : e->polynomial) {
							auto aa = tt.first;
							auto ee = tt.second;

							auto it = std::find_if(std::begin(ps), std::end(ps), [ee](const Term& t) {return t.second == ee; });
							if (it == std::end(ps)) {
								ps.emplace_back(a * aa, e);
							} else {
								it->first += a * aa;
							}
						}
					}

				}
				return std::move(ps);
			}
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

		std::list<Expression> Expression::expressions = { };

		struct Number {
			using Polynomial = Expression::Polynomial;

			Expression* eindex;
			ValueType v;

			Number(ValueType vv) :eindex(Expression::newExpression(Polynomial{})), v{ vv } { eindex->ref(); }
			Number(ValueType vv, ValueType a0, const Number& x0) :
				eindex(Expression::newExpression(Polynomial{ { {a0,x0.eindex} } })), v{ vv } { eindex->ref(); }
			Number(ValueType vv, ValueType a0, const Number& x0, ValueType a1, const Number& x1) :
				eindex(Expression::newExpression(Polynomial{ { {a0,x0.eindex}, {a1,x1.eindex} } })), v{ vv } { eindex->ref(); }
			Number(const Number& other) :eindex(other.eindex), v{other.v} { eindex->ref(); }
			Number& operator=(const Number& other) {
				eindex->dref();
				eindex = other.eindex;
				v = other.v;
				eindex->ref();
				return *this;
			}
			~Number() {  eindex->dref(); }
			ValueType d(const Number& dx) const { Cache cache; return eindex->d(dx.eindex, cache); }
			Number operator-() const { return Number{ -v, -1, *this }; }
		};
		Number operator+(const Number& l, const Number& r) { return Number{ l.v + r.v, 1, l, 1, r, }; }
		Number operator-(const Number& l, const Number& r) { return Number{ l.v - r.v, 1, l, -1, r, }; }
		Number operator*(const Number& l, const Number& r) { return Number{ l.v * r.v, r.v, l, l.v, r, }; }
		Number operator/(const Number& l, const Number& r) {
			auto ll = l.v;
			auto rr = r.v;
			return Number{ l.v / r.v, 1.0 / rr, l, -ll / (rr * rr), r, };
		}
		Number operator+(const Number& l, ValueType r) { return Number{ l.v + r, 1, l, }; }
		Number operator-(const Number& l, ValueType r) { return Number{ l.v - r, 1, l, }; }
		Number operator*(const Number& l, ValueType r) { return Number{ l.v * r, r, l, }; }
		Number operator/(const Number& l, ValueType r) { return Number{ l.v / r, 1.0 / r, l, }; }
		Number operator+(ValueType l, const Number& r) { return Number{ l + r.v, 1, r, }; }
		Number operator-(ValueType l, const Number& r) { return Number{ l - r.v, -1, r, }; }
		Number operator*(ValueType l, const Number& r) { return Number{ l * r.v, l, r, }; }
		Number operator/(ValueType l, const Number& r) { return Number{ l / r.v, -l / (r.v * r.v), r, }; }
		bool operator>(const Number& l, const Number& r) { return l.v > r.v; }
		Number exp(const Number& l) {
			auto ll = std::exp(l.v);
			return Number{ ll, ll, l, };
		}
		Number sqrt(const Number& l) {
			auto ll = std::sqrt(l.v);
			return Number{ ll, ll, l, };
		}
		Number pow(const Number& l, ValueType r) {
			auto ll = std::pow(l.v, r);
			return Number{ ll, r * ll / l.v, l, };
		}

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

		TimePoint end;
		TimePoint start;
		Real      ans;
		Timer(std::function<Real()> f) : end(), start(Clock::now()), ans(f()) {
			end = Clock::now();
		}

		long long duration() {
			return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		}
	};
}

TEST(Ad09, Test) {

	Real s(100);
	auto f = [&s]() {return putAmericanOption(s, 0.2, 100, 0.005, 3, 1000); };
	Timer t(f);

	EXPECT_DOUBLE_EQ(13.494113143178293, t.ans.v);

	// real = double 17 milli sec
	// real = simple struct 30 milli sec
	EXPECT_LE(440, t.duration());
	EXPECT_GT(480, t.duration());

	size_t count = 0;
	for (auto& e : math::Expression::expressions) {
		if (e.reference != 0) { ++count; }
	}
	EXPECT_EQ(2, count);
	EXPECT_EQ(3001520, math::Expression::expressions.size());
	//math::Expression::compressions();

	EXPECT_DOUBLE_EQ(13.494113143178293, t.ans.eindex->polynomial[0].first);

	EXPECT_DOUBLE_EQ(-0.42779717603899964, t.ans.d(s));
}
