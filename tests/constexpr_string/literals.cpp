#include <iostream>

#include "../util.hpp"

#include "../../frozen/string.hpp"

using namespace frozen;

int main()
{
    STATIC_ASSERT((123.45_fstr == "123.45"));
    STATIC_ASSERT((123.45e10_fstr == "123.45e10"));
    STATIC_ASSERT((123_fstr == "123"));

    STATIC_ASSERT(("aiueo"_fstr == make_string("aiueo")));
    STATIC_ASSERT((L"あいうえお"_fstr == make_string(L"あいうえお")));
    STATIC_ASSERT((u"ｲﾇｩ…"_fstr == make_string(u"ｲﾇｩ…")));
    STATIC_ASSERT((U"＾ω＾"_fstr == make_string(U"＾ω＾")));

    STATIC_ASSERT(('_'_fstr == make_string("_")));
    STATIC_ASSERT((L'-'_fstr == make_string(L"-")));
    STATIC_ASSERT((u'ω'_fstr == make_string(u"ω")));
    STATIC_ASSERT((U'ω'_fstr == make_string(U"ω")));

    std::cout << make_string("OK\n");
    return 0;
}
