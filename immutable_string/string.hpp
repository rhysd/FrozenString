#if !defined ISTRING_STRING_HPP_INCLUDED
#define      ISTRING_STRING_HPP_INCLUDED

#include <cstddef>

#include "./basic_string.hpp"
#include "./make.hpp"
#include "./to_string.hpp"

namespace istring {

using std::size_t;

template<size_t N>
using string = basic_string<char, N>;

template<size_t N>
using wstring = basic_string<wchar_t, N>;

template<size_t N>
using w16string = basic_string<char16_t, N>;

template<size_t N>
using w32string = basic_string<char32_t, N>;

} // namespace istring


#endif    // ISTRING_STRING_HPP_INCLUDED
