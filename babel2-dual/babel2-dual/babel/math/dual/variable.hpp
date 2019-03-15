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

			struct IndexedVariable : public Expression {
				Index    index_;
				RealType real_;
				RealType firstatindex_;

				IndexedVariable(
					const RealType& real,
					const Index&    index,
					const RealType& firstAtIndex) :
					index_(index), real_(real), firstatindex_(firstAtIndex) {}

				RealType real() override {
					return real_;
				}
				RealType first(const Index & index) override {
					return index == index_ ? firstatindex_ : 0;
				}
			};

		}
	}
}