#if !defined FROZEN_META_STRING_ALGORITHM_HPP_INCLUDED
#define      FROZEN_META_STRING_ALGORITHM_HPP_INCLUDED

#include "./basic_string.hpp"

namespace frozen {
namespace meta {

// concat {{{
template< class T, class U >
struct concat_;

template< class CharT, CharT... C1, CharT... C2 >
struct concat_< basic_string<CharT, C1...>, basic_string<CharT, C2...> >
  : basic_string<CharT, C1..., C2...>
{};

template< class Str1, class Str2 >
using concat = typename concat_<Str1, Str2>::type;

// }}}


// push_front {{{
template<class S, typename S::char_type Char>
struct push_front_;

template< class CharT, CharT Char, CharT... Chars >
struct push_front_< basic_string<CharT, Chars...>, Char >
  : basic_string<CharT, Char, Chars...>
{};

template<class S, typename S::char_type C>
using push_front = typename push_front_<S, C>::type;

template<class CharT, CharT C, class S>
using cons = typename push_front_<S, C>::type;
// }}}


// push_front_t {{{
template<class S, class C>
struct push_front_t_;

template< class CharT, class Char, CharT... Chars >
struct push_front_t_< basic_string<CharT, Chars...>, Char >
  : basic_string<CharT, Char::value, Chars...>
{};

template<class S, class C>
using push_front_t = typename push_front_t_<S, C>::type;

template<class C, class S>
using cons_t = typename push_front_t_<S, C>::type;
// }}}


// push_back {{{
template<class S, typename S::char_type Char>
struct push_back_;

template< class CharT, CharT Char, CharT... Chars >
struct push_back_< basic_string<CharT, Chars...>, Char >
  : basic_string<CharT, Chars..., Char>
{};

template<class S, typename S::char_type C>
using push_back = typename push_back_<S, C>::type;
// }}}


// push_back_t {{{
template<class S, class C>
struct push_back_t_;

template< class CharT, class Char, CharT... Chars >
struct push_back_t_< basic_string<CharT, Chars...>, Char >
  : basic_string<CharT, Chars..., Char::value>
{};

template<class S, class C>
using push_back_t = typename push_back_t_<S, C>::type;
// }}}


// add_newline {{{
template<class S>
struct add_newline_ : push_back_< S, static_cast<typename S::char_type>('\n') >
{};

template<class Str>
using add_newline = typename add_newline_<Str>::type;
// }}}


// pop_front {{{
template<class S>
struct pop_front_;

template<class CharT, CharT Head, CharT... Tail>
struct pop_front_< basic_string<CharT, Head, Tail...> >
  : basic_string<CharT, Tail...>
{};

template<class S>
using pop_front = typename pop_front_<S>::type;
// }}}


// front {{{
template<class S>
struct front_;

template<class CharT, CharT Head, CharT... Tail>
struct front_< basic_string<CharT, Head, Tail...> >{
    using type = CharT;
    static CharT const value = Head;
};

template<class S>
using front = typename front_<S>::type;
// }}}


// remove_trailing_nuls {{{
template<size_t N, class T>
struct remove_trailing_nuls_;

template<class CharT, CharT Head, CharT... Tail>
struct remove_trailing_nuls_<1, basic_string<CharT, Head, Tail...>>
  : basic_string<CharT>
{};

template<class CharT, size_t N, CharT Head, CharT... Tail>
struct remove_trailing_nuls_<N, basic_string<CharT, Head, Tail...>>
  : push_front<typename remove_trailing_nuls_<N-1, basic_string<CharT, Tail...>>::type, Head>
{};

template<size_t N, class T>
using remove_trailing_nuls = typename remove_trailing_nuls_<N, T>::type;

// }}}

} // namespace meta
} // namespace frozen

#endif    // FROZEN_META_STRING_ALGORITHM_HPP_INCLUDED
