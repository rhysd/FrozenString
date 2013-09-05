#if !defined FROZEN_TYPE_FROM_STRING_LITERAL_HPP_INCLUDED
#define      FROZEN_TYPE_FROM_STRING_LITERAL_HPP_INCLUDED

#include <type_traits>

#include "./basic_string.hpp"

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/config/limits.hpp>

#define FROZEN_FROM_STRING_LITERAL(lit) FROZEN_FROM_STRING_LITERAL_I(lit)
#define FROZEN_FROM_STRING_LITERAL_I(lit) \
    remove_trailing_null_chars< \
        sizeof(lit) / sizeof(*lit), \
        frozen::type::basic_string< \
            std::decay<decltype(*lit)>::type, \
            BOOST_PP_ENUM(BOOST_PP_LIMIT_REPEAT, FROZEN_FROM_STRING_LITERAL_M, lit) \
        > \
    >
#define FROZEN_FROM_STRING_LITERAL_M(z, i, lit) lit[min((size_t)i, sizeof(lit) / sizeof(*lit) - 1)]

#endif    // FROZEN_TYPE_FROM_STRING_LITERAL_HPP_INCLUDED
