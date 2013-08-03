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

template<class CharT>
struct is_char{
  static_assert(is_one_of<CharT, char, wchar_t, char16_t, char32_t>::value,
                "type of element is not character type.");
  typedef CharT type;
  static bool const value = true;
};

// template<class CharT>
// struct is_char{
//   static const bool value = false;
// };
//
// template<>
// struct is_char<char>{
//   static const bool value = true;
//   typedef char type;
// };
//
// template<>
// struct is_char<wchar_t>{
//   static const bool value = true;
//   typedef wchar_t type;
// };
//
// template<>
// struct is_char<char16_t>{
//   static const bool value = true;
//   typedef char16_t type;
// };
//
// template<>
// struct is_char<char32_t>{
//   static const bool value = true;
//   typedef char32_t type;
// };

} // namespace istring
} // namespace detail

#endif    // ISTRING_DETAIL_UTIL_HPP_INCLUDED
