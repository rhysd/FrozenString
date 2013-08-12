#if !defined FROZEN_DETAIL_LOG_HPP_INCLUDED
#define      FROZEN_DETAIL_LOG_HPP_INCLUDED

#include <type_traits>
#include <cstddef>
#include <limits>
#ifdef __GLIBCXX__
#   include <cmath>
#endif

#include "./util.hpp"

namespace frozen {
namespace detail { 

    using std::size_t;

    namespace constants{
        static constexpr double e = 2.718281828459045;
    } // namespace constants

    template<class Num,
             class = typename std::enable_if<
                         std::is_floating_point<
                             typename std::decay<Num>::type
                         >::value
                     >::type
            >
    inline constexpr
    Num log_0_1_impl(Num n, size_t depth)
    {
        return (depth%2==0 ? -1 : 1) * detail::pow(n-1, depth) / depth +
                  (depth>=256 ? 0 : log_0_1_impl(n, depth+1));
    }

    template<class Num,
             class = typename std::enable_if<
                         std::is_floating_point<
                             typename std::decay<Num>::type
                         >::value
                     >::type
            >
    inline constexpr
    Num log_1_impl(Num n, double base)
    {
        return n < 1 ? n : 1 + log_1_impl(n/base, base);
    }

    template<class Num>
    inline constexpr
    Num log_1(Num n, double base)
    {
        return log_1_impl(n/base, base);
    }

    template<class Num,
             class Ret = typename std::conditional<
                             std::is_integral<
                                 typename std::decay<Num>::type
                             >::value,
                             double,
                             Num
                         >::type
            >
    inline constexpr
    Ret log(Num n)
    {
#ifdef __GLIBCXX__
        return std::log(n);
#else
        return n <= 0.0 ?         std::numeric_limits<Ret>::quiet_NaN() :
               0.0 < n && n<1.0 ? log_0_1_impl(static_cast<Ret>(n), 1) :
                                  log_1(static_cast<Ret>(n), constants::e);
#endif
    }

    template<class Num,
             class Ret = typename std::conditional<
                             std::is_integral<
                                 typename std::decay<Num>::type
                             >::value,
                             double,
                             Num
                         >::type
            >
    inline constexpr
    Ret log10(Num n)
    {
#ifdef __GLIBCXX__
        return std::log10(n);
#else
        return n <= 0.0 ?           std::numeric_limits<Ret>::quiet_NaN() :
               0.0 < n && n < 1.0 ? log_0_1_impl(static_cast<Ret>(n), 1) / log(10.0) :
                                    log_1(static_cast<Ret>(n), 10.0);
#endif
    }

} // namespace detail
} // namespace frozen

#endif    // FROZEN_DETAIL_LOG_HPP_INCLUDED
