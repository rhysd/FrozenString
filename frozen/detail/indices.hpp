#if !defined FROZEN_DETAIL_INDICES_HPP_INCLUDED
#define      FROZEN_DETAIL_INDICES_HPP_INCLUDED

#include <cstddef>
#include <type_traits>

namespace frozen {
namespace detail {

    using std::size_t;

    template< size_t... Indices >
    struct indices{
        static constexpr size_t value[sizeof...(Indices)] = {Indices...};
    };

    template<class IndicesType, size_t Next>
    struct make_indices_next;

    template<size_t... Indices, size_t Next>
    struct make_indices_next<indices<Indices...>, Next> {
        typedef indices<Indices..., (Indices + Next)...> type;
    };

    template<class IndicesType, size_t Next, size_t Tail>
    struct make_indices_next2;

    template<size_t... Indices, size_t Next, size_t Tail>
    struct make_indices_next2<indices<Indices...>, Next, Tail> {
        typedef indices<Indices..., (Indices + Next)..., Tail> type;
    };

    template<size_t First, size_t Step, std::size_t N, class = void>
    struct make_indices_impl;

    template<size_t First, size_t Step, std::size_t N>
    struct make_indices_impl<
        First,
        Step,
        N,
        typename std::enable_if<(N == 0)>::type
    > {
        typedef indices<> type;
    };

    template<size_t First, size_t Step, std::size_t N>
    struct make_indices_impl<
        First,
        Step,
        N,
        typename std::enable_if<(N == 1)>::type
    > {
        typedef indices<First> type;
    };

    template<size_t First, size_t Step, std::size_t N>
    struct make_indices_impl<
        First,
        Step,
        N,
        typename std::enable_if<(N > 1 && N % 2 == 0)>::type
    >
        : detail::make_indices_next<
            typename detail::make_indices_impl<First, Step, N / 2>::type,
            First + N / 2 * Step
        >
    {};

    template<size_t First, size_t Step, std::size_t N>
    struct make_indices_impl<
        First,
        Step,
        N,
        typename std::enable_if<(N > 1 && N % 2 == 1)>::type
    >
        : detail::make_indices_next2<
            typename detail::make_indices_impl<First, Step, N / 2>::type,
            First + N / 2 * Step,
            First + (N - 1) * Step
        >
    {};

    template<size_t First, size_t Last, size_t Step = 1>
    struct make_indices_
        : detail::make_indices_impl<
            First,
            Step,
            ((Last - First) + (Step - 1)) / Step
        >
    {};

    template < size_t Start, size_t Last, size_t Step = 1 >
    using make_indices = typename make_indices_< Start, Last, Step >::type;

} // namespace detail
} // namespace frozen

#endif    // FROZEN_DETAIL_INDICES_HPP_INCLUDED
