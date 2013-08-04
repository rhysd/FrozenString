#if !defined ISTRING_TO_STRING_HPP_INCLUDED
#define      ISTRING_TO_STRING_HPP_INCLUDED

#include <cstddef>
#include <cmath>
#include <utility>
#include <type_traits>

#include "./detail/indices.hpp"
#include "./detail/digits.hpp"
#include "./detail/forward.hpp"

#include "./basic_string.hpp"

namespace istring {

using std::size_t;

namespace detail {

template<class Char, class Int, size_t... Indices>
inline constexpr
basic_string<Char, detail::int_digits10<Int>()>
to_basic_string_integral(Int i, size_t digits, indices<Indices...>)
{
    return {{
                ( static_cast<Char>( Indices <= digits  ? 
                        i / static_cast<int>(std::pow(10, digits - Indices)) % 10 + '0' : '\0')
                )...
           }};
}

} // namespace detail

template<class Char, class T, class = typename std::enable_if<std::is_integral<T>::value>::type>
inline constexpr
basic_string<Char, detail::int_digits10<T>()> to_basic_string(T t)
{
    return detail::to_basic_string_integral<Char>(
                t,
                static_cast<size_t>(std::log10(t)),
                detail::make_indices<0, detail::int_digits10<T>()>()
            );
}

} // namespace istring

#endif    // ISTRING_TO_STRING_HPP_INCLUDED
