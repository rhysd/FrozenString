#if !defined FROZEN_STRING_DETAIL_DUMP_STRING_HPP_INCLUDED
#define      FROZEN_STRING_DETAIL_DUMP_STRING_HPP_INCLUDED

#include <cstddef>
#include <iostream>
#include "./util.hpp"

namespace frozen {

using std::size_t;

// forward declaration
template<class Char, size_t N>
class basic_string;

namespace detail {

    template<class Char, bool = detail::is_wide_char<Char>::value>
    struct dumper;

    template<class Char>
    struct dumper<Char, true>{
        static const Char nul = static_cast<Char>('\0');
        template<size_t N, class OStream = std::wostream>
        static void dump(basic_string<Char, N> const& s, OStream& os = std::wcerr)
        {
            for(auto const& c : s){
              if(c==nul){
                  os << L"\\0";
              }else{
                  os << c;
              }
            }
            os << std::endl;
        }
    };

    template<>
    struct dumper<char, false>{
        static const char nul = '\0';
        template<size_t N, class OStream = std::ostream>
        static void dump(basic_string<char, N> const& s, OStream& os = std::cerr)
        {
            for(auto const& c : s){
              if(c==nul){
                  os << "\\0";
              }else{
                  os << c;
              }
            }
            os << std::endl;
        }
    };

    template<class Char, size_t N>
    void dump(basic_string<Char, N> const& s)
    {
        detail::dumper<Char>::dump(s);
    }

    template<class Char, size_t N, class OStream>
    void dump(basic_string<Char, N> const& s, OStream &os)
    {
        detail::dumper<Char>::dump(s, os);
    }

} // namespace detail


} // namespace frozen

#endif    // FROZEN_STRING_DETAIL_DUMP_STRING_HPP_INCLUDED
