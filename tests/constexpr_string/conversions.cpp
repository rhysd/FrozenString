#include <string>
#include <cassert>

#include "../util.hpp"

#include "../../frozen/string.hpp"

using namespace frozen;

int main()
{
    SASSERT(to_basic_string<char>(42) == make_string("42"));
    SASSERT(to_basic_string<char>(-423) == make_string("-423"));

    SASSERT(detail::digits10_of(100.123) == 11);
    SASSERT(detail::digits10_of(0.123) == 9);

    SASSERT(detail::float_integer_part_digits10_of(456.123, 0) == 6);
    SASSERT(detail::float_integer_part_digits10_of(456.123, 1) == 5);
    SASSERT(detail::float_integer_part_digits10_of(456.123, 2) == 4);
    SASSERT(detail::float_integer_part_digits10_of(0.123, 0) == 0);
    SASSERT(detail::float_integer_part_digits10_of(-5.123, 0) == 5);
    SASSERT(detail::float_integer_part_digits10_of(1e10, 9) == 0);
    SASSERT(detail::float_integer_part_digits10_of(1e100, 9) == 0);
    SASSERT(detail::float_integer_part_digits10_of(45674567.123, 4) == 7);
    SASSERT(detail::float_integer_part_digits10_of(999999.0e100, 105) == 9);
    SASSERT(detail::float_fraction_part_digits10_of(456.123, 0) == 1);
    SASSERT(detail::float_fraction_part_digits10_of(456.123, 1) == 2);
    SASSERT(detail::float_fraction_part_digits10_of(456.123, 2) == 3);
    SASSERT(detail::float_fraction_part_digits10_of(-5.1234, 3) == 4);
    SASSERT(to_basic_string<char>(123.45) == make_string("123.45"));
    SASSERT(to_basic_string<char>(-123.45) == make_string("-123.45"));
    SASSERT(to_basic_string<char>(1.2345678e10) == make_string("12345678000"));
    SASSERT(to_basic_string<char>(-1.2345678e10) == make_string("-12345678000"));
    SASSERT(to_basic_string<char>(0.0) == make_string("0"));
    SASSERT(to_string(123.45) == make_string("123.45"));
    SASSERT(to_string(-123.45) == make_string("-123.45"));
    SASSERT(to_string(1.2345678e10) == make_string("12345678000"));
    SASSERT(to_string(-1.2345678e10) == make_string("-12345678000"));
    SASSERT(to_string(0.0) == make_string("0"));
    SASSERT(to_wstring(123.45) == make_string(L"123.45"));
    SASSERT(to_wstring(-123.45) == make_string(L"-123.45"));
    SASSERT(to_wstring(1.2345678e10) == make_string(L"12345678000"));
    SASSERT(to_wstring(-1.2345678e10) == make_string(L"-12345678000"));
    SASSERT(to_wstring(0.0) == make_string(L"0"));
    SASSERT(to_u16string(123.45) == make_string(u"123.45"));
    SASSERT(to_u16string(-123.45) == make_string(u"-123.45"));
    SASSERT(to_u16string(1.2345678e10) == make_string(u"12345678000"));
    SASSERT(to_u16string(-1.2345678e10) == make_string(u"-12345678000"));
    SASSERT(to_u16string(0.0) == make_string(u"0"));
    SASSERT(to_u32string(123.45) == make_string(U"123.45"));
    SASSERT(to_u32string(-123.45) == make_string(U"-123.45"));
    SASSERT(to_u32string(1.2345678e10) == make_string(U"12345678000"));
    SASSERT(to_u32string(-1.2345678e10) == make_string(U"-12345678000"));
    SASSERT(to_u32string(0.0) == make_string(U"0"));

    assert(make_string("aiueo kakiku").to_std_string() == std::string("aiueo kakiku"));
    assert(make_string(L"aiueo kakiku").to_std_string() == std::wstring(L"aiueo kakiku"));
    assert(make_string(u"aiueo kakiku").to_std_string() == std::u16string(u"aiueo kakiku"));
    assert(make_string(U"aiueo kakiku").to_std_string() == std::u32string(U"aiueo kakiku"));

    SASSERT(detail::is_should_be_removed(make_string("123.45000"), 8, 6));
    SASSERT(detail::is_should_be_removed(make_string("123.45000"), 8, 8));
    SASSERT_NOT(detail::is_should_be_removed(make_string("123.45000"), 8, 4));
    SASSERT_NOT(detail::is_should_be_removed(make_string("123.45000"), 8, 0));

    SASSERT(string<16>(make_string("hoge")) == "hoge");
    string<16> hoge = make_string("hoge");
    string<16> hoge2 = make_string("");
    (void)hoge, (void)hoge2;

    std::cout << make_string("OK\n");
    return 0;
}
