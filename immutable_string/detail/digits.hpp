#if !defined ISTRING_DETAIL_DIGITS_HPP_INCLUDED
#define      ISTRING_DETAIL_DIGITS_HPP_INCLUDED

#include <cstddef>
#include <limits>

namespace istring {

using std::size_t;

namespace detail {

    static constexpr size_t size_t_max_digits10
        = std::numeric_limits<size_t>::digits10 + 1;

    static constexpr size_t int_max_digits10
        = std::numeric_limits<int>::digits10 + 1;

    static constexpr size_t double_max_digits10
        = std::numeric_limits<double>::max_digits10 + 8;

}

}

#endif    // ISTRING_DETAIL_DIGITS_HPP_INCLUDED
