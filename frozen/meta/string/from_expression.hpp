#if !defined FROZEN_META_STRING_FROM_EXPRESSION_HPP_INCLUDED
#define      FROZEN_META_STRING_FROM_EXPRESSION_HPP_INCLUDED

#include <type_traits>

#include <boost/preprocessor/stringize.hpp>

#include "./from_literals.hpp"

#define FROZEN_FROM_NUMERIC_EXPRESSION_WITH_CHECK(lit, val) \
  std::enable_if<std::is_arithmetic<typename std::decay<decltype(val)>::type>::value, FROZEN_FROM_STRING_LITERAL(lit)>::type
#define FROZEN_FROM_NUMERIC_EXPR(lit) \
  FROZEN_FROM_NUMERIC_EXPRESSION_WITH_CHECK(BOOST_PP_STRINGIZE(lit), lit)

#endif    // FROZEN_META_STRING_FROM_EXPRESSION_HPP_INCLUDED

