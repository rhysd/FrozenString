#include <iostream>

#include "../util.hpp"

#include "../../immutable_string/string.hpp"
#include "../../immutable_string/literals.hpp"

using namespace istring;
using istring::operator "" _istr;

int main()
{
    STATIC_ASSERT((123.45_istr == "123.45"));
    STATIC_ASSERT((123_istr == "123"));

    std::cout << make("OK\n");
    return 0;
}
