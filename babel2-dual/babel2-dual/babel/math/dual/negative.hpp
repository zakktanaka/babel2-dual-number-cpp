#pragma once

#include <cmath>
#include "UnaryFunction.hpp"

namespace babel {
	namespace math {
		namespace dual {

			template<typename RealType_>
			struct Negative : public UnaryFunction<RealType_> {
				Negative(std::shared_ptr<Expression> hs) : UnaryFunction(hs, -hs->real(), -1) {}
			};

		}
	}
}
