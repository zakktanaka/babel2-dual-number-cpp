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

		}
	}
}
