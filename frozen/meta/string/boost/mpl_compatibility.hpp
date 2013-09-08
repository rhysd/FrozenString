#if !defined FROZEN_META_STRING_BOOST_MPL_COMPATIBILITY_HPP_INCLUDED
#define      FROZEN_META_STRING_BOOST_MPL_COMPATIBILITY_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>

namespace frozen {
namespace meta {

template< class CharT, CharT... Chars >
struct basic_string;

struct string_tag;
struct string_iterator_tag;

} // namespace meta
} // namespace frozen

namespace boost {
namespace mpl {

template<class Sequence>
struct sequence_tag;

template<class CharT, CharT... Chars>
struct sequence_tag<frozen::meta::basic_string<CharT, Chars...>>{
    using type = frozen::meta::string_tag;
};

template<class Tag>
struct size_impl;

template<>
struct size_impl<frozen::meta::string_tag>{
    template<class String>
    struct apply;

    template<class CharT, CharT... Chars>
    struct apply<frozen::meta::basic_string<CharT, Chars...>>
        : mpl::size_t<sizeof...(Chars)>
    {};
};


} // namespace mpl
} // namespace boost

#endif    // FROZEN_META_STRING_BOOST_MPL_COMPATIBILITY_HPP_INCLUDED
