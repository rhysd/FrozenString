#if !defined ISTRING_DETAIL_INDICES_HPP_INCLUDED
#define      ISTRING_DETAIL_INDICES_HPP_INCLUDED

#include <cstddef>

namespace istring {
namespace detail {

    using std::size_t;

    template< size_t... Indices >
    struct indices{};

    template < size_t Start,
               size_t Last,
               size_t Step = 1,
               class Acc = indices<>,
               bool Finish = (Start>=Last) >
    struct make_indices_{
        typedef Acc type;
    };

    template < size_t Start,
               size_t Last,
               size_t Step,
               size_t... Indices >
    struct make_indices_< Start, Last, Step, indices<Indices...>, false >
             : make_indices_<Start+Step, Last, Step, indices<Indices..., Start>>
    {};

    template < size_t Start, size_t Last, size_t Step = 1 >
    using make_indices = typename make_indices_< Start, Last, Step >::type;

} // namespace detail
} // namespace istring

#endif    // ISTRING_DETAIL_INDICES_HPP_INCLUDED
