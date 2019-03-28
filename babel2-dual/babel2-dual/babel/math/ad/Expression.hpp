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
					using Term       = std::pair<ValueType, const ThisType*>;
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

					const Expression* operator()(ValueType x, Polynomial polynomial) {
						expressions.emplace_back(Expression{ x, polynomial });
						return &*std::rbegin(expressions);
					}

					const Expression* operator()(ValueType x) {
						return (*this)(x, {});
					}
				};

				template<typename ValueType_>
				inline const Expression<ValueType_>* add(
					const Expression<ValueType_>* lhs, 
					const Expression<ValueType_>* rhs, 
					ExpressionGenerator<ValueType_>& gen) {
					return gen( lhs->x + rhs->x, { {ValueType_(1), lhs}, {ValueType_(1), rhs} });
				}
				template<typename ValueType_>
				inline const Expression<ValueType_>* add(
					ValueType_                    lhs, 
					const Expression<ValueType_>* rhs, 
					ExpressionGenerator<ValueType_>& gen) {
					return gen(lhs + rhs->x, { {ValueType_(1), rhs} });
				}
				template<typename ValueType_>
				inline const Expression<ValueType_>* add(
					const Expression<ValueType_>* lhs,
					ValueType_                    rhs,
					ExpressionGenerator<ValueType_>& gen) {
					return gen((lhs->x + rhs), { {ValueType_(1), lhs} });
				}

				template<typename ValueType_>
				inline const Expression<ValueType_>* subtract(
					const Expression<ValueType_>* lhs,
					const Expression<ValueType_>* rhs,
					ExpressionGenerator<ValueType_>& gen) {
					return gen(lhs->x - rhs->x, { {ValueType_(1), lhs}, {ValueType_(-1), rhs} });
				}
				template<typename ValueType_>
				inline const Expression<ValueType_>* subtract(
					ValueType_                    lhs,
					const Expression<ValueType_>* rhs,
					ExpressionGenerator<ValueType_>& gen) {
					return gen(lhs - rhs->x, { {ValueType_(-1), rhs} });
				}
				template<typename ValueType_>
				inline const Expression<ValueType_>* subtract(
					const Expression<ValueType_>* lhs,
					ValueType_                    rhs,
					ExpressionGenerator<ValueType_>& gen) {
					return gen(lhs->x - rhs, { {ValueType_(1), lhs} });
				}

				template<typename ValueType_>
				inline const Expression<ValueType_>* times(
					const Expression<ValueType_>* lhs,
					const Expression<ValueType_>* rhs,
					ExpressionGenerator<ValueType_>& gen) {
					return gen(lhs->x * rhs->x, { {rhs->x, lhs}, {lhs->x, rhs} });
				}
				template<typename ValueType_>
				inline const Expression<ValueType_>* times(
					ValueType_                    lhs,
					const Expression<ValueType_>* rhs,
					ExpressionGenerator<ValueType_>& gen) {
					return gen(lhs * rhs->x, { {lhs, rhs} });
				}
				template<typename ValueType_>
				inline const Expression<ValueType_>* times(
					const Expression<ValueType_>* lhs,
					ValueType_                    rhs,
					ExpressionGenerator<ValueType_>& gen) {
					return gen(lhs->x * rhs, { {rhs, lhs} });
				}

				template<typename ValueType_>
				inline const Expression<ValueType_>* divide(
					const Expression<ValueType_>* lhs,
					const Expression<ValueType_>* rhs,
					ExpressionGenerator<ValueType_>& gen) {
					return gen(lhs->x / rhs->x, { {ValueType_(1) / rhs->x, lhs}, {ValueType_(-1) * lhs->x / (rhs->x * rhs->x), rhs} });
				}
				template<typename ValueType_>
				inline const Expression<ValueType_>* divide(
					ValueType_                    lhs,
					const Expression<ValueType_>* rhs,
					ExpressionGenerator<ValueType_>& gen) {
					return gen(lhs / rhs->x, { {ValueType_(-1) / (rhs->x * rhs->x), rhs} });
				}
				template<typename ValueType_>
				inline const Expression<ValueType_>* divide(
					const Expression<ValueType_>* lhs,
					ValueType_                    rhs,
					ExpressionGenerator<ValueType_>& gen) {
					return gen(lhs->x / rhs, { { ValueType_(1) / rhs, lhs} });
				}

			}
		}
	}
}