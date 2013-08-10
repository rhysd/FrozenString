#if !defined FROZEN_DETAIL_UTIL_HPP_INCLUDED
#define      FROZEN_DETAIL_UTIL_HPP_INCLUDED

#include <type_traits>

namespace frozen {
namespace detail {

extern void *enabler;

template<class T, class U, class... Args>
struct is_one_of
    : std::conditional<
          std::is_same<T, U>::value,
          std::true_type,
          is_one_of<T, Args...>
      >::type
{};

template<class T, class U>
struct is_one_of<T, U>
    : std::is_same<T, U>::type
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

template<class T, class U>
inline constexpr
T pow(T base, U exp)
{
    return exp == 0 ? 1 : base * pow(base, exp-1);
}

} // namespace frozen
} // namespace detail

#endif    // FROZEN_DETAIL_UTIL_HPP_INCLUDED
