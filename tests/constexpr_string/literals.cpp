#include <iostream>

#include "../util.hpp"

#include "../../frozen/string.hpp"
#include "../../frozen/literals.hpp"

using namespace frozen;
using frozen::operator "" _istr;

int main()
{
    STATIC_ASSERT((123.45_istr == "123.45"));
    STATIC_ASSERT((123_istr == "123"));

    std::cout << make("OK\n");
    return 0;
}
