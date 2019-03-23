#pragma once

#include "expression.hpp"

namespace babel {
	namespace math {
		namespace dual {

			template<typename RealType_>
			struct Constant : public Expression<RealType_> {
				Constant(const RealType& real) : Expression(real) {}

				RealType first(const Index & index) override {
					return 0;
				};
			};
		}
	}
}