#if !defined FROZEN_TYPE_FROM_STRING_LITERAL_HPP_INCLUDED
#define      FROZEN_TYPE_FROM_STRING_LITERAL_HPP_INCLUDED

#include <type_traits>

#include "./basic_string.hpp"
#include "./algorithm.hpp"

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/config/limits.hpp>

namespace frozen {
namespace type {
namespace detail {

    template<class T>
    constexpr T min(T a, T b)
    {
        return a < b ? a : b;
    }

} // namespace detail
} // namespace type
} // namespace frozen


#define FROZEN_FROM_STRING_LITERAL(lit) FROZEN_FROM_STRING_LITERAL_I(lit)
#define FROZEN_FROM_STRING_LITERAL_I(lit) \
    frozen::type::remove_trailing_nuls< \
        sizeof(lit) / sizeof(*lit), \
        frozen::type::basic_string< \
            std::decay<decltype(*lit)>::type, \
            BOOST_PP_ENUM(BOOST_PP_LIMIT_REPEAT, FROZEN_FROM_STRING_LITERAL_M, lit) \
        > \
    >
#define FROZEN_FROM_STRING_LITERAL_M(z, i, lit) lit[frozen::type::detail::min((size_t)i, sizeof(lit) / sizeof(*lit) - 1)]

#endif    // FROZEN_TYPE_FROM_STRING_LITERAL_HPP_INCLUDED
