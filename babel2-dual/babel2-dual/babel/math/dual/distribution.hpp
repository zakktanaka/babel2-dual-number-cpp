#pragma once

#include "../core/distribution.hpp"
#include "UnaryFunction.hpp"

namespace babel {
	namespace math {
		namespace dual {

			namespace math = babel::math;

			template<typename RealType_>
			struct Cdf : public UnaryFunction<RealType_> {
				Cdf(std::shared_ptr<Expression> hs) :
					UnaryFunction(
						hs,
						math::cdf(hs->real()),
						math::pdf(hs->real())) {}
			};

			template<typename RealType_>
			struct Pdf : public UnaryFunction<RealType_> {
				Pdf(std::shared_ptr<Expression> hs) :
					UnaryFunction(
						hs,
						math::pdf (hs->real()),
						math::dpdf(hs->real())) {}
			};
		}
	}
}
