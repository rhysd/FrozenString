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
    STATIC_ASSERT(("aiueopoyo" == s1 + s2));
    STATIC_ASSERT((s2 + "payo" == "poyopayo"));
    STATIC_ASSERT(("payo" + s2 == "payopoyo"));
    STATIC_ASSERT((s1 + s2 != s2 + s1));
    STATIC_ASSERT((s1 + "payo" != s2 + s1));

    std::cout << "OK\n";
    return 0;
}

