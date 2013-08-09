#include <iostream>

#include "../util.hpp"

#include "../../immutable_string/string.hpp"

using namespace istring;

int main()
{
    STATIC_ASSERT((to_basic_string<char>(42) == make("42")));
    STATIC_ASSERT((to_basic_string<char>(-423) == make("-423")));

    STATIC_ASSERT((detail::digits10_of(100.123) == 11));
    STATIC_ASSERT((detail::digits10_of(0.123) == 9));

    STATIC_ASSERT((detail::float_integer_part_digits10_of(456.123, 0) == 6));
    STATIC_ASSERT((detail::float_integer_part_digits10_of(456.123, 1) == 5));
    STATIC_ASSERT((detail::float_integer_part_digits10_of(456.123, 2) == 4));
    STATIC_ASSERT((detail::float_integer_part_digits10_of(0.123, 0) == 0));
    STATIC_ASSERT((detail::float_integer_part_digits10_of(-5.123, 0) == 5));
    STATIC_ASSERT((detail::float_integer_part_digits10_of(1e10, 9) == 0));
    STATIC_ASSERT((detail::float_integer_part_digits10_of(1e100, 9) == 0));
    STATIC_ASSERT((detail::float_integer_part_digits10_of(45674567.123, 4) == 7));
    STATIC_ASSERT((detail::float_integer_part_digits10_of(999999.0e100, 105) == 9));
    STATIC_ASSERT((detail::float_fraction_part_digits10_of(456.123, 0) == 1));
    STATIC_ASSERT((detail::float_fraction_part_digits10_of(456.123, 1) == 2));
    STATIC_ASSERT((detail::float_fraction_part_digits10_of(456.123, 2) == 3));
    STATIC_ASSERT((detail::float_fraction_part_digits10_of(-5.1234, 3) == 4));
    STATIC_ASSERT((to_basic_string<char>(123.45) == make("123.450000")));
    STATIC_ASSERT((to_basic_string<char>(-123.45) == make("-123.450000")));
    STATIC_ASSERT((to_basic_string<char>(1.2345678e10) == make("12345678000.000000")));
    STATIC_ASSERT((to_basic_string<char>(-1.2345678e10) == make("-12345678000.000000")));
    STATIC_ASSERT((to_basic_string<char>(0.0) == make("0.000000")));
    STATIC_ASSERT((to_string(123.45) == make("123.450000")));
    STATIC_ASSERT((to_string(-123.45) == make("-123.450000")));
    STATIC_ASSERT((to_string(1.2345678e10) == make("12345678000.000000")));
    STATIC_ASSERT((to_string(-1.2345678e10) == make("-12345678000.000000")));
    STATIC_ASSERT((to_string(0.0) == make("0.000000")));
    STATIC_ASSERT((to_wstring(123.45) == make(L"123.450000")));
    STATIC_ASSERT((to_wstring(-123.45) == make(L"-123.450000")));
    STATIC_ASSERT((to_wstring(1.2345678e10) == make(L"12345678000.000000")));
    STATIC_ASSERT((to_wstring(-1.2345678e10) == make(L"-12345678000.000000")));
    STATIC_ASSERT((to_wstring(0.0) == make(L"0.000000")));
    STATIC_ASSERT((to_w16string(123.45) == make(u"123.450000")));
    STATIC_ASSERT((to_w16string(-123.45) == make(u"-123.450000")));
    STATIC_ASSERT((to_w16string(1.2345678e10) == make(u"12345678000.000000")));
    STATIC_ASSERT((to_w16string(-1.2345678e10) == make(u"-12345678000.000000")));
    STATIC_ASSERT((to_w16string(0.0) == make(u"0.000000")));
    STATIC_ASSERT((to_w32string(123.45) == make(U"123.450000")));
    STATIC_ASSERT((to_w32string(-123.45) == make(U"-123.450000")));
    STATIC_ASSERT((to_w32string(1.2345678e10) == make(U"12345678000.000000")));
    STATIC_ASSERT((to_w32string(-1.2345678e10) == make(U"-12345678000.000000")));
    STATIC_ASSERT((to_w32string(0.0) == make(U"0.000000")));


    std::cout << make("OK\n");
    return 0;
}
