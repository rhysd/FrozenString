#if !defined FROZEN_TYPE_BASIC_STRING_HPP_INCLUDED
#define      FROZEN_TYPE_BASIC_STRING_HPP_INCLUDED

#include <cstddef>
#include <array>
#include <iostream>
#include <type_traits>

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/config/limits.hpp>

namespace frozen {
namespace type {

using std::size_t;

template< class CharT, CharT... Chars >
struct basic_string{

    static const CharT value[sizeof...(Chars)+1];

    constexpr std::array<CharT, sizeof...(Chars)+1>
    to_array() const
    {
        return {{Chars..., '\0'}};
    }
};

template< class CharT, CharT... Chars >
const CharT basic_string<CharT, Chars...>::value[sizeof...(Chars)+1] = {Chars..., '\0'};

} // namespace type
} // namespace frozen

#endif    // FROZEN_TYPE_BASIC_STRING_HPP_INCLUDED
