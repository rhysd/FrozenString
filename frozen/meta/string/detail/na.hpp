#if !defined FROZEN_META_STRING_DETAIL_NA_HPP_INCLUDED
#define      FROZEN_META_STRING_DETAIL_NA_HPP_INCLUDED

#include <cstddef>

namespace frozen {
namespace meta {
namespace detail {

struct na{
  typedef na type;
  static const std::size_t value = 0;
};

} // namespace detail
} // namespace meta
} // namespace frozen

#endif    // FROZEN_META_STRING_DETAIL_NA_HPP_INCLUDED
