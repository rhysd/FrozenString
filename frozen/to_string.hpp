#if !defined FROZEN_TO_STRING_HPP_INCLUDED
#define      FROZEN_TO_STRING_HPP_INCLUDED

#include <cstddef>
#include <cmath>
#include <utility>
#include <type_traits>

#include "./detail/indices.hpp"
#include "./detail/digits.hpp"
#include "./detail/forward.hpp"
#include "./detail/util.hpp"

namespace frozen {

using std::size_t;

// forward declaration
template<class Char, size_t N>
class basic_string;

namespace detail {

    template<class Char, class Int, size_t... Indices>
    inline constexpr
    basic_string<Char, detail::int_max_digits10<Int>()>
    to_basic_string_integral(Int i, size_t digits, indices<Indices...>)
    {
        return {{
                    static_cast<Char>( i < 0 ?
                        (
                            Indices == 0 ? '-' :
                            Indices-1 < digits ? detail::digits10_at(-i, digits-(Indices-1)-1) + '0' : '\0'
                        ) :
                        (
                            Indices < digits ? detail::digits10_at(i, digits-Indices-1) + '0' : '\0'
                        )
                    )...
            }};
    }

} // namespace detail

template< class Char, class T,
          class = typename std::enable_if<
                      std::is_integral<
                          typename std::decay<T>::type
                      >::value
                  >::type >
inline constexpr
basic_string<Char, detail::int_max_digits10<T>()> to_basic_string(T t)
{
    return detail::to_basic_string_integral<Char>(
                t,
                detail::digits10_of(t),
                detail::make_indices<0, detail::int_max_digits10<T>()>()
            );
}


namespace detail {

    template<class Char, class Float, size_t... Indices>
    inline constexpr
    basic_string<Char, detail::float_max_digits10<Float>::value>
    to_basic_string_float(Float f, size_t digit_int, size_t digit, indices<Indices...>)
    {
        return {{ static_cast<Char>( f < 0 ?
                    ( Indices == 0 ? '-' :
                        Indices - 1 < digit_int ? '0' + detail::float_integer_part_digits10_of(f, digit_int-1 - (Indices-1)) :
                        Indices - 1 == digit_int ? '.' :
                        Indices  < digit ? '0' + detail::float_fraction_part_digits10_of(f, (Indices - 2) - digit_int) : '\0'
                    ) :
                    ( Indices < digit_int ? '0' + detail::float_integer_part_digits10_of(f, (digit_int-1) - Indices) :
                        Indices == digit_int ? '.' :
                        Indices+1 < digit ? '0' + detail::float_fraction_part_digits10_of(f, (Indices-1) - digit_int) : '\0'
                    )
                )... }};
    }

} // namespace detail

template<class Char, class T,
         class = typename std::enable_if<
                     std::is_floating_point<
                         typename std::decay<T>::type
                     >::value
                 >::type>
inline constexpr
basic_string<Char, detail::float_max_digits10<T>::value> to_basic_string(T t)
{
    return detail::to_basic_string_float<Char>(
                t,
                detail::float_digits10_of_integer_part(t),
                detail::digits10_of(t),
                detail::make_indices<0, detail::float_max_digits10<T>::value>()
           );
}

template<class T>
inline constexpr
auto to_string(T t)
    -> decltype( to_basic_string<char>(std::declval<T>()) )
{
    return to_basic_string<char>(t);
}

template<class T>
inline constexpr
auto to_wstring(T t)
    -> decltype( to_basic_string<wchar_t>(std::declval<T>()) )
{
    return to_basic_string<wchar_t>(t);
}

template<class T>
inline constexpr
auto to_u16string(T t)
    -> decltype( to_basic_string<char16_t>(std::declval<T>()) )
{
    return to_basic_string<char16_t>(t);
}

template<class T>
inline constexpr
auto to_u32string(T t)
    -> decltype( to_basic_string<char32_t>(std::declval<T>()) )
{
    return to_basic_string<char32_t>(t);
}

} // namespace frozen

#endif    // FROZEN_TO_STRING_HPP_INCLUDED
