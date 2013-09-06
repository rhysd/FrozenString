#if !defined FROZEN_TYPE_ALGORITHM_HPP_INCLUDED
#define      FROZEN_TYPE_ALGORITHM_HPP_INCLUDED

#include "./basic_string.hpp"

namespace frozen {
namespace type {

// concat {{{
template< class T, class U >
struct concat_;

template< class CharT, CharT... C1, CharT... C2 >
struct concat_< basic_string<CharT, C1...>, basic_string<CharT, C2...> >{
    typedef basic_string<CharT, C1..., C2...> type;
};

template< class Str1, class Str2 >
using concat = typename concat_<Str1, Str2>::type;

// }}}


// add_newline {{{
template<class T>
struct add_newline_;

template< class CharT, CharT... Chars >
struct add_newline_< basic_string<CharT, Chars...> >{
    typedef basic_string<CharT, Chars..., '\n'> type;
};

template<class Str>
using add_newline = typename add_newline_<Str>::type;

// }}}


// cons {{{
template<class CharT, CharT C, class T>
struct cons_;

template<class CharT, CharT C, CharT... Chars>
struct cons_<CharT, C, basic_string<CharT, Chars...>>{
    typedef basic_string<CharT, C, Chars...> type;
};

template<class CharT, CharT C, class T>
using cons = typename cons_<CharT, C, T>::type;

// }}}


// remove_trailing_nuls {{{
template<size_t N, class T>
struct remove_trailing_nuls_;

template<class CharT, CharT Head, CharT... Tail>
struct remove_trailing_nuls_<1, basic_string<CharT, Head, Tail...>>{
    typedef basic_string<CharT> type;
};

template<class CharT, size_t N, CharT Head, CharT... Tail>
struct remove_trailing_nuls_<N, basic_string<CharT, Head, Tail...>>{
    typedef cons<CharT, Head, typename remove_trailing_nuls_<N-1, basic_string<CharT, Tail...>>::type> type;
};

template<size_t N, class T>
using remove_trailing_nuls = typename remove_trailing_nuls_<N, T>::type;

// }}}



} // namespace type
} // namespace frozen

#endif    // FROZEN_TYPE_ALGORITHM_HPP_INCLUDED
