#pragma once

#include "types.hpp"

namespace babel {
	namespace math {
		namespace dual {

			template<typename RealType_>
			struct Expression {
				using RealType = typename RealType_;
				Expression() {}
				virtual ~Expression() {}
				virtual RealType real() = 0;
				virtual RealType first(const Index& index) = 0;
			};

		}
	}
}
