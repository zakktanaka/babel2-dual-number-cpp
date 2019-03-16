#pragma once

#include <memory>
#include "expression.hpp"

namespace babel {
	namespace math {
		namespace dual {

			template<typename RealType_>
			struct Plus : public Expression<RealType_> {
				std::shared_ptr<Expression> lhs_;
				std::shared_ptr<Expression> rhs_;

				Plus(
					std::shared_ptr<Expression> lhs,
					std::shared_ptr<Expression> rhs
				) : lhs_(lhs), rhs_(rhs) {}

				RealType real() override {
					return lhs_->real() + rhs_->real();
				}
				RealType first(const Index & index) override {
					return lhs_->first(index) + rhs_->first(index);
				}
			};

			template<typename RealType_>
			struct Minus : public Expression<RealType_> {
				std::shared_ptr<Expression> lhs_;
				std::shared_ptr<Expression> rhs_;

				Minus(
					std::shared_ptr<Expression> lhs,
					std::shared_ptr<Expression> rhs
				) : lhs_(lhs), rhs_(rhs) {}

				RealType real() override {
					return lhs_->real() - rhs_->real();
				}
				RealType first(const Index & index) override {
					return lhs_->first(index) - rhs_->first(index);
				}
			};

			template<typename RealType_>
			struct Multi : public Expression<RealType_> {
				std::shared_ptr<Expression> lhs_;
				std::shared_ptr<Expression> rhs_;

				Multi(
					std::shared_ptr<Expression> lhs,
					std::shared_ptr<Expression> rhs
				) : lhs_(lhs), rhs_(rhs) {}

				RealType real() override {
					return lhs_->real() * rhs_->real();
				}
				RealType first(const Index & index) override {
					auto  x0 = lhs_->real();
					auto dx0 = lhs_->first(index);
					auto  x1 = rhs_->real();
					auto dx1 = rhs_->first(index);
					return x0 * dx1 + x1 * dx0;
				}
			};

			template<typename RealType_>
			struct Div : public Expression<RealType_> {
				std::shared_ptr<Expression> lhs_;
				std::shared_ptr<Expression> rhs_;

				Div(
					std::shared_ptr<Expression> lhs,
					std::shared_ptr<Expression> rhs
				) : lhs_(lhs), rhs_(rhs) {}

				RealType real() override {
					return lhs_->real() / rhs_->real();
				}
				RealType first(const Index & index) override {
					auto  x0 = lhs_->real();
					auto dx0 = lhs_->first(index);
					auto  x1 = rhs_->real();
					auto dx1 = rhs_->first(index);
					return (x1 * dx0 - x0 * dx1) / (x1 * x1);
				}
			};

		}
	}
}
