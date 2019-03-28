#pragma once
#include <list>
#include <vector>
#include <utility>

namespace babel {
	namespace math {
		namespace ad {
			namespace expression {

				template<typename ValueType_>
				struct  Expression {
					using ValueType  = ValueType_;
					using ThisType   = Expression<ValueType>;
					using Term       = std::pair<ValueType, ThisType*>;
					using Polynomial = std::vector<Term>;

					const ValueType  x;
					const Polynomial polynomial;

					ValueType differential(const ThisType* h) const {
						if (h == this) {
							return 1;
						}

						ValueType d(0);
						for (auto& term : polynomial) {
							d += std::get<0>(term) * std::get<1>(term)->differential(h);
						}
						return d;
					}
				};

				template<typename ValueType_>
				struct  ExpressionGenerator {
					using ValueType  = ValueType_;
					using Expression = Expression<ValueType>;
					using Polynomial = typename Expression::Polynomial;

					std::list<Expression> expressions;

					Expression* generate(ValueType x, Polynomial polynomial) {
						expressions.emplace_back(Expression{ x, polynomial });
						return &*std::rbegin(expressions);
					}

					Expression* generate(ValueType x) {
						return generate(x, {});
					}

				};

			}
		}
	}
}