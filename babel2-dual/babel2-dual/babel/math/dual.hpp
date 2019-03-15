#pragma once
#include <memory>
#include "dual/expression.hpp"
#include "dual/constant.hpp"
#include "dual/variable.hpp"
#include "dual/arithmetic.hpp"
#include "dual/negative.hpp"
#include "dual/math.hpp"
#include "dual/distribution.hpp"

#define BABEL_DUAL_UNARY_FUNC(funcname, funcstruct) \
	inline Dual funcname(const Dual& hs) { return Dual(std::make_shared<funcstruct>(hs.expression())); }

namespace babel {
	namespace math {

		class Dual {
		private:
			using Expression = dual::Expression;
			using RealType   = dual::RealType;
			using Index      = dual::Index;

			std::shared_ptr<Expression> expression_;

		public:
			Dual(std::shared_ptr<Expression> expression) :
				expression_(expression) {}

			Dual(const RealType& real) :
				Dual(std::make_shared<dual::Constant>(real)) {}

			Dual(
				const RealType& real,
				std::vector<RealType> firsts) :
				Dual(std::make_shared<dual::Variable>(real, firsts)) {}

			Dual(
				const RealType& real,
				const Index&    index,
				const RealType& firstAtIndex) :
				Dual(std::make_shared<dual::IndexedVariable>(real, index, firstAtIndex)) {}
			
			Dual(const Dual& ) = default;
			Dual(      Dual&&) = default;

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

			Dual operator+() const { return Dual(expression_); }
			Dual operator-() const { return Dual(std::make_shared<dual::Negative>(expression_)); }
		};

		inline Dual operator+(const Dual& lhs, const Dual& rhs) { return Dual(lhs) += rhs; }
		inline Dual operator-(const Dual& lhs, const Dual& rhs) { return Dual(lhs) -= rhs; }
		inline Dual operator*(const Dual& lhs, const Dual& rhs) { return Dual(lhs) *= rhs; }
		inline Dual operator/(const Dual& lhs, const Dual& rhs) { return Dual(lhs) /= rhs; }

		inline bool operator==(const Dual& lhs, const Dual& rhs) { return   lhs.real() == rhs.real(); }
		inline bool operator!=(const Dual& lhs, const Dual& rhs) { return !(lhs == rhs); }

		inline bool operator< (const Dual& lhs, const Dual& rhs) { return lhs.real() < rhs.real(); }
		inline bool operator> (const Dual& lhs, const Dual& rhs) { return   rhs < lhs;  }
		inline bool operator<=(const Dual& lhs, const Dual& rhs) { return !(lhs > rhs); }
		inline bool operator>=(const Dual& lhs, const Dual& rhs) { return !(lhs < rhs); }

		BABEL_DUAL_UNARY_FUNC(exp,  dual::Exp);
		BABEL_DUAL_UNARY_FUNC(log,  dual::Log);
		BABEL_DUAL_UNARY_FUNC(sqrt, dual::Sqrt);

		inline Dual pow(const Dual& hs, const dual::RealType& p) {
			return Dual(std::make_shared<dual::Pow>(hs.expression(), p));
		}

		BABEL_DUAL_UNARY_FUNC(cdf, dual::Cdf);

	}
}

#undef BABEL_DUAL_UNARY_FUNC
