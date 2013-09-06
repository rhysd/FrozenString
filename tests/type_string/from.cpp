#include "../../frozen/type/string.hpp"
#include "../util.hpp"

using namespace frozen::type;

SAME_TYPE(S("3.14"), FROZEN_FROM_NUMERIC_LITERAL(3.14));
SAME_TYPE(S("42"), FROZEN_FROM_NUMERIC_LITERAL(42));
SAME_TYPE(S("-3.14"), FROZEN_FROM_NUMERIC_EXPR(-3.14));
SAME_TYPE(S("-42"), FROZEN_FROM_NUMERIC_EXPR(-42));
SAME_TYPE(S("1+2"), FROZEN_FROM_NUMERIC_EXPR(1+2));

#include <iostream>
int main()
{
    std::cout << "OK\n";
    return 0;
}
