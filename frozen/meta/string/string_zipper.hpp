#if !defined FROZEN_META_STRING_STRING_ZIPPER_HPP_INCLUDED
#define      FROZEN_META_STRING_STRING_ZIPPER_HPP_INCLUDED

#include "./basic_string.hpp"
#include "./operations.hpp"
#include "./detail/na.hpp"

namespace frozen {
namespace meta {
namespace zipper {

template<class L, class R>
struct string_zipper;

template<class CharT, CharT Prev, CharT Next, CharT... Left, CharT... Right>
struct string_zipper<basic_string<CharT, Prev, Left...>, basic_string<CharT, Next, Right...>>{
    using char_type = CharT;
    using left = basic_string<CharT, Left...>;
    using right = basic_string<CharT, Right...>;
    static const CharT before = Prev;
    static const CharT after = Next;
    using next = string_zipper<basic_string<CharT, Next, Prev, Left...>, basic_string<CharT, Right...>>;
    using prior = string_zipper<basic_string<CharT, Left...>, basic_string<CharT, Prev, Next, Right...>>;
};

template<class CharT, CharT Next, CharT... Right>
struct string_zipper<basic_string<CharT>, basic_string<CharT, Next, Right...>>{
    using char_type = CharT;
    using left = basic_string<CharT>;
    using right = basic_string<CharT, Next, Right...>;
    static const CharT after = Next;
    using next = string_zipper<basic_string<CharT, Next>, basic_string<CharT, Right...>>;
    using prior = detail::na;
};

template<class CharT, CharT Prev, CharT... Left>
struct string_zipper<basic_string<CharT, Prev, Left...>, basic_string<CharT>>{
    using char_type = CharT;
    using left = basic_string<CharT, Left...>;
    using right = basic_string<CharT>;
    static const CharT before = Prev;
    using next = detail::na;
    using prior = string_zipper<basic_string<CharT, Left...>, basic_string<CharT, Prev>>;
};

template<class CharT>
struct string_zipper<basic_string<CharT>, basic_string<CharT>>{
    using char_type = CharT;
    using left = basic_string<CharT>;
    using right = basic_string<CharT>;
    using next = detail::na;
    using prior = detail::na;
};

template<class Zipper>
struct is_begin;

template<class Left, class Right>
struct is_begin<string_zipper<Left, Right>> : empty<Left>
{};

template<class Zipper>
struct is_end;

template<class Left, class Right>
struct is_end<string_zipper<Left, Right>> : empty<Right>
{};


template<class String>
struct zipper_of{
    using type = string_zipper<basic_string<typename String::char_type>, String>;
};

template<class Zipper>
struct get{
    static const typename Zipper::char_type value = Zipper::before;
};

template<class Zipper, typename Zipper::char_type Char>
struct insert_after;

template<class CharT, class Left, CharT... RightChars, CharT Char>
struct insert_after<string_zipper<Left, basic_string<CharT, RightChars...>>, Char>{
    using type = string_zipper<Left, basic_string<CharT, Char, RightChars...>>;
};

template<class Zipper, typename Zipper::char_type Char>
struct insert_before;

template<class CharT, CharT... LeftChars, class Right, CharT Char>
struct insert_before<string_zipper<basic_string<CharT, LeftChars...>, Right>, Char>{
    using type = string_zipper<basic_string<CharT, Char, LeftChars...>, Right>;
};

template<class Zipper>
struct remove_after;

template<class CharT, class Left, CharT RHead, CharT... RightChars>
struct remove_after<string_zipper<Left, basic_string<CharT, RHead, RightChars...>>>{
    using type = string_zipper<Left, basic_string<CharT, RightChars...>>;
};

template<class Zipper>
struct remove_before;

template<class CharT, CharT LHead, CharT... LeftChars, class Right>
struct remove_before<string_zipper<basic_string<CharT, LHead, LeftChars...>, Right>>{
    using type = string_zipper<basic_string<CharT, LeftChars...>, Right>;
};

// TODO unimplemented (O(n))
template<class Zipper>
struct string_of;


} // namespace zipper
} // namespace meta
} // namespace frozen

#endif    // FROZEN_META_STRING_STRING_ZIPPER_HPP_INCLUDED
