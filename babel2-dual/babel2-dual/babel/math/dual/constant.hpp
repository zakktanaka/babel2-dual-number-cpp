#pragma once

#include "expression.hpp"

namespace babel {
	namespace math {
		namespace dual {

			template<typename RealType_>
			struct Constant : public Expression<RealType_> {
			private:
				RealType real_;

			public:
				Constant(const RealType& real) : real_(real) {}

				RealType real() override {
					return real_;
				}

				RealType first(const Index & index) override {
					return 0;
				};
			};
		}
	}
}