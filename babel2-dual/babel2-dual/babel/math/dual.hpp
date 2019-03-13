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

			RealType real()                    const { return expression_->real(); }
			RealType first(const Index& index) const { return expression_->first(index); }
			std::shared_ptr<Expression> expression() const { return expression_; }

			Dual& operator+=(const Dual& hs) { expression_ = std::make_shared<dual::Plus> (expression_, hs.expression_); return (*this); }
			Dual& operator-=(const Dual& hs) { expression_ = std::make_shared<dual::Minus>(expression_, hs.expression_); return (*this); }
			Dual& operator*=(const Dual& hs) { expression_ = std::make_shared<dual::Multi>(expression_, hs.expression_); return (*this); }
			Dual& operator/=(const Dual& hs) { expression_ = std::make_shared<dual::Div>  (expression_, hs.expression_); return (*this); }

			Dual& operator++() { return (*this) += 1; }
			Dual& operator--() { return (*this) -= 1; }
			
			Dual  operator++(int) { auto e = expression_; (*this) += 1; return e; }
			Dual  operator--(int) { auto e = expression_; (*this) -= 1; return e; }
		};

		inline Dual operator+(const Dual& lhs, const Dual& rhs) { return Dual(lhs) += rhs; }
		inline Dual operator-(const Dual& lhs, const Dual& rhs) { return Dual(lhs) -= rhs; }
		inline Dual operator*(const Dual& lhs, const Dual& rhs) { return Dual(lhs) *= rhs; }
		inline Dual operator/(const Dual& lhs, const Dual& rhs) { return Dual(lhs) /= rhs; }

	}
}