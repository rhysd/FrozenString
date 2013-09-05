#include <iostream>

#include "../util.hpp"

#include "../../frozen/string.hpp"

using namespace frozen;

int main()
{
    SASSERT(123.45_fstr == "123.45");
    SASSERT(123.45e10_fstr == "123.45e10");
    SASSERT(123_fstr == "123");

    SASSERT("aiueo"_fstr == make_string("aiueo"));
    SASSERT(L"あいうえお"_fstr == make_string(L"あいうえお"));
    SASSERT(u"ｲﾇｩ…"_fstr == make_string(u"ｲﾇｩ…"));
    SASSERT(U"＾ω＾"_fstr == make_string(U"＾ω＾"));

    SASSERT('_'_fstr == make_string("_"));
    SASSERT(L'-'_fstr == make_string(L"-"));
    SASSERT(u'ω'_fstr == make_string(u"ω"));
    SASSERT(U'ω'_fstr == make_string(U"ω"));

    std::cout << make_string("OK\n");
    return 0;
}
