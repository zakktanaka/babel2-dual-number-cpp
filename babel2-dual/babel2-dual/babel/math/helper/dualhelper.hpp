#pragma once

#include <string>
#include <unordered_map>
#include "../dual.hpp"

namespace babel {
	namespace math {
		namespace helper {

			using DualIndex = babel::math::dual::Index;
			using DualTag   = std::string;

			struct DualKey {
				const DualIndex index;
				const DualTag   tag;
			};

			template<typename T> class DualHelper{};

			template<typename RealType_> class DualHelper<babel::math::Dual<typename RealType_>> {
			private:
				using RealType = typename RealType_;
				using RealDual = babel::math::Dual<RealType>;

				DualIndex indexer_;
				std::unordered_map<std::string, DualKey> keys_;

			public:
				DualHelper() : indexer_(0), keys_() {}

				RealDual newDual(const DualTag& tag, const RealType& real) {
					return newDual(tag, real, 1);
				}

				RealDual newDual(const DualTag& tag, const RealType& real, const RealType& first) {
					if (keys_.find(tag) != std::end(keys_)) {
						throw std::runtime_error("dual is already created.");
					}

					auto key = DualKey{indexer_++, tag};
					keys_.emplace(tag, key);

					return RealDual{real, key.index, first};
				}

				DualKey getKey(const DualTag& tag) const {
					auto key = keys_.find(tag);
					if (key == std::end(keys_)) {
						throw std::runtime_error("tag is not created.");
					}

					return key->second;
				}

				RealType getFirst(const RealDual& val, const DualKey& key) const {
					return val.first(key.index);
				}

				RealType getFirst(const RealDual& val, const DualTag& tag) const {
					return getFirst(val, getKey(tag));
				}
			};

		}
	}
}