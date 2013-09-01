#if !defined FROZEN_DETAIL_UTIL_HPP_INCLUDED
#define      FROZEN_DETAIL_UTIL_HPP_INCLUDED

#include "../type_traits_aliases.hpp"

namespace frozen {
namespace detail {

extern void *enabler;

template<class T, class U, class... Args>
struct is_one_of
    : alias::conditional<
          std::is_same<T, U>::value,
          std::true_type,
          is_one_of<T, Args...>
      >
{};

template<class T, class U>
struct is_one_of<T, U>
    : alias::is_same<T, U>
{};


template<class CharT, bool = is_one_of<CharT, char, wchar_t, char16_t, char32_t>::value>
struct check_char {
    static bool const value = false;
};

template<class CharT>
struct check_char<CharT, true>{
  typedef CharT type;
  static bool const value = true;
};

template<class CharT, bool = is_one_of<CharT, wchar_t, char16_t, char32_t>::value>
struct is_wide_char : std::integral_constant<bool, false>
{};

template<class CharT>
struct is_wide_char<CharT, true> : std::integral_constant<bool, true>
{};

template<class T, class U>
inline constexpr
T pow(T base, U exp) noexcept
{
    return exp == 0 ? 1 : base * pow(base, exp-1);
}

template<class T>
inline constexpr
T abs(T t) noexcept
{
    return t > 0 ? t : -t;
}

} // namespace frozen
} // namespace detail

#endif    // FROZEN_DETAIL_UTIL_HPP_INCLUDED
