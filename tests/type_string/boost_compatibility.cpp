#include "../../frozen/meta/string.hpp"
#include "../util.hpp"

#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/empty.hpp>

using namespace frozen::meta;

IS_SAME(boost::mpl::size<S("hoge")>::type, boost::mpl::size_t<4>);
IS_SAME(boost::mpl::size<S("")>::type, boost::mpl::size_t<0>);
SASSERT(boost::mpl::size<S("hoge")>::type::value == 4);

SASSERT(boost::mpl::empty<S("")>::type::value);
IS_SAME(boost::mpl::empty<S("")>::type, boost::mpl::true_);
SASSERT_NOT(boost::mpl::empty<S("hoge")>::type::value);

int main()
{
    std::cout << "OK\n";
    return 0;
}
