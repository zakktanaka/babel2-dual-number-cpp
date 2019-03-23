#pragma once

#include <memory>
#include "expression.hpp"

namespace babel {
	namespace math {
		namespace dual {

			template<typename RealType_>
			struct UnaryFunction : public Expression<RealType_> {
			private:
				RealType dx_;
				std::shared_ptr<Expression> hs_;

			public:
				UnaryFunction(std::shared_ptr<Expression> hs, RealType x, RealType dx) : Expression(x), dx_(dx), hs_(hs) {}
				virtual ~UnaryFunction() {}

				RealType first(const Index & index) override { return dx_ * hs_->first(index); }
			};

		}
	}
}
