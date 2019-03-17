#pragma once

#include "../core/cmath.hpp"
#include "unary_function.hpp"

namespace babel {
	namespace math {
		namespace dual {

			namespace math = babel::math;

			template<typename RealType_>
			struct Exp : public UnaryFunction<RealType_> {
				Exp(std::shared_ptr<Expression> hs) : 
					UnaryFunction(
					hs, 
					math::exp(hs->real()), 
					math::exp(hs->real())) {}
			};

			template<typename RealType_>
			struct Log : public UnaryFunction<RealType_> {
				Log(std::shared_ptr<Expression> hs) : 
					UnaryFunction(
						hs, 
						math::log(hs->real()),
						1 / hs->real()) {}
			};

			template<typename RealType_>
			struct Sqrt : public UnaryFunction<RealType_> {
				Sqrt(std::shared_ptr<Expression> hs) : 
					UnaryFunction(
						hs, 
						math::sqrt(hs->real()),
						0.5 / math::sqrt(hs->real())) {}
			};

			template<typename RealType_>
			struct Pow : public UnaryFunction<RealType_> {
				Pow(std::shared_ptr<Expression> hs, const RealType& p) : 
					UnaryFunction(
						hs, 
						math::pow(hs->real(), p),
						p * math::pow(hs->real(), p - 1)) {}
			};

			template<typename RealType_>
			struct Pow1 : public UnaryFunction<RealType_> {
				Pow1(const RealType& p, std::shared_ptr<Expression> hs) :
					UnaryFunction(
						hs,
						math::pow(p, hs->real()),
						math::pow(p, hs->real()) * math::log(p)) {}
			};

			template<typename RealType_>
			struct Pow2 : public Expression<RealType_> {
				RealType_ real_;
				std::shared_ptr<Expression> lhs_;
				std::shared_ptr<Expression> rhs_;

				Pow2(
					std::shared_ptr<Expression> lhs,
					std::shared_ptr<Expression> rhs
				) : 
					real_(math::pow(lhs->real(), rhs->real())), 
					lhs_(lhs), 
					rhs_(rhs) {}

				RealType real() override {
					return real_;
				}
				RealType first(const Index & index) override {
					auto  x0 = lhs_->real();
					auto dx0 = lhs_->first(index);
					auto  x1 = rhs_->real();
					auto dx1 = rhs_->first(index);
					return real_ * (math::log(x0) * dx1 + dx0 * x1 / x0);
				}
			};

		}
	}
}
