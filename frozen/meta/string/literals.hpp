#if !defined FROZEN_META_STRING_LITERALS_HPP_INCLUDED
#define      FROZEN_META_STRING_LITERALS_HPP_INCLUDED

#include "./basic_string.hpp"

#include <type_traits>

namespace frozen {
namespace type {

template<char... Chars>
auto operator"" _ftypestr()
    -> basic_string<char, Chars...>
{
    return {};
}

} // namespace type
} // namespace frozen

#endif    // FROZEN_META_STRING_LITERALS_HPP_INCLUDED
