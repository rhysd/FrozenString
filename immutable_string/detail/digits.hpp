#if !defined ISTRING_DETAIL_DIGITS_HPP_INCLUDED
#define      ISTRING_DETAIL_DIGITS_HPP_INCLUDED

#include <cstddef>
#include <cmath>
#include <limits>
#include <type_traits>
#include <stdexcept>

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
    size_t int_max_digits10()
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
        return std::abs(i)<1 ? 1 : std::log10(std::abs(i))+1;
    }

    static constexpr size_t float_digits10_of_fractional_part = 6;

    template< class Float >
    inline constexpr
    size_t float_digits10_of_integer_part(Float f)
    {
        return std::abs(f)<1.0f ? 1 : std::log10(std::abs(f))+1;
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
        return float_digits10_of_integer_part(f) + float_digits10_of_fractional_part + 2;
    }

    template< class Int,
              class = typename std::enable_if<
                            std::is_integral<
                                typename std::decay<Int>::type
                            >::value
                      >::type
            >
    inline constexpr
    size_t digits10_at(Int i, size_t idx)
    {
        return static_cast<Int>(std::abs(i)) / static_cast<size_t>(detail::pow(10, idx)) % 10;
    }

    template< class Float,
              typename std::enable_if<
                  std::is_floating_point<
                      typename std::decay<Float>::type
                  >::value
              >::type*& = detail::enabler
            >
    struct float_max_digits10{
        static const size_t value =
            std::numeric_limits<Float>::max_exponent10 + float_digits10_of_fractional_part + 2;
    };

    template< class Float >
    inline constexpr
    size_t fmod10_base(Float f)
    {
        return f < 10.0 ? static_cast<size_t>(f) : detail::fmod10_base(f-10);
    }

    template< class Float >
    inline constexpr
    size_t fmod10_impl(Float f, size_t base)
    {
        // 2 because constexpr recursion limit is 512 and put the number of recursion in it at fmod10_base()
        return base < 2 ? fmod10_base(f) :
               f - detail::pow(10.0, base) < 0 ? detail::fmod10_impl(f, base - 2) :
               detail::fmod10_impl(f - detail::pow(10.0, base), base);
    }

    template< class Float >
    inline constexpr
    size_t fmod10(Float f)
    {
        return fmod10_impl(f, std::numeric_limits<Float>::max_exponent10 - 2);
    }

    template< class Float,
              typename std::enable_if<
                  std::is_floating_point<
                      typename std::decay<Float>::type
                  >::value
              >::type*& = detail::enabler
            >
    inline constexpr
    size_t float_integer_part_digits10_of_impl(Float f, size_t idx)
    {
        return f < std::numeric_limits<unsigned long long int>::max() ?
                       static_cast<unsigned long long int>(f) % 10 :
                       detail::fmod10(std::abs(f) / detail::pow(10.0, idx));
    }

    template< class Float,
              typename std::enable_if<
                  std::is_floating_point<
                      typename std::decay<Float>::type
                  >::value
              >::type*& = detail::enabler
            >
    inline constexpr
    size_t float_integer_part_digits10_of(Float f, size_t idx)
    {
        return float_integer_part_digits10_of_impl(std::abs(f) / detail::pow(10.0, idx), idx);
    }

    template< class Float,
              typename std::enable_if<
                  std::is_floating_point<
                      typename std::decay<Float>::type
                  >::value
              >::type*& = detail::enabler
            >
    inline constexpr
    size_t float_fraction_part_digits10_of(Float f, size_t digit)
    {
        return float_integer_part_digits10_of(f * detail::pow(10.0, digit+1), 0);
    }
}

}

#endif    // ISTRING_DETAIL_DIGITS_HPP_INCLUDED
