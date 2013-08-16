#if !defined ISTRING_TEST_UTIL_HPP_INCLUDED
#define      ISTRING_TEST_UTIL_HPP_INCLUDED

#define STATIC_ASSERT(expr) static_assert(expr, #expr)
#define STATIC_ASSERT_NOT(expr) static_assert(!(expr), #expr)

namespace test_frozen{
template<class T>
constexpr T is_constexpr_impl(T x) throw(int)
{
  return x;
}
}

#define IS_CONSTEXPR(EXPR) noexcept(test_frozen::is_constexpr_impl(EXPR))

#endif    // ISTRING_TEST_UTIL_HPP_INCLUDED
