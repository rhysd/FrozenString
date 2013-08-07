#if !defined ISTRING_EMPTY_HPP_INCLUDED
#define      ISTRING_EMPTY_HPP_INCLUDED

#include <cstddef>

#include "./basic_string.hpp"

namespace istring {

using std::size_t;

namespace detail {

template<class C>
inline constexpr
basic_string<C, 1> empty_basic_str(C const (&s)[1])
{
    return {s};
}

} // namespace detail

static constexpr auto empty_str = detail::empty_basic_str<char>("");
static constexpr auto empty_wstr = detail::empty_basic_str<wchar_t>(L"");
static constexpr auto empty_w16str = detail::empty_basic_str<char16_t>(u"");
static constexpr auto empty_w32str = detail::empty_basic_str<char32_t>(U"");


} // namespace istring

#endif    // ISTRING_EMPTY_HPP_INCLUDED
