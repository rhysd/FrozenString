#if !defined FROZEN_META_STRING_LITERALS_HPP_INCLUDED
#define      FROZEN_META_STRING_LITERALS_HPP_INCLUDED

#include "./basic_string.hpp"

#include <type_traits>

namespace frozen {
namespace meta {

template<char... Chars>
auto operator"" _ftypestr()
    -> basic_string<char, Chars...>
{
    return {};
}

} // namespace meta
} // namespace frozen

#endif    // FROZEN_META_STRING_LITERALS_HPP_INCLUDED
