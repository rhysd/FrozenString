#if !defined ISTRING_BASIC_STRING_HPP_INCLUDED
#define      ISTRING_BASIC_STRING_HPP_INCLUDED

#include <cstddef>
#include <stdexcept>
#include <ostream>

#include "./detail/indices.hpp"
#include "./detail/array_wrapper.hpp"
#include "./make.hpp"


namespace istring {

using std::size_t;

template<class Char, size_t N>
class basic_string{
public:

    // type definitions
    typedef Char value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef detail::make_indices<0, N> indices_type;

    // ctor definitions
    basic_string() = delete;

    constexpr basic_string(Char const (&str)[N])
        : basic_string(str, detail::make_indices<0, N>())
    {}

    // implicit conversion from <braced initializer list> to array_wrapper is expected
    constexpr basic_string(detail::array_wrapper<Char, N> aw)
        : elems(aw)
    {}

    // access
    constexpr value_type front() const
    {
        return elems.data[0];
    }

    constexpr value_type back() const
    {
        return elems.data[N-1];
    }

    constexpr const_pointer data() const
    {
        return elems.data;
    }

    constexpr value_type at(size_type idx) const
    {
        return idx < N ? elems.data[idx] : throw std::out_of_range("index out of range");
    }

    // iterator interfaces
    constexpr const_iterator begin() const
    {
        return elems.data;
    }

    constexpr const_iterator end() const
    {
        return elems.data + N;
    }

    iterator begin()
    {
        return elems.data;
    }

    iterator end()
    {
        return elems.data + N;
    }

    // capacity
    constexpr size_type size() const
    {
        return N;
    }

    constexpr size_type max_size() const
    {
        return N;
    }

    constexpr bool empty() const
    {
        return N==0;
    }

    // operators
    constexpr value_type operator[](size_type idx) const
    {
        return this->at(idx);
    }

    template<size_t M>
    constexpr basic_string<Char, N+M-1> operator+(basic_string<Char, M> const& rhs) const
    {
        return operator_plus_impl(rhs, detail::make_indices<0, N-1>(), detail::make_indices<0, M-1>());
    }

    template<size_t M>
    constexpr basic_string<Char, N+M-1> operator+(Char const (&rhs)[M]) const
    {
        return operator_plus_impl(rhs, detail::make_indices<0, N-1>(), detail::make_indices<0, M-1>());
    }

    constexpr basic_string<Char, N+1> operator+(Char rhs) const
    {
        return operator_plus_impl(rhs, detail::make_indices<0, N-1>());
    }

    template<size_t M>
    constexpr bool operator==(basic_string<Char, M> const& rhs) const
    {
        return N!=M ? false : operator_equal_impl(rhs.elems, 0);
    }

    template<size_t M>
    constexpr bool operator==(Char const (&rhs)[M]) const
    {
        return N!=M ? false : operator_equal_impl(rhs, 0);
    }

    template<size_t M>
    constexpr bool operator!=(basic_string<Char, M> const& rhs) const
    {
        return ! operator==(rhs);
    }

    template<size_t M>
    constexpr bool operator!=(Char const (&rhs)[M]) const
    {
        return ! operator==(rhs);
    }

    template<size_t M>
    constexpr bool operator<(basic_string<Char, M> const& rhs) const
    {
        return operator_less_impl<M>(rhs, 0);
    }

    template<size_t M>
    constexpr bool operator<(Char const(&rhs)[M]) const
    {
        return operator_less_impl<M>(rhs, 0);
    }

    template<size_t M>
    constexpr bool operator>=(basic_string<Char, M> const& rhs) const
    {
        return ! operator<(rhs);
    }

    template<size_t M>
    constexpr bool operator>=(Char const(&rhs)[M]) const
    {
        return ! operator<(rhs);
    }

    template<size_t M>
    constexpr bool operator>(basic_string<Char, M> const& rhs) const
    {
        return operator_greater_impl<M>(rhs, 0);
    }

    template<size_t M>
    constexpr bool operator>(Char const(&rhs)[M]) const
    {
        return operator_greater_impl<M>(rhs, 0);
    }

    template<size_t M>
    constexpr bool operator<=(basic_string<Char, M> const& rhs) const
    {
        return ! operator>(rhs);
    }

    template<size_t M>
    constexpr bool operator<=(Char const(&rhs)[M]) const
    {
        return ! operator>(rhs);
    }

    template<class C, size_t J>
    friend inline std::ostream &operator<<(std::ostream &os, basic_string<C, J> const& rhs);

private:
    template<size_t... Indices>
    constexpr basic_string(Char const (&str)[N], detail::indices<Indices...>)
        : elems({str[Indices]...})
    {}

    template<class Array, size_t... IndicesL, size_t... IndicesR>
    constexpr basic_string<Char, (N-1)+sizeof...(IndicesR)+1> operator_plus_impl(Array const& rhs, detail::indices<IndicesL...>, detail::indices<IndicesR...>) const
    {
        return {{elems[IndicesL]..., rhs[IndicesR]..., '\0'}};
    }

    template<size_t... IndicesL>
    constexpr basic_string<Char, N+1> operator_plus_impl(Char rhs, detail::indices<IndicesL...>) const
    {
        return {{elems[IndicesL]..., rhs, '\0'}};
    }

    template<class Array>
    constexpr bool operator_equal_impl(Array const& rhs, size_t idx) const
    {
        return idx == N ? true : elems[idx] == rhs[idx] && operator_equal_impl(rhs, idx+1);
    }

    template<size_t M, class Array>
    constexpr bool operator_less_impl(Array const& rhs, size_t idx) const
    {
        return idx == M ? false :
               idx == N ? true :
               elems[idx] < rhs[idx] ? true :
               elems[idx] > rhs[idx] ? false :
               operator_less_impl<M>(rhs, idx+1);
    }

    template<size_t M, class Array>
    constexpr bool operator_greater_impl(Array const& rhs, size_t idx) const
    {
        return idx == N ? false :
               idx == M ? true :
               elems[idx] < rhs[idx] ? false :
               elems[idx] > rhs[idx] ? true :
               operator_greater_impl<M>(rhs, idx+1);
    }

private:
    detail::array_wrapper<Char, N> const elems;
};

template<class Char, size_t M, size_t N>
inline constexpr bool operator==(Char const (&lhs)[M], basic_string<Char, N> const& rhs)
{
    return rhs == lhs;
}

template<class Char, size_t M, size_t N>
inline constexpr bool operator!=(Char const (&lhs)[M], basic_string<Char, N> const& rhs)
{
    return rhs != lhs;
}

namespace detail {

    template<class Char, size_t M, size_t N, size_t... IndicesL, size_t... IndicesR>
    inline constexpr basic_string<Char, M+N-1> operator_plus_impl(Char const (&lhs)[M], basic_string<Char, N> const& rhs, detail::indices<IndicesL...>, detail::indices<IndicesR...>)
    {
        return {{lhs[IndicesL]..., rhs[IndicesR]..., '\0'}};
    }

} // namespace detail

template<class Char, size_t M, size_t N>
inline constexpr basic_string<Char, M+N-1> operator+(Char const (&lhs)[M], basic_string<Char, N> const& rhs)
{
    return detail::operator_plus_impl(lhs, rhs, detail::make_indices<0, M-1>(), detail::make_indices<0, N-1>());
}

namespace detail {

    template<class Char, size_t N, size_t... IndicesR>
    inline constexpr basic_string<Char, N+1> operator_plus_impl(Char lhs, basic_string<Char, N> const& rhs, detail::indices<IndicesR...>)
    {
        return {{lhs, rhs[IndicesR]...}};
    }

} // namespace detail

template<class Char, size_t N>
inline constexpr basic_string<Char, N+1> operator+(Char lhs, basic_string<Char, N> const& rhs)
{
    return detail::operator_plus_impl(lhs, rhs, detail::make_indices<0, N>());
}

template<class Char, size_t N, size_t M>
inline constexpr bool operator<(Char const (&lhs)[N], basic_string<Char, M> const& rhs)
{
    return rhs > lhs;
}

template<class Char, size_t N, size_t M>
inline constexpr bool operator>(Char const (&lhs)[N], basic_string<Char, M> const& rhs)
{
    return rhs < lhs;
}

template<class Char, size_t N, size_t M>
inline constexpr bool operator<=(Char const (&lhs)[N], basic_string<Char, M> const& rhs)
{
    return rhs >= lhs;
}

template<class Char, size_t N, size_t M>
inline constexpr bool operator>=(Char const (&lhs)[N], basic_string<Char, M> const& rhs)
{
    return rhs <= lhs;
}

template<class Char, size_t N>
inline std::ostream &operator<<(std::ostream &os, basic_string<Char, N> const& rhs)
{
    os << rhs.elems.data;
    return os;
}

} // namespace istring

#endif    // ISTRING_BASIC_STRING_HPP_INCLUDED

