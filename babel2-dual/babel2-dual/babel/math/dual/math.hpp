#pragma once

#include <cmath>
#include "UnaryFunction.hpp"

namespace babel {
	namespace math {
		namespace dual {

			struct Exp : public UnaryFunction {
				Exp(std::shared_ptr<Expression> hs) : UnaryFunction(hs, std::exp(hs->real()), std::exp(hs->real())) {}
			};

			struct Log : public UnaryFunction {
				Log(std::shared_ptr<Expression> hs) : UnaryFunction(hs, std::log(hs->real()), 1 / hs->real()) {}
			};

			struct Sqrt : public UnaryFunction {
				Sqrt(std::shared_ptr<Expression> hs) : 
					UnaryFunction(
						hs, 
						std::sqrt(hs->real()), 
						0.5 / std::sqrt(hs->real())) {}
			};

			struct Pow : public UnaryFunction {
				Pow(std::shared_ptr<Expression> hs, const RealType& p) : 
					UnaryFunction(
						hs, 
						std::pow(hs->real(), p), 
						p * std::pow(hs->real(), p - 1)) {}
			};

		}
	}
}
