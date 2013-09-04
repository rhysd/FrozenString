#include "../../frozen/string.hpp"

constexpr frozen::string<10>
fizzbuzz_value(int i)
{
    return i % 15 == 0 ? "fizzbuzz" :
           i %  3 == 0 ? "fizz" :
           i %  5 == 0 ? "buzz" :
                         frozen::to_string(i);
}

template<unsigned int I>
constexpr frozen::string<I*11+1>
fizzbuzz()
{
    return fizzbuzz<I-1>() + fizzbuzz_value(I) + '\n';
}

template<>
constexpr frozen::string<1>
fizzbuzz<0>()
{
    return "";
}

// result
static constexpr char result[] =
    "1\n2\nfizz\n4\nbuzz\nfizz\n7\n8\nfizz\nbuzz\n11\nfizz\n13\n14\nfizzbuzz\n";

int main()
{
    static_assert(fizzbuzz<15>() == result, "");
    return 0;
}
