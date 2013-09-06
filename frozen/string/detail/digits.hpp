#if !defined FROZEN_STRING_DETAIL_DIGITS_HPP_INCLUDED
#define      FROZEN_STRING_DETAIL_DIGITS_HPP_INCLUDED

#include <cstddef>
#include <limits>
#include <stdexcept>

#include "../../type_traits_aliases.hpp"
#include "./util.hpp"
#include "./log.hpp"

namespace frozen {

using std::size_t;

namespace detail {

    template< class Int,
              class = alias::enable_if<
                            std::is_integral<
                                alias::decay<Int>
                            >::value
                      >
            >
    inline constexpr
    size_t int_max_digits10() noexcept
    {
        return std::numeric_limits<Int>::digits10 + 1;
    }

    template< class Int,
              alias::enable_if<
                  std::is_integral<
                      alias::decay<Int>
                  >::value
              >*& = enabler
            >
    inline constexpr
    size_t digits10_of(Int i)
    {
        return detail::abs(i)<1 ? 1 : detail::log10(detail::abs(i))+1;
    }

    static constexpr size_t float_digits10_of_fractional_part = 6;

    template< class Float >
    inline constexpr
    size_t float_digits10_of_integer_part(Float f)
    {
        return detail::abs(f)<1.0f ? 1 : detail::log10(detail::abs(f))+1;
    }

    template< class Float,
              alias::enable_if<
                  std::is_floating_point<
                      alias::decay<Float>
                  >::value
              >*& = detail::enabler
            >
    inline constexpr
    size_t digits10_of(Float f)
    {
        // 2 means a space for '-' and '.'
        return float_digits10_of_integer_part(f) + float_digits10_of_fractional_part + 2;
    }

    template< class Int,
              class = alias::enable_if<
                            std::is_integral<
                                alias::decay<Int>
                            >::value
                      >
            >
    inline constexpr
    size_t digits10_at(Int i, size_t idx) noexcept
    {
        return static_cast<Int>(detail::abs(i)) / static_cast<size_t>(detail::pow(10, idx)) % 10;
    }

    template< class Float,
              alias::enable_if<
                  std::is_floating_point<
                      alias::decay<Float>
                  >::value
              >*& = detail::enabler
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
              alias::enable_if<
                  std::is_floating_point<
                      alias::decay<Float>
                  >::value
              >*& = detail::enabler
            >
    inline constexpr
    size_t float_integer_part_digits10_of_impl(Float f, size_t idx)
    {
        return f < std::numeric_limits<unsigned long long int>::max() ?
                       static_cast<unsigned long long int>(f) % 10 :
                       detail::fmod10(detail::abs(f) / detail::pow(10.0, idx));
    }

    template< class Float,
              alias::enable_if<
                  std::is_floating_point<
                      alias::decay<Float>
                  >::value
              >*& = detail::enabler
            >
    inline constexpr
    size_t float_integer_part_digits10_of(Float f, size_t idx)
    {
        return float_integer_part_digits10_of_impl(detail::abs(f) / detail::pow(10.0, idx), idx);
    }

    template< class Float,
              alias::enable_if<
                  std::is_floating_point<
                      alias::decay<Float>
                  >::value
              >*& = detail::enabler
            >
    inline constexpr
    size_t float_fraction_part_digits10_of(Float f, size_t digit)
    {
        return float_integer_part_digits10_of(f * detail::pow(10.0, digit+1), 0);
    }
}

} // namespace frozen

#endif    // FROZEN_STRING_DETAIL_DIGITS_HPP_INCLUDED
