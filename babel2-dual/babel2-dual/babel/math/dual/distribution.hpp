#pragma once

#include "../core/distribution.hpp"
#include "UnaryFunction.hpp"

namespace babel {
	namespace math {
		namespace dual {

			namespace math = babel::math;

			struct Cdf : public UnaryFunction {
				Cdf(std::shared_ptr<Expression> hs) :
					UnaryFunction(
						hs,
						math::cdf(hs->real()),
						math::pdf(hs->real())) {}
			};

		}
	}
}
