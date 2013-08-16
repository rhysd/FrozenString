#if !defined FROZEN_DETAIL_STRLEN_HPP_INCLUDED
#define      FROZEN_DETAIL_STRLEN_HPP_INCLUDED

#include <utility>
#include <limits>
#include <stdexcept>
#include <cstddef>

namespace frozen {
namespace detail {

    using std::size_t;

    namespace impl {
        template<class String>
        inline constexpr
        size_t strlen_impl(String const& s, size_t idx_max, size_t idx)
        {
            return s[idx] == '\0' || idx >= idx_max ? 0 : 1 + strlen_impl(s, idx_max, idx+1);
        }
    } // namespace impl

    // @brief: s is null terminated.
    template<class String>
    inline constexpr
    size_t strlen(String const& s, size_t idx_max = std::numeric_limits<size_t>::max())
    {
        return impl::strlen_impl(s, idx_max, 0);
    }

} // namespace detail
} // namespace frozen

#endif    // FROZEN_DETAIL_STRLEN_HPP_INCLUDED
