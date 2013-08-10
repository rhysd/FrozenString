#if !defined FROZEN_ALIASES_HPP_INCLUDED
#define      FROZEN_ALIASES_HPP_INCLUDED

#include <cstddef>

#include "./basic_string.hpp"

namespace frozen {

using std::size_t;

template<size_t N>
using string = basic_string<char, N>;

template<size_t N>
using wstring = basic_string<wchar_t, N>;

template<size_t N>
using u16string = basic_string<char16_t, N>;

template<size_t N>
using u32string = basic_string<char32_t, N>;

} // namespace frozen


#endif    // FROZEN_ALIASES_HPP_INCLUDED
