#pragma once

#include <memory>
#include "expression.hpp"

namespace babel {
	namespace math {
		namespace dual {

			struct UnaryFunction : public Expression {
			private:
				RealType x_;
				RealType dx_;
				std::shared_ptr<Expression> hs_;

			public:
				UnaryFunction(std::shared_ptr<Expression> hs, RealType x, RealType dx) : x_(x), dx_(dx), hs_(hs) {}
				virtual ~UnaryFunction() {}

				RealType real()                     override { return x_; }
				RealType first(const Index & index) override { return dx_ * hs_->first(index); }
			};

		}
	}
}
