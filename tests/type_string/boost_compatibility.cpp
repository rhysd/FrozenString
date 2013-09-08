#include "../../frozen/meta/string.hpp"
#include "../util.hpp"

#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>

using namespace frozen::meta;

IS_SAME(boost::mpl::size<S("hoge")>::type, boost::mpl::size_t<4>);
IS_SAME(boost::mpl::size<S("")>::type, boost::mpl::size_t<0>);

#include <iostream>
int main()
{
    std::cout << "OK\n";
    return 0;
}
