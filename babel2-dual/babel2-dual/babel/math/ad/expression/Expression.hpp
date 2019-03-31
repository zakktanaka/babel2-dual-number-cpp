#pragma once
#include <vector>
#include <utility>
#include "../../core/cmath.hpp"
#include "../../core/distribution.hpp"

namespace babel {
	namespace math {
		namespace ad {
			namespace expression {

				template<typename ValueType_>
				struct  Expression {
					using ValueType  = ValueType_;
					using ThisType   = Expression<ValueType>;
					using Term       = std::pair<ValueType, const ThisType&>;
					using Polynomial = std::vector<Term>;

					ValueType  x;
					Polynomial polynomial;

					Expression(const ThisType&) = default;
					Expression(ThisType&&)      = default;

					ThisType& operator=(const ThisType&)     = default;
					ThisType& operator=(ThisType&&) noexcept = default;

					ValueType differential(const ThisType& h) const {
						auto p = &h;
						if (p == this) {
							return 1;
						}

						ValueType d(0);
						for (auto& term : polynomial) {
							d += std::get<0>(term) * std::get<1>(term).differential(h);
						}
						return d;
					}
				};

				template<typename E>
				inline E add(const E& lhs, const E& rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs.x + rhs.x, { {ValueType(1), lhs}, {ValueType(1), rhs} } };
				}
				template<typename E>
				inline E add(typename E::ValueType lhs, const E& rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs + rhs.x, { {ValueType(1), rhs} } };
				}
				template<typename E>
				inline E add(const E& lhs, typename E::ValueType rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs.x + rhs, { {ValueType(1), lhs} } };
				}

				template <typename E>
				inline E subtract(const E& lhs, const E& rhs) {
					using ValueType = typename E::ValueType;
					return E{lhs.x - rhs.x, {{ValueType(1), lhs}, {ValueType(-1), rhs}}};
				}
				template<typename E>
				inline E subtract(typename E::ValueType lhs, const E& rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs - rhs.x, { {ValueType(-1), rhs} } };
				}
				template<typename E>
				inline E subtract(const E& lhs, typename E::ValueType rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs.x - rhs, { {ValueType(1), lhs} } };
				}

				template<typename E>
				inline E times(const E& lhs, const E& rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs.x * rhs.x, { {rhs.x, lhs}, {lhs.x, rhs} } };
				}
				template<typename E>
				inline E times(typename E::ValueType lhs, const E& rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs * rhs.x, { {lhs, rhs} } };
				}
				template<typename E>
				inline E times(const E& lhs, typename E::ValueType rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs.x * rhs, { {rhs, lhs} } };
				}

				template<typename E>
				inline E divide(const E& lhs, const E& rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs.x / rhs.x, { {ValueType(1) / rhs.x, lhs}, {ValueType(-1) * lhs.x / (rhs.x * rhs.x), rhs} } };
				}
				template<typename E>
				inline E divide(typename E::ValueType lhs, const E& rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs / rhs.x, { {-lhs / (rhs.x * rhs.x), rhs} } };
				}
				template<typename E>
				inline E divide(const E& lhs, typename E::ValueType rhs) {
					using ValueType = typename E::ValueType;
					return E{ lhs.x / rhs, { { ValueType(1) / rhs, lhs} } };
				}

				template<typename ValueType_>
				inline Expression<ValueType_> exp(const Expression<ValueType_>& x) {
					using VT = ValueType_;
					using Ex = Expression<VT>;
					namespace math = babel::math;
					return Ex{ math::exp(x.x), {{math::exp(x.x), x}} };
				}

				template<typename ValueType_>
				inline Expression<ValueType_> log(const Expression<ValueType_>& x) {
					using VT = ValueType_;
					using Ex = Expression<VT>;
					namespace math = babel::math;
					return Ex{ math::log(x.x), { { VT(1) / x.x, x} } };
				}

				template<typename ValueType_>
				inline Expression<ValueType_> sqrt(const Expression<ValueType_>& x) {
					using VT = ValueType_;
					using Ex = Expression<VT>;
					namespace math = babel::math;
					return Ex{ math::sqrt(x.x), { { VT(0.5) / math::sqrt(x.x), x} } };
				}

				template<typename E>
				inline E pow(const E& lhs, const E& rhs) {
					using ValueType = typename E::ValueType;
					namespace math = babel::math;
					auto x = lhs.x;
					auto y = rhs.x;
					auto a = math::pow(x, y);
					return E{ a, { { a * y / x, lhs}, {a * math::log(x), rhs} } };
				}
				template<typename E>
				inline E pow(typename E::ValueType lhs, const E& rhs) {
					using ValueType = typename E::ValueType;
					namespace math = babel::math;
					auto x = lhs;
					auto y = rhs.x;
					auto a = math::pow(x, y);
					return E{ a, { {a * math::log(x), rhs} } };
				}
				template<typename E>
				inline E pow(const E& lhs, typename E::ValueType rhs) {
					using ValueType = typename E::ValueType;
					namespace math = babel::math;
					auto x = lhs.x;
					auto y = rhs;
					auto a = math::pow(x, y);
					return E{ a, { { a * y / x, lhs} } };
				}

				template<typename ValueType_>
				inline Expression<ValueType_> cdf(const Expression<ValueType_>& x) {
					using VT = ValueType_;
					using Ex = Expression<VT>;
					namespace math = babel::math;
					return Ex{ math::cdf(x.x), { { math::pdf(x.x), x} } };
				}

				template<typename ValueType_>
				inline Expression<ValueType_> pdf(const Expression<ValueType_>& x) {
					using VT = ValueType_;
					using Ex = Expression<VT>;
					namespace math = babel::math;
					return Ex{ math::pdf(x.x), { { math::dpdf(x.x), x} } };
				}

			}
		}
	}
}