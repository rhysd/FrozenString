#if !defined ISTRING_DETAIL_DIGITS_HPP_INCLUDED
#define      ISTRING_DETAIL_DIGITS_HPP_INCLUDED

#include <cstddef>
#include <cmath>
#include <limits>
#include <type_traits>

#include "./util.hpp"

namespace istring {

using std::size_t;

namespace detail {

    template< class Int,
              class = typename std::enable_if<
                            std::is_integral<
                                typename std::decay<Int>::type
                            >::value
                      >::type
            >
    inline constexpr
    size_t int_digits10()
    {
        return std::numeric_limits<Int>::digits10 + 1;
    }

    // FIXME
    // constexpr std::log10() is a libstdc++ feature.
    // std::log10() in libc++ doesn't work in a constant expression.
    template< class Int,
              typename std::enable_if<
                  std::is_integral<
                      typename std::decay<Int>::type
                  >::value
              >::type*& = enabler
            >
    inline constexpr
    size_t digits10_of(Int i)
    {
        return i==0 ? 1 : std::log10(std::abs(i))+1;
    }

    static constexpr size_t digits10_of_fractional_part = 6;

    template< class Float >
    inline constexpr
    size_t digits10_of_integer_part(Float f)
    {
        return f==0.0f ? 1 : std::log10(std::abs(f))+1;
    }

    // FIXME
    // constexpr std::log10() is a libstdc++ feature.
    // std::log10() in libc++ doesn't work in a constant expression.
    template< class Float,
              typename std::enable_if<
                  std::is_floating_point<
                      typename std::decay<Float>::type
                  >::value
              >::type*& = detail::enabler
            >
    inline constexpr
    size_t digits10_of(Float f)
    {
        // 2 means a space for '-' and '.'
        return digits10_of_integer_part(f) + digits10_of_fractional_part + 2;
    }

    template< class Int,
              class = typename std::enable_if<
                            std::is_integral<Int>::value
                      >::type
            >
    inline constexpr
    size_t digits10_at(Int i, size_t idx)
    {
        return i / static_cast<int>(detail::pow(10, idx)) % 10;
    }

    template< class Float,
              class = typename std::enable_if<
                            std::is_floating_point<Float>::value
                      >::type
            >
    inline constexpr
    size_t float_digits10()
    {
        return std::numeric_limits<Float>::max_digits10 + 8;
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
