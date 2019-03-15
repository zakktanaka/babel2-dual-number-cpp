#pragma once

#include <string>
#include <unordered_map>
#include "../dual.hpp"

namespace babel {
	namespace math {
		namespace helper {

			using Dual      = babel::math::Dual;
			using DualIndex = babel::math::dual::Index;
			using DualReal  = babel::math::dual::RealType;
			using DualTag   = std::string;

			struct DualKey {
				const DualIndex index;
				const DualTag   tag;
			};

			template<typename T> class DualHelper{};

			template<> class DualHelper<babel::math::Dual> {
			private:
				DualIndex indexer_;
				std::unordered_map<std::string, DualKey> keys_;

			public:
				DualHelper() : indexer_(0), keys_() {}

				Dual newDual(const DualTag& tag, const DualReal& real) {
					return newDual(tag, real, 1);
				}

				Dual newDual(const DualTag& tag, const DualReal& real, const DualReal& first) {
					if (keys_.find(tag) != std::end(keys_)) {
						throw std::runtime_error("dual is already created.");
					}

					auto key = DualKey{indexer_++, tag};
					keys_.emplace(tag, key);

					return Dual{real, key.index, first};
				}

				DualKey getKey(const DualTag& tag) const {
					auto key = keys_.find(tag);
					if (key == std::end(keys_)) {
						throw std::runtime_error("tag is not created.");
					}

					return key->second;
				}

				DualReal getFirst(const Dual& val, const DualKey& key) const {
					return val.first(key.index);
				}

				DualReal getFirst(const Dual& val, const DualTag& tag) const {
					return getFirst(val, getKey(tag));
				}
			};

		}
	}
}