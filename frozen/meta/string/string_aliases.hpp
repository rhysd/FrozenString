#if !defined FROZEN_META_STRING_STRING_ALIASES_HPP_INCLUDED
#define      FROZEN_META_STRING_STRING_ALIASES_HPP_INCLUDED

#include "./basic_string.hpp"

namespace frozen {
namespace type {

template<char... Chars>
using string = basic_string<char, Chars...>;

template<wchar_t... Chars>
using wstring = basic_string<wchar_t, Chars...>;

template<char16_t... Chars>
using u16string = basic_string<char16_t, Chars...>;

template<char32_t... Chars>
using u32string = basic_string<char32_t, Chars...>;

} // namespace type
} // namespace frozen

#endif    // FROZEN_META_STRING_STRING_ALIASES_HPP_INCLUDED
