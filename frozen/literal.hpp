#if !defined FROZEN_LITERALS_HPP_INCLUDED
#define      FROZEN_LITERALS_HPP_INCLUDED

#include <cstddef>

#include "./detail/indices.hpp"
#include "./detail/digits.hpp"
#include "./detail/strlen.hpp"
#include "./detail/macros.hpp"
#include "./basic_string.hpp"




namespace frozen {

using std::size_t;

namespace detail {

    struct operator_literal_fstr_impl{
        size_t const size;

        constexpr operator_literal_fstr_impl(size_t s) : size(s) {}

        template<class Char, size_t... Indices>
        constexpr
        basic_string<Char, sizeof...(Indices)>
        operator()(Char const* str, indices<Indices...>) const
        {
            return {{ Indices < size ? str[Indices] : static_cast<Char>('\0')... }};
        }
    };

} // namespace detail

inline constexpr
basic_string<char, detail::float_max_digits10<double>::value>
operator"" _fstr(char const* cstr)
{
    return detail::operator_literal_fstr_impl{detail::strlen(cstr, detail::float_max_digits10<double>::value)}(cstr, detail::make_indices<0, detail::float_max_digits10<double>::value>());
}

inline constexpr
basic_string<char, FROZEN_STRING_LITERALS_MAX_LENGTH>
operator"" _fstr(char const* str, size_t const size)
{
    return detail::operator_literal_fstr_impl{size}(str, detail::make_indices<0, FROZEN_STRING_LITERALS_MAX_LENGTH>());
}

inline constexpr
basic_string<wchar_t, FROZEN_STRING_LITERALS_MAX_LENGTH>
operator"" _fstr(wchar_t const* str, size_t const size)
{
    return detail::operator_literal_fstr_impl{size}(str, detail::make_indices<0, FROZEN_STRING_LITERALS_MAX_LENGTH>());
}

inline constexpr
basic_string<char16_t, FROZEN_STRING_LITERALS_MAX_LENGTH>
operator"" _fstr(char16_t const* str, size_t const size)
{
    return detail::operator_literal_fstr_impl{size}(str, detail::make_indices<0, FROZEN_STRING_LITERALS_MAX_LENGTH>());
}

inline constexpr
basic_string<char32_t, FROZEN_STRING_LITERALS_MAX_LENGTH>
operator"" _fstr(char32_t const* str, size_t const size)
{
    return detail::operator_literal_fstr_impl{size}(str, detail::make_indices<0, FROZEN_STRING_LITERALS_MAX_LENGTH>());
}

inline constexpr
basic_string<char, 2>
operator"" _fstr(char c)
{
    return {{c, '\0'}};
}

inline constexpr
basic_string<wchar_t, 2>
operator"" _fstr(wchar_t c)
{
    return {{c, L'\0'}};
}

inline constexpr
basic_string<char16_t, 2>
operator"" _fstr(char16_t c)
{
    return {{c, u'\0'}};
}

inline constexpr
basic_string<char32_t, 2>
operator"" _fstr(char32_t c)
{
    return {{c, U'\0'}};
}

} // namespace frozen

#endif    // FROZEN_LITERALS_HPP_INCLUDED
