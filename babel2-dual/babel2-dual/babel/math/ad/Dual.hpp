#pragma once

#include <cassert>
#include "AdCalculationContext.hpp"

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

				const Expression& expression() const {
					return *pooled_;
				}

				const ValueType& x() const {
					return expression().x;
				}

				ThisType& operator+=(const ThisType& rhs) {
					pooled_ = epool()->pool(expression::add(expression(), rhs.expression()));
					return (*this);
				}

				ThisType& operator+=(ValueType rhs) {
					pooled_ = epool()->pool(expression::add(expression(), rhs));
					return (*this);
				}
			};


		}
	}
}