#pragma once

#include <cmath>
#include "UnaryFunction.hpp"

namespace babel {
	namespace math {
		namespace dual {

			struct Negative : public UnaryFunction {
				Negative(std::shared_ptr<Expression> hs) : UnaryFunction(hs, -hs->real(), -1) {}
			};

		}
	}
}
