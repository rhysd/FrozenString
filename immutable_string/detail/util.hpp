#if !defined ISTRING_DETAIL_UTIL_HPP_INCLUDED
#define      ISTRING_DETAIL_UTIL_HPP_INCLUDED

#include <type_traits>

namespace istring {
namespace detail {

extern void *enabler;

template<class T, class U, class... Args>
struct is_one_of : is_one_of<T, Args...>
{};

template<class T, class... Args>
struct is_one_of<T, T, Args...> : std::true_type
{};

template<class T, class U>
struct is_one_of<T, U> : std::false_type
{};

template<class CharT, bool = is_one_of<CharT, char, wchar_t, char16_t, char32_t>::value>
struct is_char {
    static bool const value = false;
};

template<class CharT>
struct is_char<CharT, true>{
  typedef CharT type;
  static bool const value = true;
};

template<class T, class U>
inline constexpr
T pow(T base, U exp)
{
    return exp == 0 ? 1 : base * pow(base, exp-1);
}

} // namespace istring
} // namespace detail

#endif    // ISTRING_DETAIL_UTIL_HPP_INCLUDED
