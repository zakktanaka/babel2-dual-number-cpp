#pragma once

#include <list>
#include "Expression.hpp"

namespace babel {
	namespace math {
		namespace ad {
			namespace expression {

				template<typename ValueType_>
				struct ExpressionPool {
					using ValueType      = ValueType_;
					using ExpressionType = Expression<ValueType>;

					std::list<ExpressionType> pool_;

					ExpressionType* pool(ExpressionType expression) {
						pool_.emplace_back(std::move(expression));
						return &*std::rbegin(pool_);
					}
				};


			}
		}
	}
}