#if !defined ISTRING_MAKE_HPP_INCLUDED
#define      ISTRING_MAKE_HPP_INCLUDED

#include <cstddef>

namespace istring {

using std::size_t;

// decleration
template<class T, size_t N>
class basic_string;

template<class T, size_t N>
inline constexpr basic_string<T, N> make(T const (&str)[N])
{
    return {str};
}

} // namespace sstring

#endif    // ISTRING_MAKE_HPP_INCLUDED
