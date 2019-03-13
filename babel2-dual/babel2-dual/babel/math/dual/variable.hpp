#pragma once

#include <vector>
#include "expression.hpp"

namespace babel {
	namespace math {
		namespace dual {

			struct Variable : public Expression {
				RealType real_;
				std::vector<RealType> firsts_;

				Variable(
					const RealType& real,
					std::vector<RealType> firsts) :
					real_(real), firsts_(firsts) {}

				RealType real() override {
					return real_;
				}
				RealType first(const Index & index) override {
					return index < firsts_.size() ? firsts_[index] : 0;
				}
			};
		}
	}
}