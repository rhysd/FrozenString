#if !defined FROZEN_TYPE_TO_STRING_HPP_INCLUDED
#define      FROZEN_TYPE_TO_STRING_HPP_INCLUDED

#include "basic_string.hpp"

namespace frozen {
namespace type {

namespace detail {

    template< class CharT,
            class Int,
            Int Value,
            class Acc = basic_string<CharT>,
            bool = (Value < 10) >
    struct to_string_from_integer;

    template< class CharT,
            class Int,
            Int Value,
            CharT... Chars >
    struct to_string_from_integer< CharT, Int, Value, basic_string<CharT, Chars...>, false >
            : to_string_from_integer< CharT, Int, Value / 10, basic_string< CharT, Value % 10 + '0', Chars... > >{};

    template< class CharT,
            class Int,
            Int Value,
            CharT... Chars >
    struct to_string_from_integer< CharT, Int, Value, basic_string<CharT, Chars...>, true >{
        typedef basic_string< CharT, Value + '0', Chars... > type;
    };

} // namespace detail

template<class CharT, class T, T Value>
struct to_basic_string;

template<class CharT, class Int, typename std::is_integral<Int>::type Value>
struct to_basic_string<CharT, Int, Value> : detail::to_string_from_integer<CharT, Int, Value>
{
    static_assert(std::is_integral<Int>::value, "");
};

template<class Int, Int Value>
using to_string = to_basic_string<char, Int, Value>;

template<class Int, Int Value>
using to_wstring = to_basic_string<wchar_t, Int, Value>;

template<class Int, Int Value>
using to_u16string = to_basic_string<char16_t, Int, Value>;

template<class Int, Int Value>
using to_u32string = to_basic_string<char32_t, Int, Value>;

} // namespace type
} // namespace frozen

#endif    // FROZEN_TYPE_TO_STRING_HPP_INCLUDED
