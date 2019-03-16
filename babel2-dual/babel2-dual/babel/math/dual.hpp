#pragma once
#include <memory>
#include "dual/expression.hpp"
#include "dual/constant.hpp"
#include "dual/variable.hpp"
#include "dual/arithmetic.hpp"
#include "dual/negative.hpp"
#include "dual/math.hpp"
#include "dual/distribution.hpp"
#include "utility/type_traits.hpp"

#define BABEL_DUAL_UNARY_FUNC(funcname, funcstruct) \
	template<typename RealType_> inline Dual<typename RealType_> funcname(const Dual<typename RealType_>& hs) { return Dual<typename RealType_>(std::make_shared<funcstruct<typename RealType_>>(hs.expression())); }

namespace babel {
	namespace math {

		template<typename RealType_>
		class Dual {
		private:
			using Index      = dual::Index;
			using RealType   = typename RealType_;
			using Expression = dual::Expression<RealType>;
			using RealDual   = Dual<RealType>;
			std::shared_ptr<Expression> expression_;

		public:
			Dual(std::shared_ptr<Expression> expression) :
				expression_(expression) {}

			Dual(const RealType& real) :
				Dual(std::make_shared<dual::Constant<RealType>>(real)) {}

			Dual(
				const RealType& real,
				std::vector<RealType> firsts) :
				Dual(std::make_shared<dual::Variable<RealType>>(real, firsts)) {}

			Dual(
				const RealType& real,
				const Index&    index,
				const RealType& firstAtIndex) :
				Dual(std::make_shared<dual::IndexedVariable<RealType>>(real, index, firstAtIndex)) {}
			
			Dual(const Dual& ) = default;
			Dual(      Dual&&) = default;

			RealType real()                    const { return expression_->real(); }
			RealType first(const Index& index) const { return expression_->first(index); }
			std::shared_ptr<Expression> expression() const { return expression_; }

			RealDual& operator+=(const Dual& hs) { expression_ = std::make_shared<dual::Plus<RealType>> (expression_, hs.expression_); return (*this); }
			RealDual& operator-=(const Dual& hs) { expression_ = std::make_shared<dual::Minus<RealType>>(expression_, hs.expression_); return (*this); }
			RealDual& operator*=(const Dual& hs) { expression_ = std::make_shared<dual::Multi<RealType>>(expression_, hs.expression_); return (*this); }
			RealDual& operator/=(const Dual& hs) { expression_ = std::make_shared<dual::Div<RealType>>  (expression_, hs.expression_); return (*this); }

			RealDual& operator++() { return (*this) += 1; }
			RealDual& operator--() { return (*this) -= 1; }
			
			RealDual operator++(int) { auto e = expression_; (*this) += 1; return e; }
			RealDual operator--(int) { auto e = expression_; (*this) -= 1; return e; }

			RealDual operator+() const { return Dual(expression_); }
			RealDual operator-() const { return Dual(std::make_shared<dual::Negative<RealType>>(expression_)); }
		};

		template<typename RealType_>
		inline Dual<typename RealType_> operator+(const Dual<typename RealType_>& lhs, const Dual<typename RealType_>& rhs) { return Dual<typename RealType_>(lhs) += rhs; }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline Dual<typename RealType_> operator+(Other_ lhs, const Dual<typename RealType_>& rhs) { return Dual<typename RealType_>(lhs) += rhs; }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline Dual<typename RealType_> operator+(const Dual<typename RealType_>& lhs, Other_ rhs) { return Dual<typename RealType_>(lhs) += Dual<typename RealType_>(rhs); }

		template<typename RealType_>
		inline Dual<typename RealType_> operator-(const Dual<typename RealType_>& lhs, const Dual<typename RealType_>& rhs) { return Dual<typename RealType_>(lhs) -= rhs; }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline Dual<typename RealType_> operator-(Other_ lhs, const Dual<typename RealType_>& rhs) { return Dual<typename RealType_>(lhs) -= rhs; }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline Dual<typename RealType_> operator-(const Dual<typename RealType_>& lhs, Other_ rhs) { return Dual<typename RealType_>(lhs) -= Dual<typename RealType_>(rhs); }

		template<typename RealType_>
		inline Dual<typename RealType_> operator*(const Dual<typename RealType_>& lhs, const Dual<typename RealType_>& rhs) { return Dual<typename RealType_>(lhs) *= rhs; }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline Dual<typename RealType_> operator*(Other_ lhs, const Dual<typename RealType_>& rhs) { return Dual<typename RealType_>(lhs) *= rhs; }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline Dual<typename RealType_> operator*(const Dual<typename RealType_>& lhs, Other_ rhs) { return Dual<typename RealType_>(lhs) *= Dual<typename RealType_>(rhs); }

		template<typename RealType_>
		inline Dual<typename RealType_> operator/(const Dual<typename RealType_>& lhs, const Dual<typename RealType_>& rhs) { return Dual<typename RealType_>(lhs) /= rhs; }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline Dual<typename RealType_> operator/(Other_ lhs, const Dual<typename RealType_>& rhs) { return Dual<typename RealType_>(lhs) /= rhs; }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline Dual<typename RealType_> operator/(const Dual<typename RealType_>& lhs, Other_ rhs) { return Dual<typename RealType_>(lhs) /= Dual<typename RealType_>(rhs); }

		template<typename RealType_>
		inline bool operator==(const Dual<typename RealType_>& lhs, const Dual<typename RealType_>& rhs) { return lhs.real() == rhs.real(); }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator==(Other_ lhs, const Dual<typename RealType_>& rhs) { return lhs        == rhs.real(); }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator==(const Dual<typename RealType_>& lhs, Other_ rhs) { return lhs.real() == rhs       ; }

		template<typename RealType_>
		inline bool operator!=(const Dual<typename RealType_>& lhs, const Dual<typename RealType_>& rhs) { return !(lhs == rhs); }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator!=(Other_ lhs, const Dual<typename RealType_>& rhs) { return !(lhs == rhs); }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator!=(const Dual<typename RealType_>& lhs, Other_ rhs) { return !(lhs == rhs); }

		template<typename RealType_>
		inline bool operator< (const Dual<typename RealType_>& lhs, const Dual<typename RealType_>& rhs) { return lhs.real() < rhs.real(); }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator< (Other_ lhs, const Dual<typename RealType_>& rhs) { return lhs        < rhs.real(); }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator< (const Dual<typename RealType_>& lhs, Other_ rhs) { return lhs.real() < rhs       ; }

		template<typename RealType_>
		inline bool operator> (const Dual<typename RealType_>& lhs, const Dual<typename RealType_>& rhs) { return   rhs < lhs;  }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator> (Other_ lhs, const Dual<typename RealType_>& rhs) { return   rhs < lhs;  }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator> (const Dual<typename RealType_>& lhs, Other_ rhs) { return   rhs < lhs;  }

		template<typename RealType_>
		inline bool operator<=(const Dual<typename RealType_>& lhs, const Dual<typename RealType_>& rhs) { return !(lhs > rhs); }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator<=(Other_ lhs, const Dual<typename RealType_>& rhs) { return !(lhs > rhs); }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator<=(const Dual<typename RealType_>& lhs, Other_ rhs) { return !(lhs > rhs); }

		template<typename RealType_>
		inline bool operator>=(const Dual<typename RealType_>& lhs, const Dual<typename RealType_>& rhs) { return !(lhs < rhs); }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator>=(Other_ lhs, const Dual<typename RealType_>& rhs) { return !(lhs < rhs); }
		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline bool operator>=(const Dual<typename RealType_>& lhs, Other_ rhs) { return !(lhs < rhs); }

		BABEL_DUAL_UNARY_FUNC(exp,  dual::Exp);
		BABEL_DUAL_UNARY_FUNC(log,  dual::Log);
		BABEL_DUAL_UNARY_FUNC(sqrt, dual::Sqrt);

		template<typename RealType_, typename Other_, typename type_traits::nullptr_t_if_convertible<Other_, RealType_> = nullptr>
		inline Dual<typename RealType_> pow(const Dual<typename RealType_>& hs, Other_ p) {
			return Dual<typename RealType_>(std::make_shared<dual::Pow<typename RealType_>>(hs.expression(), RealType_(p)));
		}

		BABEL_DUAL_UNARY_FUNC(cdf, dual::Cdf);
		BABEL_DUAL_UNARY_FUNC(pdf, dual::Pdf);

	}
}

#undef BABEL_DUAL_UNARY_FUNC
