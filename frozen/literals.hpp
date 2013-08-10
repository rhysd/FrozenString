#if !defined FROZEN_LITERALS_HPP_INCLUDED
#define      FROZEN_LITERALS_HPP_INCLUDED

#include <cstddef>

#include "./detail/indices.hpp"
#include "./detail/digits.hpp"
#include "./detail/strlen.hpp"
#include "./basic_string.hpp"


namespace frozen {

using std::size_t;

namespace detail {

    struct operator_istr_impl{
        size_t const size;

        constexpr operator_istr_impl(size_t s) : size(s) {}

        template<size_t... Indices>
        constexpr
        basic_string<char, detail::float_max_digits10<double>::value>
        operator()(char const* str, indices<Indices...>) const
        {
            return {{(Indices < size ? str[Indices] : '\0')...}};
        }
    };

} // namespace detail

inline constexpr
basic_string<char, detail::float_max_digits10<double>::value>
operator"" _istr(char const* cstr)
{
    return detail::operator_istr_impl{detail::strlen(cstr, detail::float_max_digits10<double>::value)}(cstr, detail::make_indices<0, detail::float_max_digits10<double>::value>());
}


} // namespace frozen

#endif    // FROZEN_LITERALS_HPP_INCLUDED
