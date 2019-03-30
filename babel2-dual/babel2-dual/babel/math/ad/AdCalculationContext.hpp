#pragma once

#include <cassert>
#include "expression/ExpressionPool.hpp"

namespace babel {
	namespace math {
		namespace ad {

			namespace detail {
				template<typename ValueType_>
				thread_local babel::math::ad::expression::ExpressionPool<ValueType_>* expressionPool = nullptr;
			}

			template<typename ValueType_>
			struct AdCalculationContext {
				using ValueType = ValueType_;
				using EPool     = expression::ExpressionPool<ValueType>;

				static EPool* getExpresisonPoolOnThisThread() {
					assert(detail::expressionPool<ValueType> != nullptr && "AdCalculationContext has already existed on this thread.");
					return detail::expressionPool<ValueType>;
				}

				EPool pool;

				AdCalculationContext() : pool() {
					assert(detail::expressionPool<ValueType> == nullptr && "AdCalculationContext exists on this thread.");
					detail::expressionPool<ValueType> = &pool;
				}

				~AdCalculationContext() {
					detail::expressionPool<ValueType> = nullptr;
				}
			};
		}
	}
}