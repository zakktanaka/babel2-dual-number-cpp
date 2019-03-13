#pragma once
#include <memory>
#include "expression.hpp"
#include "constant.hpp"
#include "variable.hpp"

namespace babel {
	namespace math {
		namespace dual {

			class Dual {
			private:
				std::shared_ptr<Expression> expression_;

			public:
				Dual(std::shared_ptr<Expression> expression) :
					expression_(expression) {}

				Dual(const RealType& real) :
					expression_(std::make_shared<Constant>(real)) {}

				Dual(
					const RealType& real,
					std::vector<RealType> firsts) :
					expression_(std::make_shared<Variable>(real, firsts)) {}

				RealType real() const {
					return expression_->real();
				}

				RealType first(const Index& index) const {
					return expression_->first(index);
				}

				std::shared_ptr<Expression> expression() const {
					return expression_;
				}
			};
		}
	}
}