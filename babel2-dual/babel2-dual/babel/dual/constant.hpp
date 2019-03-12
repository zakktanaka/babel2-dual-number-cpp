#pragma once

#include "expression.hpp"

namespace babel {
	namespace dual {

		struct Constant : public Expression {
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