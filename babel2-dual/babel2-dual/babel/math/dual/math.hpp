#pragma once

#include "../core/cmath.hpp"
#include "UnaryFunction.hpp"

namespace babel {
	namespace math {
		namespace dual {

			struct Exp : public UnaryFunction {
				Exp(std::shared_ptr<Expression> hs) : 
					UnaryFunction(
					hs, 
					babel::math::exp(hs->real()), 
					babel::math::exp(hs->real())) {}
			};

			struct Log : public UnaryFunction {
				Log(std::shared_ptr<Expression> hs) : 
					UnaryFunction(
						hs, 
						babel::math::log(hs->real()),
						1 / hs->real()) {}
			};

			struct Sqrt : public UnaryFunction {
				Sqrt(std::shared_ptr<Expression> hs) : 
					UnaryFunction(
						hs, 
						babel::math::sqrt(hs->real()),
						0.5 / babel::math::sqrt(hs->real())) {}
			};

			struct Pow : public UnaryFunction {
				Pow(std::shared_ptr<Expression> hs, const RealType& p) : 
					UnaryFunction(
						hs, 
						babel::math::pow(hs->real(), p),
						p * babel::math::pow(hs->real(), p - 1)) {}
			};

		}
	}
}
