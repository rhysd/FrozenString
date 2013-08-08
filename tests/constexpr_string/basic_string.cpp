#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "../util.hpp"

#include "../../immutable_string/string.hpp"

using namespace istring;

int main()
{
    constexpr string<4> arr[] = {"a", "bb", "ccc"};
    (void) arr;
    constexpr string<7> s1 = "aiueo";
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
    STATIC_ASSERT((make("aaab\0\0") < make("aab")));
    STATIC_ASSERT((make("aab") < "aaba\0"));
    STATIC_ASSERT(("aab\0\0" < make("aaba")));
    STATIC_ASSERT_NOT((make("\0") < make("")));

    STATIC_ASSERT_NOT((s1 > s1));
    STATIC_ASSERT((make("aab") > make("aaab")));
    STATIC_ASSERT((make("aaba") > "aab"));
    STATIC_ASSERT(("aaba" > make("aab")));
    STATIC_ASSERT_NOT((make("") > make("")));
    STATIC_ASSERT((make("aab\0\0") > make("aaab")));
    STATIC_ASSERT((make("aaba") > "aab\0"));
    STATIC_ASSERT((make("aaba\0\0") > "aab\0"));
    STATIC_ASSERT(("aaba\0" > make("aab")));
    STATIC_ASSERT(("aaba" > make("aab\0\0")));
    STATIC_ASSERT_NOT((make("\0") > make("")));

    constexpr auto s4 = s3;
    STATIC_ASSERT((s4 == s3));

    STATIC_ASSERT((s1 + s2 + "hoge" == "aiueopoyohoge"));
    STATIC_ASSERT((s1 + "kakikukeko" + s2 == "aiueokakikukekopoyo"));

    constexpr string<10> s5('a');
    STATIC_ASSERT((s5 == "aaaaaaaaa"));

    STATIC_ASSERT((make("aaaaaa").size() == 6));
    STATIC_ASSERT((make("aaaa\0\0\0").size() == 4));
    STATIC_ASSERT((make("").size() == 0));
    STATIC_ASSERT((string<5>{{'p', 'o', 'y', 'o'}}.size() == 4));

    STATIC_ASSERT((make("aa\0\0\0\0\0\0") + "bb" == "aabb"));
    STATIC_ASSERT(("aabb" == make("aa\0\0\0\0\0\0") + "bb"));
    STATIC_ASSERT((make("aabb") == make("aa\0\0\0\0\0\0") + "bb"));

    STATIC_ASSERT((to_basic_string<char>(42) == make("42")));
    STATIC_ASSERT((to_basic_string<char>(-423) == make("-423")));

    STATIC_ASSERT((make("Today is ") + 8 + '/' + 5 == "Today is 8/5"));
    STATIC_ASSERT((make("My progress is ") + 0 == "My progress is 0"));

    STATIC_ASSERT((10000 + make(" errors occur") == "10000 errors occur"));
    STATIC_ASSERT((0 + make("") == "0"));

    STATIC_ASSERT((basic_string<char, 0>::len == 1));
    STATIC_ASSERT((basic_string<char, 0>{""} == ""));

    // make json at compile-time from config
    static size_t constexpr random_tree_depth = 4;
    static size_t constexpr population_size = 100;
    static size_t constexpr mutation_percent = 5;
    static size_t constexpr crossover_percent = 50;
    auto constexpr json = empty_str +
                  '{' +
                      "\"random_tree_depth\" : " + random_tree_depth + ',' +
                      "\"population_size\" : " + population_size + ',' +
                      "\"mutation_percent\" : " + mutation_percent + ',' +
                      "\"crossover_percent\" : " + crossover_percent + ',' +
                  '}';
    STATIC_ASSERT((json == "{\"random_tree_depth\" : 4,\"population_size\" : 100,\"mutation_percent\" : 5,\"crossover_percent\" : 50,}"));

    STATIC_ASSERT((detail::digits10_of(100.123) == 11));
    STATIC_ASSERT((detail::digits10_of(0.123) == 9));
    // should be equal finally
    STATIC_ASSERT((to_basic_string<char>(123.45) != make("123.45")));

    std::cout << make("OK\n");
    return 0;
}

