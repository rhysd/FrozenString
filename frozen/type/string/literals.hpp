#include "./basic_string.hpp"

#include <type_traits>

namespace frozen {
namespace type {

template<char... Chars>
auto operator"" _ftypestr()
    -> basic_string<char, Chars...>
{
    return {};
}

} // namespace type
} // namespace frozen
