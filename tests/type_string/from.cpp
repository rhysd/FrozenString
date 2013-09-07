#include "../../frozen/meta/string.hpp"
#include "../util.hpp"

using namespace frozen::meta;

IS_SAME(S("3.14"), FROZEN_FROM_NUMERIC_LITERAL(3.14));
IS_SAME(S("42"), FROZEN_FROM_NUMERIC_LITERAL(42));
IS_SAME(S("-3.14"), FROZEN_FROM_NUMERIC_EXPR(-3.14));
IS_SAME(S("-42"), FROZEN_FROM_NUMERIC_EXPR(-42));
IS_SAME(S("1+2"), FROZEN_FROM_NUMERIC_EXPR(1+2));

#include <iostream>
int main()
{
    std::cout << "OK\n";
    return 0;
}
