#if !defined FROZEN_STRING_EMPTY_HPP_INCLUDED
#define      FROZEN_STRING_EMPTY_HPP_INCLUDED

#include <cstddef>

#include "./basic_string.hpp"

namespace frozen {

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
static constexpr auto empty_u16str = detail::empty_basic_str<char16_t>(u"");
static constexpr auto empty_u32str = detail::empty_basic_str<char32_t>(U"");


} // namespace frozen

#endif    // FROZEN_STRING_EMPTY_HPP_INCLUDED
