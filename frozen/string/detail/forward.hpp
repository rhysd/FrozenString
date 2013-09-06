#if !defined FROZEN_STRING_DETAIL_FORWARD_HPP_INCLUDED
#define      FROZEN_STRING_DETAIL_FORWARD_HPP_INCLUDED

#include "../../type_traits_aliases.hpp"

namespace frozen {
namespace detail {

    template <class T>
    inline constexpr T &&forward( alias::remove_reference<T> &t) noexcept
    {
        return std::move(t);
    }

    template <class T>
    T &&forward( alias::remove_reference<T> &&) = delete;

} // namespace detail
} // namespace frozen

#endif    // FROZEN_STRING_DETAIL_FORWARD_HPP_INCLUDED
