#if !defined FROZEN_STRING_MAKE_HPP_INCLUDED
#define      FROZEN_STRING_MAKE_HPP_INCLUDED

#include <cstddef>

namespace frozen {

using std::size_t;

// forward decleration
template<class T, size_t N>
class basic_string;

template<class T, size_t N>
inline constexpr basic_string<T, N> make_string(T const (&str)[N])
{
    return {str};
}

template<class T, size_t N>
inline constexpr basic_string<T, N> make(T const (&str)[N])
{
    return {str};
}

} // namespace frozen

#endif    // FROZEN_STRING_MAKE_HPP_INCLUDED
