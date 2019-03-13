#pragma once
#include <memory>
#include "dual/expression.hpp"
#include "dual/constant.hpp"
#include "dual/variable.hpp"
#include "dual/arithmetic.hpp"

namespace babel {
	namespace math {

		class Dual {
		private:
			using Expression = dual::Expression;
			using RealType = dual::RealType;
			using Index = dual::Index;

			std::shared_ptr<Expression> expression_;

		public:
			Dual(std::shared_ptr<Expression> expression) :
				expression_(expression) {}

			Dual(const RealType& real) :
				expression_(std::make_shared<dual::Constant>(real)) {}

			Dual(
				const RealType& real,
				std::vector<RealType> firsts) :
				expression_(std::make_shared<dual::Variable>(real, firsts)) {}

			RealType real() const {
				return expression_->real();
			}

			RealType first(const Index& index) const {
				return expression_->first(index);
			}

			std::shared_ptr<Expression> expression() const {
				return expression_;
			}

		};

		inline Dual operator+(const Dual& lhs, const Dual& rhs) { return Dual(std::make_shared<dual::Plus>(lhs.expression(), rhs.expression())); }
		inline Dual operator-(const Dual& lhs, const Dual& rhs) { return Dual(std::make_shared<dual::Minus>(lhs.expression(), rhs.expression())); }
		inline Dual operator*(const Dual& lhs, const Dual& rhs) { return Dual(std::make_shared<dual::Multi>(lhs.expression(), rhs.expression())); }
		inline Dual operator/(const Dual& lhs, const Dual& rhs) { return Dual(std::make_shared<dual::Div>(lhs.expression(), rhs.expression())); }

	}
}