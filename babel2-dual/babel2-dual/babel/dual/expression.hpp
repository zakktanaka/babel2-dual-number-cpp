#pragma once

#include "types.hpp"

namespace babel {
	namespace dual {

		struct Expression {
			Expression(){}
			virtual ~Expression(){}
		 	virtual RealType real() = 0;
			virtual RealType first(const Index& index) = 0;
		};

	}
}
