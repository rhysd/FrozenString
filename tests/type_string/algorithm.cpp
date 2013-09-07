#include "../../frozen/meta/string.hpp"
#include "../util.hpp"

using namespace frozen::meta;

IS_SAME(push_back<S("hoge"), '!'>, S("hoge!"));
IS_SAME(add_newline<S("hoge")>, S("hoge\n"));
IS_SAME(push_front<S("hoge"), '?'>, S("?hoge"));
IS_SAME(cons<char, '?', S("hoge")>, S("?hoge"));
IS_SAME(pop_front<S("hoge")>, S("oge"));

#include <iostream>
int main()
{
    std::cout << "OK\n";
    return 0;
}
