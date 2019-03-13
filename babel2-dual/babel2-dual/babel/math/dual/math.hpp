#pragma once

#include <memory>
#include <cmath>
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

			struct Exp : public UnaryFunction {
				Exp(std::shared_ptr<Expression> hs) : UnaryFunction(hs, std::exp(hs->real()), std::exp(hs->real())) {}
			};

			struct Log : public UnaryFunction {
				Log(std::shared_ptr<Expression> hs) : UnaryFunction(hs, std::log(hs->real()), 1 / hs->real()) {}
			};

		}
	}
}
