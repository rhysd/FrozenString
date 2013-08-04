#if !defined ISTRING_DETAIL_FORWARD_HPP_INCLUDED
#define      ISTRING_DETAIL_FORWARD_HPP_INCLUDED

#include <type_traits>

namespace istring {
namespace detail {

    template <class T>
    inline constexpr T &&forward( typename std::remove_reference<T>::type &t) noexcept
    {
        return std::move(t);
    }

    template <class T>
    T &&forward( typename std::remove_reference<T>::type &&) = delete;

} // namespace detail
} // namespace istring

#endif    // ISTRING_DETAIL_FORWARD_HPP_INCLUDED
