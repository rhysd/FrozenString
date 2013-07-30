#include <iostream>
#include <algorithm>

#include "../util.hpp"

#include "../../immutable_string/string.hpp"

using namespace istring;

int main()
{
    ::setlocale(LC_ALL, "");
    constexpr string<6> s1 = "aiueo";
    constexpr string<5> s2({'p', 'o', 'y', 'o', '\0'});
    STATIC_ASSERT((s1.size() == s2.size()+1));

    constexpr auto s3 = make(L"ほげ");
    STATIC_ASSERT((s3 == L"ほげ"));

    STATIC_ASSERT((s1 + s2 == s1 + s2));
    STATIC_ASSERT((s1 + s2 == "aiueopoyo"));
    STATIC_ASSERT((s2 + '\n' == "poyo\n"));
    STATIC_ASSERT(('_' + s2 == "_poyo"));
    STATIC_ASSERT(("aiueopoyo" == s1 + s2));
    STATIC_ASSERT((s2 + "payo" == "poyopayo"));
    STATIC_ASSERT(("payo" + s2 == "payopoyo"));
    STATIC_ASSERT((s1 + s2 != s2 + s1));
    STATIC_ASSERT((s1 + "payo" != s2 + s1));

    std::cout << make("test of output operator\n");

    STATIC_ASSERT_NOT((s1 < s1));
    STATIC_ASSERT((make("aaab") < make("aab")));
    STATIC_ASSERT((make("aab") < "aaba"));
    STATIC_ASSERT(("aab" < make("aaba")));
    STATIC_ASSERT_NOT((make("") < make("")));

    STATIC_ASSERT_NOT((s1 > s1));
    STATIC_ASSERT((make("aab") > make("aaab")));
    STATIC_ASSERT((make("aaba") > "aab"));
    STATIC_ASSERT(("aaba" > make("aab")));
    STATIC_ASSERT_NOT((make("") > make("")));

    std::cout << make("OK\n");
    return 0;
}

