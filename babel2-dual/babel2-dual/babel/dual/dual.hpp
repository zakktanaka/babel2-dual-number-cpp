#pragma once
#include <memory>
#include "expression.hpp"
#include "constant.hpp"

namespace babel {
	namespace dual {


		class Dual
		{
		private:
			std::shared_ptr<Expression> expression_;
		
		public:
			Dual(std::shared_ptr<Expression> expression) : expression_(expression) {}
			Dual(const RealType& real) : expression_(std::make_shared<Constant>(real)) {}

			RealType real() { 
				return expression_->real(); 
			}

			RealType first(const Index& index) { 
				return expression_->first(index); 
			}

		};
	}
}