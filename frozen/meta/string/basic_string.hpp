#if !defined FROZEN_META_STRING_BASIC_STRING_HPP_INCLUDED
#define      FROZEN_META_STRING_BASIC_STRING_HPP_INCLUDED

#include "../../string/basic_string.hpp"

#include <cstddef>
#include <array>
#include <iostream>
#include <type_traits>
#include <string>

namespace frozen {
namespace meta {

using std::size_t;

template< class CharT, CharT... Chars >
struct basic_string{
    typedef CharT char_type;
    typedef basic_string<CharT, Chars...> type;

    static const CharT value[sizeof...(Chars)+1];
    static const std::array<CharT, sizeof...(Chars)+1> array;
    static const frozen::basic_string<CharT, sizeof...(Chars)+1> frozen;
    static std::string to_std_string()
    {
        return value;
    }
};

template< class CharT, CharT... Chars >
const CharT basic_string<CharT, Chars...>::value[sizeof...(Chars)+1] = {Chars..., static_cast<CharT>('\0')};

template< class CharT, CharT... Chars >
std::array<CharT, sizeof...(Chars)+1> const basic_string<CharT, Chars...>::array = {{Chars..., static_cast<CharT>('\0')}};

template< class CharT, CharT... Chars >
frozen::basic_string<CharT, sizeof...(Chars)+1> const basic_string<CharT, Chars...>::frozen = {{{Chars..., static_cast<CharT>('\0')}}};


} // namespace meta
} // namespace frozen

#endif    // FROZEN_META_STRING_BASIC_STRING_HPP_INCLUDED
