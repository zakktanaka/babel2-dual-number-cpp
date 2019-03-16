#include <pch.h>
#include <babel/math/dual.hpp>
#include <babel/math/utility/type_traits.hpp>

using namespace babel::math::type_traits;
using Dual  = babel::math::Dual<double>;
using DDual = babel::math::Dual<Dual>;

TEST(TypeTraits, Test) {

	{nullptr_t_if_convertible<int,   double> n = nullptr; }
	{nullptr_t_if_convertible<int&,  double> n = nullptr; }
	{nullptr_t_if_convertible<int&&, double> n = nullptr; }

	{nullptr_t_if_convertible<const int,   double> n = nullptr; }
	{nullptr_t_if_convertible<const int&,  double> n = nullptr; }
	{nullptr_t_if_convertible<const int&&, double> n = nullptr; }

	{nullptr_t_if_convertible<double, Dual> n = nullptr; }
	{nullptr_t_if_convertible<int,    Dual> n = nullptr; }

	// compile error
	//{nullptr_t_if_convertible<int,    DDual> n = nullptr; }
	//{nullptr_t_if_convertible<double, DDual> n = nullptr; }
	{nullptr_t_if_convertible<Dual,   DDual> n = nullptr; }

	{Dual s{ int(1)   }; }
	{Dual s{ float(1) }; }
	{Dual s{ long(1)  }; }

	{DDual s{ int(1)   }; EXPECT_EQ(1, s.real().real()); }
	{DDual s{ float(1) }; EXPECT_EQ(1, s.real().real()); }
	{DDual s{ long(1)  }; EXPECT_EQ(1, s.real().real()); }
	{DDual s{ Dual{1}  }; EXPECT_EQ(1, s.real().real()); }
}