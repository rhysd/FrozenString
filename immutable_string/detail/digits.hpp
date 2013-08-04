#if !defined ISTRING_DETAIL_DIGITS_HPP_INCLUDED
#define      ISTRING_DETAIL_DIGITS_HPP_INCLUDED

#include <cstddef>
#include <cmath>
#include <limits>
#include <type_traits>

namespace istring {

using std::size_t;

namespace detail {

    template< class Int,
              class = typename std::enable_if<
                            std::is_integral<Int>::value
                      >::type
            >
    inline constexpr
    size_t int_digits10()
    {
        return std::numeric_limits<Int>::digits10 + 1;
    }

    template< class Int,
              class = typename std::enable_if<
                            std::is_integral<Int>::value
                      >::type
            >
    inline constexpr
    size_t digits10_of(Int i)
    {
        return std::log10(std::abs(i))+1;
    }

    static constexpr size_t size_t_max_digits10
        = std::numeric_limits<size_t>::digits10 + 1;

    static constexpr size_t int_max_digits10
        = std::numeric_limits<long long int>::digits10 + 1;

    static constexpr size_t double_max_digits10
        = std::numeric_limits<double>::max_digits10 + 8;

    

}

}

#endif    // ISTRING_DETAIL_DIGITS_HPP_INCLUDED
