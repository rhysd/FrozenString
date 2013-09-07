#if !defined FROZEN_META_STRING_FROM_STRING_LITERAL_HPP_INCLUDED
#define      FROZEN_META_STRING_FROM_STRING_LITERAL_HPP_INCLUDED

#include <type_traits>

#include "./basic_string.hpp"
#include "./algorithm.hpp"

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/config/limits.hpp>

namespace frozen {
namespace meta {
namespace detail {

    template<class T>
    constexpr T min(T a, T b)
    {
        return a < b ? a : b;
    }

    template<char... Chars>
    auto operator"" _frozen_detail_ftypestr_litral_for_frozen_from_numeric_literal()
        -> basic_string<char, Chars...>
    {
        return {};
    }

} // namespace detail

} // namespace meta
} // namespace frozen


#define FROZEN_FROM_STRING_LITERAL(lit) FROZEN_FROM_STRING_LITERAL_I(lit)
#define FROZEN_FROM_STRING_LITERAL_I(lit) \
    frozen::meta::remove_trailing_nuls< \
        sizeof(lit) / sizeof(*lit), \
        frozen::meta::basic_string< \
            std::decay<decltype(*lit)>::type, \
            BOOST_PP_ENUM(BOOST_PP_LIMIT_REPEAT, FROZEN_FROM_STRING_LITERAL_M, lit) \
        > \
    >
#define FROZEN_FROM_STRING_LITERAL_M(z, i, lit) lit[frozen::meta::detail::min((size_t)i, sizeof(lit) / sizeof(*lit) - 1)]

using frozen::meta::detail::operator"" _frozen_detail_ftypestr_litral_for_frozen_from_numeric_literal;
#define FROZEN_FROM_NUMERIC_LITERAL(lit) \
  std::decay<decltype(BOOST_PP_CAT(lit, _frozen_detail_ftypestr_litral_for_frozen_from_numeric_literal))>::type

#endif    // FROZEN_META_STRING_FROM_STRING_LITERAL_HPP_INCLUDED
