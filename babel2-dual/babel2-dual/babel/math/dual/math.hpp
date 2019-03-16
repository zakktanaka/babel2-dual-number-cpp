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

		}
	}
}
