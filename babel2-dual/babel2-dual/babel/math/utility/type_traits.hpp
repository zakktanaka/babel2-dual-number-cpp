#pragma once

#include <type_traits>

namespace babel {
	namespace math {
		namespace type_traits {

			template<typename From, typename To>
			using nullptr_t_if_convertible = typename std::enable_if<std::is_convertible<From, To>::value, std::nullptr_t>::type;

		}
	}
}