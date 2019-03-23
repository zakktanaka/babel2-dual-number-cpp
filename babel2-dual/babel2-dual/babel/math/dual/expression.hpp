#pragma once

#include "types.hpp"

namespace babel {
	namespace math {
		namespace dual {

			template<typename RealType_>
			struct Expression {
				using RealType = typename RealType_;
				RealType real_;
				Expression(RealType x) : real_(x) {}
				virtual ~Expression() {}
				virtual RealType real() { return real_; }
				virtual RealType first(const Index& index) = 0;
			};

		}
	}
}
