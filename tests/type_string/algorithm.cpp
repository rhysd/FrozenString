#include "../../frozen/meta/string.hpp"
#include "../util.hpp"

using namespace frozen::type;

SASSERT(std::is_same<push_back<S("hoge"), '!'>, S("hoge!")>::value);
SASSERT(std::is_same<add_newline<S("hoge")>, S("hoge\n")>::value);
SASSERT(std::is_same<push_front<S("hoge"), '?'>, S("?hoge")>::value);
SASSERT(std::is_same<cons<char, '?', S("hoge")>, S("?hoge")>::value);
SASSERT(std::is_same<pop_front<S("hoge")>, S("oge")>::value);

#include <iostream>
int main()
{
    std::cout << "OK\n";
    return 0;
}
