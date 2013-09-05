#if !defined ISTRING_TEST_UTIL_HPP_INCLUDED
#define      ISTRING_TEST_UTIL_HPP_INCLUDED

#include "../frozen/string.hpp"
#include "../frozen/type/string.hpp"

#define SASSERT(...) FROZEN_STATIC_ASSERT(__VA_ARGS__)
#define SASSERT_NOT(...) FROZEN_STATIC_ASSERT_NOT(__VA_ARGS__)

namespace test_frozen{
template<class T>
constexpr T is_constexpr_impl(T x) throw(int)
{
  return x;
}
}

#define IS_CONSTEXPR_IMPL(EXPR) noexcept(test_frozen::is_constexpr_impl(EXPR))
#define IS_CONSTEXPR(...) IS_CONSTEXPR_IMPL((__VA_ARGS__))

#endif    // ISTRING_TEST_UTIL_HPP_INCLUDED
