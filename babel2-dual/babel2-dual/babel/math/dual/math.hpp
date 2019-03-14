#pragma once

#include "../core/cmath.hpp"
#include "UnaryFunction.hpp"

namespace babel {
	namespace math {
		namespace dual {

			namespace math = babel::math;

			struct Exp : public UnaryFunction {
				Exp(std::shared_ptr<Expression> hs) : 
					UnaryFunction(
					hs, 
					math::exp(hs->real()), 
					math::exp(hs->real())) {}
			};

			struct Log : public UnaryFunction {
				Log(std::shared_ptr<Expression> hs) : 
					UnaryFunction(
						hs, 
						math::log(hs->real()),
						1 / hs->real()) {}
			};

			struct Sqrt : public UnaryFunction {
				Sqrt(std::shared_ptr<Expression> hs) : 
					UnaryFunction(
						hs, 
						math::sqrt(hs->real()),
						0.5 / math::sqrt(hs->real())) {}
			};

			struct Pow : public UnaryFunction {
				Pow(std::shared_ptr<Expression> hs, const RealType& p) : 
					UnaryFunction(
						hs, 
						math::pow(hs->real(), p),
						p * math::pow(hs->real(), p - 1)) {}
			};

		}
	}
}
