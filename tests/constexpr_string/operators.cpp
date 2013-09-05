#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "../util.hpp"

#include "../../frozen/string.hpp"

using namespace frozen;

int main()
{
    constexpr string<4> arr[] = {"a", "bb", "ccc"};
    (void) arr;
    constexpr string<7> s1 = "aiueo";
    constexpr string<5> s2{{{'p', 'o', 'y', 'o', '\0'}}};
    SASSERT(s1.size() == s2.size()+1);

    ::setlocale(LC_ALL, "");
    constexpr auto s3 = make_string(L"ほげ");
    SASSERT(s3 == L"ほげ");

    SASSERT(make_string("hoge") == make_string("hoge\0\0\0"));
    SASSERT(make_string("hoge") == "hoge\0\0\0");
    SASSERT("hoge" == make_string("hoge\0\0\0"));
    SASSERT(make_string("hoge") == make_string("hoge\0huga"));
    SASSERT(make_string(L"a") == L"a");

    SASSERT(s1 + s2 == s1 + s2);
    SASSERT(s1 + s2 == "aiueopoyo");
    SASSERT(s2 + '\n' == "poyo\n");
    SASSERT('_' + s2 == "_poyo");
    SASSERT(make_string("poyo\0\0\0") + '_' == "poyo_");
    SASSERT("aiueopoyo" == s1 + s2);
    SASSERT(s2 + "payo" == "poyopayo");
    SASSERT("payo" + s2 == "payopoyo");
    SASSERT(s1 + s2 != s2 + s1);
    SASSERT(s1 + "payo" != s2 + s1);
    SASSERT(L'_' + make_string(L"poyo") == L"_poyo");
    SASSERT(make_string(L"poyo") + L'_' == L"poyo_");

    std::stringstream ss;
    ss << make_string("test for output operator");
    assert(ss.str() == "test for output operator");

    std::wstringstream wss;
    wss << make_string(L"test for wide output operator");
    assert(wss.str() == L"test for wide output operator");

    SASSERT_NOT(s1 < s1);
    SASSERT(make_string("aaab") < make_string("aab"));
    SASSERT(make_string("aab") < "aaba");
    SASSERT("aab" < make_string("aaba"));
    SASSERT_NOT(make_string("") < make_string(""));
    SASSERT(make_string("aaab\0\0") < make_string("aab"));
    SASSERT(make_string("aab") < "aaba\0");
    SASSERT("aab\0\0" < make_string("aaba"));
    SASSERT_NOT(make_string("\0") < make_string(""));

    SASSERT_NOT(s1 > s1);
    SASSERT(make_string("aab") > make_string("aaab"));
    SASSERT(make_string("aaba") > "aab");
    SASSERT("aaba" > make_string("aab"));
    SASSERT_NOT(make_string("") > make_string(""));
    SASSERT(make_string("aab\0\0") > make_string("aaab"));
    SASSERT(make_string("aaba") > "aab\0");
    SASSERT(make_string("aaba\0\0") > "aab\0");
    SASSERT("aaba\0" > make_string("aab"));
    SASSERT("aaba" > make_string("aab\0\0"));
    SASSERT_NOT(make_string("\0") > make_string(""));

    constexpr auto s4 = s3;
    SASSERT(s4 == s3);

    SASSERT(s1 + s2 + "hoge" == "aiueopoyohoge");
    SASSERT(s1 + "kakikukeko" + s2 == "aiueokakikukekopoyo");

    SASSERT(make_string("aaaaaa").size() == 6);
    SASSERT(make_string("aaaa\0\0\0").size() == 4);
    SASSERT(make_string("").size() == 0);
    SASSERT(string<5>{{{'p', 'o', 'y', 'o'}}}.size() == 4);

    SASSERT(make_string("aa\0\0\0\0\0\0") + "bb" == "aabb");
    SASSERT("aabb" == make_string("aa\0\0\0\0\0\0") + "bb");
    SASSERT(make_string("aabb") == make_string("aa\0\0\0\0\0\0") + "bb");

    SASSERT(make_string("Today is ") + 8 + '/' + 5 == "Today is 8/5");
    SASSERT(make_string("My progress is ") + 0 == "My progress is 0");
    SASSERT(make_string(L"Today is ") + 8 + '/' + 5 == L"Today is 8/5");

    SASSERT(10000 + make_string(" errors occur") == "10000 errors occur");
    SASSERT(0 + make_string("") == "0");

    SASSERT(basic_string<char, 0>::len == 1);
    SASSERT(basic_string<char, 0>{""} == "");

    SASSERT(3.14159 + make_string(" is pi") == "3.14159 is pi");
    SASSERT(-3.14159 + make_string("") == "-3.14159");
    SASSERT(make_string("pi is ") + 3.14159 == "pi is 3.14159");
    SASSERT(make_string("") + -3.14159 == "-3.14159");

    // make_string json at compile-time from config
    static size_t constexpr random_tree_depth = 4;
    static size_t constexpr population_size = 100;
    static float constexpr mutation_percent = 5.0f;
    static float constexpr crossover_percent = 50.0f;
    auto constexpr json = empty_str +
                  '{' +
                      "\"random_tree_depth\" : " + random_tree_depth + ',' +
                      "\"population_size\" : " + population_size + ',' +
                      "\"mutation_percent\" : " + mutation_percent + ',' +
                      "\"crossover_percent\" : " + crossover_percent + ',' +
                  '}';
    SASSERT(json == "{\"random_tree_depth\" : 4,\"population_size\" : 100,\"mutation_percent\" : 5,\"crossover_percent\" : 50,}");

    std::cout << make_string("OK\n");
    return 0;
}

