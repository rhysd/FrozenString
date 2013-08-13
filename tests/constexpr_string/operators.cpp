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
    STATIC_ASSERT((s1.size() == s2.size()+1));

    ::setlocale(LC_ALL, "");
    constexpr auto s3 = make_string(L"ほげ");
    STATIC_ASSERT((s3 == L"ほげ"));

    STATIC_ASSERT((make_string("hoge") == make_string("hoge\0\0\0")));
    STATIC_ASSERT((make_string("hoge") == "hoge\0\0\0"));
    STATIC_ASSERT(("hoge" == make_string("hoge\0\0\0")));
    STATIC_ASSERT((make_string("hoge") == make_string("hoge\0huga")));
    STATIC_ASSERT((make_string(L"a") == L"a"));

    STATIC_ASSERT((s1 + s2 == s1 + s2));
    STATIC_ASSERT((s1 + s2 == "aiueopoyo"));
    STATIC_ASSERT((s2 + '\n' == "poyo\n"));
    STATIC_ASSERT(('_' + s2 == "_poyo"));
    STATIC_ASSERT((make_string("poyo\0\0\0") + '_' == "poyo_"));
    STATIC_ASSERT(("aiueopoyo" == s1 + s2));
    STATIC_ASSERT((s2 + "payo" == "poyopayo"));
    STATIC_ASSERT(("payo" + s2 == "payopoyo"));
    STATIC_ASSERT((s1 + s2 != s2 + s1));
    STATIC_ASSERT((s1 + "payo" != s2 + s1));
    STATIC_ASSERT((L'_' + make_string(L"poyo") == L"_poyo"));
    STATIC_ASSERT((make_string(L"poyo") + L'_' == L"poyo_"));

    std::stringstream ss;
    ss << make_string("test for output operator");
    assert(ss.str() == "test for output operator");

    std::wstringstream wss;
    wss << make_string(L"test for wide output operator");
    assert(wss.str() == L"test for wide output operator");

    STATIC_ASSERT_NOT((s1 < s1));
    STATIC_ASSERT((make_string("aaab") < make_string("aab")));
    STATIC_ASSERT((make_string("aab") < "aaba"));
    STATIC_ASSERT(("aab" < make_string("aaba")));
    STATIC_ASSERT_NOT((make_string("") < make_string("")));
    STATIC_ASSERT((make_string("aaab\0\0") < make_string("aab")));
    STATIC_ASSERT((make_string("aab") < "aaba\0"));
    STATIC_ASSERT(("aab\0\0" < make_string("aaba")));
    STATIC_ASSERT_NOT((make_string("\0") < make_string("")));

    STATIC_ASSERT_NOT((s1 > s1));
    STATIC_ASSERT((make_string("aab") > make_string("aaab")));
    STATIC_ASSERT((make_string("aaba") > "aab"));
    STATIC_ASSERT(("aaba" > make_string("aab")));
    STATIC_ASSERT_NOT((make_string("") > make_string("")));
    STATIC_ASSERT((make_string("aab\0\0") > make_string("aaab")));
    STATIC_ASSERT((make_string("aaba") > "aab\0"));
    STATIC_ASSERT((make_string("aaba\0\0") > "aab\0"));
    STATIC_ASSERT(("aaba\0" > make_string("aab")));
    STATIC_ASSERT(("aaba" > make_string("aab\0\0")));
    STATIC_ASSERT_NOT((make_string("\0") > make_string("")));

    constexpr auto s4 = s3;
    STATIC_ASSERT((s4 == s3));

    STATIC_ASSERT((s1 + s2 + "hoge" == "aiueopoyohoge"));
    STATIC_ASSERT((s1 + "kakikukeko" + s2 == "aiueokakikukekopoyo"));

    STATIC_ASSERT((make_string("aaaaaa").size() == 6));
    STATIC_ASSERT((make_string("aaaa\0\0\0").size() == 4));
    STATIC_ASSERT((make_string("").size() == 0));
    STATIC_ASSERT((string<5>{{{'p', 'o', 'y', 'o'}}}.size() == 4));

    STATIC_ASSERT((make_string("aa\0\0\0\0\0\0") + "bb" == "aabb"));
    STATIC_ASSERT(("aabb" == make_string("aa\0\0\0\0\0\0") + "bb"));
    STATIC_ASSERT((make_string("aabb") == make_string("aa\0\0\0\0\0\0") + "bb"));

    STATIC_ASSERT((make_string("Today is ") + 8 + '/' + 5 == "Today is 8/5"));
    STATIC_ASSERT((make_string("My progress is ") + 0 == "My progress is 0"));
    STATIC_ASSERT((make_string(L"Today is ") + 8 + '/' + 5 == L"Today is 8/5"));

    STATIC_ASSERT((10000 + make_string(" errors occur") == "10000 errors occur"));
    STATIC_ASSERT((0 + make_string("") == "0"));

    STATIC_ASSERT((basic_string<char, 0>::len == 1));
    STATIC_ASSERT((basic_string<char, 0>{""} == ""));

    STATIC_ASSERT((3.14159 + make_string(" is pi") == "3.141590 is pi"));
    STATIC_ASSERT((-3.14159 + make_string("") == "-3.141590"));
    STATIC_ASSERT((make_string("pi is ") + 3.14159 == "pi is 3.141590"));
    STATIC_ASSERT((make_string("") + -3.14159 == "-3.141590"));

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
    STATIC_ASSERT((json == "{\"random_tree_depth\" : 4,\"population_size\" : 100,\"mutation_percent\" : 5.000000,\"crossover_percent\" : 50.000000,}"));

    std::cout << make_string("OK\n");
    return 0;
}

