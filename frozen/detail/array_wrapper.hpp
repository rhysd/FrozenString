#if !defined FROZEN_DETAIL_ARRAY_WRAPPER_HPP_INCLUDED
#define      FROZEN_DETAIL_ARRAY_WRAPPER_HPP_INCLUDED

#include <cstddef>

namespace frozen {
namespace detail {

    using std::size_t;

    // aggregate to take braced-initializer list in ctor
    template<class Char, size_t N>
    struct array_wrapper{
        Char data[N==0 ? 1 : N];

        constexpr Char operator[](size_t idx) const
        {
            return data[idx];
        }

        constexpr size_t size() const
        {
            return N;
        }
    };

} // namespace detail
} // namespace frozen

#endif    // FROZEN_DETAIL_ARRAY_WRAPPER_HPP_INCLUDED
