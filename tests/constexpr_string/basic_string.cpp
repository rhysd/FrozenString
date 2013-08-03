#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "../util.hpp"

#include "../../immutable_string/string.hpp"

using namespace istring;

int main()
{
    constexpr string<6> s1 = "aiueo";
    constexpr string<5> s2({'p', 'o', 'y', 'o', '\0'});
    STATIC_ASSERT((s1.size() == s2.size()+1));

    ::setlocale(LC_ALL, "");
    constexpr auto s3 = make(L"ほげ");
    STATIC_ASSERT((s3 == L"ほげ"));

    STATIC_ASSERT((make("hoge") == make("hoge\0\0\0")));
    STATIC_ASSERT((make("hoge") == "hoge\0\0\0"));
    STATIC_ASSERT(("hoge" == make("hoge\0\0\0")));
    STATIC_ASSERT((make("hoge") == make("hoge\0huga")));

    STATIC_ASSERT((s1 + s2 == s1 + s2));
    STATIC_ASSERT((s1 + s2 == "aiueopoyo"));
    STATIC_ASSERT((s2 + '\n' == "poyo\n"));
    STATIC_ASSERT(('_' + s2 == "_poyo"));
    STATIC_ASSERT((make("poyo\0\0\0") + '_' == "poyo_"));
    STATIC_ASSERT(("aiueopoyo" == s1 + s2));
    STATIC_ASSERT((s2 + "payo" == "poyopayo"));
    STATIC_ASSERT(("payo" + s2 == "payopoyo"));
    STATIC_ASSERT((s1 + s2 != s2 + s1));
    STATIC_ASSERT((s1 + "payo" != s2 + s1));

    std::stringstream ss;
    ss << make("test for output operator");
    assert(ss.str() == "test for output operator");

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

    constexpr auto s4 = s3;
    STATIC_ASSERT((s4 == s3));

    constexpr string<10> s5('a');
    STATIC_ASSERT((s5 == "aaaaaaaaa"));

    STATIC_ASSERT((make("aaaaaa").size() == 6));
    STATIC_ASSERT((make("aaaa\0\0\0").size() == 4));
    STATIC_ASSERT((make("").size() == 0));
    STATIC_ASSERT((string<5>{{'p', 'o', 'y', 'o'}}.size() == 4));


    // STATIC_ASSERT((123.45e10_istr == "123.45e10"));

    std::cout << make("OK\n");
    return 0;
}

