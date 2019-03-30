#pragma once

#include <cassert>
#include "AdCalculationContext.hpp"

#define BABEL_AD_DEFINE_DUAL_UNARY_ARITHMETIC(op, func) \
	ThisType& operator op(const ThisType& rhs) {               \
		pooled_ = epool()->pool(func(*pooled_, *rhs.pooled_)); \
		return (*this);                                        \
	}                                                          \
	ThisType& operator op(ValueType rhs) {                     \
		pooled_ = epool()->pool(func(*pooled_, rhs));          \
		return (*this);                                        \
	}

#define BABEL_AD_DEFINE_DUAL_BINARY_ARITHMETIC(op, func) \
	template<typename DUAL>                                                  \
	inline DUAL operator op(const DUAL& lhs, const DUAL& rhs) {              \
		return DUAL(func(lhs.expression(), rhs.expression()));               \
	}                                                                        \
	template<typename DUAL>                                                  \
	inline DUAL operator op(const DUAL& lhs, typename DUAL::ValueType rhs) { \
		return DUAL(func(lhs.expression(), rhs));                            \
	}                                                                        \
	template<typename DUAL>                                                  \
	inline DUAL operator op(typename DUAL::ValueType lhs, const DUAL& rhs) { \
		return DUAL(func(lhs, rhs.expression()));                            \
	}

namespace babel {
	namespace math {
		namespace ad {

			template<typename ValueType_>
			class Dual {
			public:
				using ValueType  = double; // ValueType_;
				using ThisType   = Dual<ValueType>;
				using AdContext  = AdCalculationContext<ValueType>;
				using EPool      = typename AdContext::EPool;
				using Expression = typename EPool::ExpressionType;
				using Polynomial = typename Expression::Polynomial;

			private:
				static EPool* epool() {
					return AdContext::getExpresisonPoolOnThisThread();
				}

				Expression* pooled_;

			public:
				Dual(Expression expression) : 
					pooled_(epool()->pool(expression)) {}

				Dual(ValueType x) :
					Dual(Expression{ x }) {}

				Dual(const Dual&) = default;
				Dual(Dual&&)      = default;

				const Expression& expression() const {
					return *pooled_;
				}

				ValueType x() const {
					return pooled_->x;
				}
				ValueType differential(const ThisType& dx) const {
					return pooled_->differential(*dx.pooled_);
				}

				Dual& operator=(const Dual&)     = default;
				Dual& operator=(Dual&&) noexcept = default;
				Dual& operator=(ValueType other) {
					pooled_ = epool()->pool(Expression{other});
					return *this;
				}

				BABEL_AD_DEFINE_DUAL_UNARY_ARITHMETIC(+=, expression::add);
				BABEL_AD_DEFINE_DUAL_UNARY_ARITHMETIC(-=, expression::subtract);
				BABEL_AD_DEFINE_DUAL_UNARY_ARITHMETIC(*=, expression::times);
				BABEL_AD_DEFINE_DUAL_UNARY_ARITHMETIC(/=, expression::divide);

				ThisType& operator++() { return (*this) += 1; }
				ThisType& operator--() { return (*this) -= 1; }

				ThisType operator++(int) { ThisType t(*this); (*this) += 1; return t; }
				ThisType operator--(int) { ThisType t(*this); (*this) -= 1; return t; }

				ThisType operator+() const { return *this; }
				ThisType operator-() const { return ThisType(*this) *= -1; }
			};

			BABEL_AD_DEFINE_DUAL_BINARY_ARITHMETIC(+, expression::add);
			BABEL_AD_DEFINE_DUAL_BINARY_ARITHMETIC(-, expression::subtract);
			BABEL_AD_DEFINE_DUAL_BINARY_ARITHMETIC(*, expression::times);
			BABEL_AD_DEFINE_DUAL_BINARY_ARITHMETIC(/, expression::divide);

			template<typename DUAL>
			inline bool operator==(const DUAL& lhs, const DUAL& rhs) {
				return lhs.expression().x == rhs.expression().x;
			}
			template<typename DUAL>
			inline bool operator==(const DUAL& lhs, typename DUAL::ValueType rhs) {
				return lhs.expression().x == rhs;
			}
			template<typename DUAL>
			inline bool operator==(typename DUAL::ValueType lhs, const DUAL& rhs) {
				return lhs == rhs.expression().x;
			}

			template<typename DUAL> inline bool operator!=(const DUAL& lhs, const DUAL& rhs)              { return !(lhs == rhs); }
			template<typename DUAL> inline bool operator!=(const DUAL& lhs, typename DUAL::ValueType rhs) { return !(lhs == rhs); }
			template<typename DUAL> inline bool operator!=(typename DUAL::ValueType lhs, const DUAL& rhs) { return !(lhs == rhs); }

			template<typename DUAL>
			inline bool operator<(const DUAL& lhs, const DUAL& rhs) {
				return lhs.expression().x < rhs.expression().x;
			}
			template<typename DUAL>
			inline bool operator<(const DUAL& lhs, typename DUAL::ValueType rhs) {
				return lhs.expression().x < rhs;
			}
			template<typename DUAL>
			inline bool operator<(typename DUAL::ValueType lhs, const DUAL& rhs) {
				return lhs < rhs.expression().x;
			}
			template<typename DUAL> inline bool operator >(const DUAL& lhs, const DUAL& rhs)              { return rhs < lhs; }
			template<typename DUAL> inline bool operator >(const DUAL& lhs, typename DUAL::ValueType rhs) { return rhs < lhs; }
			template<typename DUAL> inline bool operator >(typename DUAL::ValueType lhs, const DUAL& rhs) { return rhs < lhs; }
			template<typename DUAL> inline bool operator<=(const DUAL& lhs, const DUAL& rhs)              { return !(lhs > rhs); }
			template<typename DUAL> inline bool operator<=(const DUAL& lhs, typename DUAL::ValueType rhs) { return !(lhs > rhs); }
			template<typename DUAL> inline bool operator<=(typename DUAL::ValueType lhs, const DUAL& rhs) { return !(lhs > rhs); }
			template<typename DUAL> inline bool operator>=(const DUAL& lhs, const DUAL& rhs)              { return !(lhs < rhs); }
			template<typename DUAL> inline bool operator>=(const DUAL& lhs, typename DUAL::ValueType rhs) { return !(lhs < rhs); }
			template<typename DUAL> inline bool operator>=(typename DUAL::ValueType lhs, const DUAL& rhs) { return !(lhs < rhs); }

		}
	}
}

#undef BABEL_AD_DEFINE_DUAL_UNARY_ARITHMETIC
#undef BABEL_AD_DEFINE_DUAL_BINARY_ARITHMETIC
