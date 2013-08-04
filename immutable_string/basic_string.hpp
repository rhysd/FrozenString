#if !defined ISTRING_BASIC_STRING_HPP_INCLUDED
#define      ISTRING_BASIC_STRING_HPP_INCLUDED

#include <cstddef>
#include <stdexcept>
#include <ostream>

#include "./detail/util.hpp"
#include "./detail/indices.hpp"
#include "./detail/array_wrapper.hpp"
#include "./detail/strlen.hpp"

namespace istring {

using std::size_t;

// forward declaration
template<class Char, size_t N>
class basic_string;

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

    template<class Char, size_t M, size_t N>
    class operator_plus_impl{
        size_t const size_lhs;
        size_t const size_rhs;

    public:
        constexpr operator_plus_impl(size_t sl, size_t sr)
            : size_lhs(sl), size_rhs(sr) {}

        template<class ArrayL, class ArrayR, size_t... IndicesL, size_t... IndicesR>
        constexpr basic_string<Char, M+N> operator()(ArrayL const& lhs, ArrayR const& rhs, detail::indices<IndicesL...>, detail::indices<IndicesR...>)
        {
            return {{
                        ( IndicesL < size_lhs ?
                            lhs[IndicesL] :
                            rhs[IndicesL - size_lhs]
                        )...,
                        ( IndicesR + (M - size_lhs ) < size_rhs ?
                            rhs[IndicesR + (M - size_lhs)] :
                            '\0'
                        )...
                    }};
        }
    };

} // namespace detail

template<class Char, size_t M, size_t N>
inline constexpr basic_string<Char, M+N> operator+(Char const (&lhs)[M], basic_string<Char, N> const& rhs)
{
    return detail::operator_plus_impl<Char, M, N>(detail::strlen(lhs), detail::strlen(rhs))(lhs, rhs, detail::make_indices<0, M>(), detail::make_indices<0, N>());
}

namespace detail {

    template<class Char, size_t N, size_t... IndicesR>
    inline constexpr basic_string<Char, N+1> operator_plus_char_impl(Char lhs, basic_string<Char, N> const& rhs, detail::indices<IndicesR...>)
    {
        return {{lhs, rhs[IndicesR]...}};
    }

} // namespace detail

template<class Char, size_t N>
inline constexpr basic_string<Char, N+1> operator+(Char lhs, basic_string<Char, N> const& rhs)
{
    return detail::operator_plus_char_impl(lhs, rhs, detail::make_indices<0, N>());
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


template<class Char, size_t N>
class basic_string{
public:

    // type definitions
    typedef typename detail::is_char<Char>::type value_type;
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

    explicit constexpr basic_string(Char c)
        : basic_string(c, detail::make_indices<0, N-1>())
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

    constexpr size_type max_size() const
    {
        return N;
    }

    constexpr bool empty() const
    {
        return N==0;
    }

    constexpr size_type size() const
    {
        return size_impl(0);
    }

    // operators
    constexpr value_type operator[](size_type idx) const
    {
        return this->at(idx);
    }

    template<size_t M>
    constexpr basic_string<Char, N+M> operator+(basic_string<Char, M> const& rhs) const
    {
        return detail::operator_plus_impl<Char, M, N>(detail::strlen(elems), detail::strlen(rhs))(elems, rhs, detail::make_indices<0, M>(), detail::make_indices<0, N>());
    }

    template<size_t M>
    constexpr basic_string<Char, N+M> operator+(Char const (&rhs)[M]) const
    {
        return detail::operator_plus_impl<Char, M, N>(detail::strlen(elems), detail::strlen(rhs))(elems, rhs, detail::make_indices<0, M>(), detail::make_indices<0, N>());
    }

    constexpr basic_string<Char, N+1> operator+(Char rhs) const
    {
        return operator_plus_char_impl(rhs, detail::strlen(elems), detail::make_indices<0, N>());
    }

    template<size_t M>
    constexpr bool operator==(basic_string<Char, M> const& rhs) const
    {
        return detail::strlen(elems, N)!=detail::strlen(rhs, M) ?
            false : operator_equal_impl(rhs, 0, detail::strlen(elems, N<M ? N : M));
    }

    template<size_t M>
    constexpr bool operator==(Char const (&rhs)[M]) const
    {
        return detail::strlen(elems, N)!=detail::strlen(rhs, M) ?
            false : operator_equal_impl(rhs, 0, detail::strlen(elems, N<M ? N : M));
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
        return operator_less_impl(detail::strlen(elems, N), detail::strlen(rhs, M))(elems, rhs, 0);
    }

    template<size_t M>
    constexpr bool operator<(Char const(&rhs)[M]) const
    {
        return operator_less_impl(detail::strlen(elems, N), detail::strlen(rhs, M))(elems, rhs, 0);
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
        return operator_greater_impl(detail::strlen(elems, N), detail::strlen(rhs, M))(elems, rhs, 0);
    }

    template<size_t M>
    constexpr bool operator>(Char const(&rhs)[M]) const
    {
        return operator_greater_impl(detail::strlen(elems, N), detail::strlen(rhs, M))(elems, rhs, 0);
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

    template<size_t... Indices>
    explicit constexpr basic_string(Char c, detail::indices<Indices...>)
        : elems({(static_cast<void>(Indices), c)..., '\0'})
    {}

    template<size_t... IndicesL>
    constexpr basic_string<Char, N+1> operator_plus_char_impl(Char rhs, size_t len_lhs, detail::indices<IndicesL...>) const
    {
        return {{
                    ( IndicesL < len_lhs ? elems[IndicesL] :
                      IndicesL == len_lhs ? rhs : '\0' )...
               }};
    }

    template<class Array>
    constexpr bool operator_equal_impl(Array const& rhs, size_t idx, size_t max_size) const
    {
        return idx == max_size ? true : elems[idx] == rhs[idx] && operator_equal_impl(rhs, idx+1, max_size);
    }

    class operator_less_impl{
        size_t const size_lhs;
        size_t const size_rhs;

    public:
        constexpr operator_less_impl(size_t sl, size_t sr)
            : size_lhs(sl), size_rhs(sr) {}

        template<class ArrayL, class ArrayR>
        constexpr bool operator()(ArrayL const& lhs, ArrayR const& rhs, size_t idx) const
        {
            return idx == size_rhs ? false :
                   idx == size_lhs ? true :
                   lhs[idx] < rhs[idx] ? true :
                   lhs[idx] > rhs[idx] ? false :
                                         operator()(lhs, rhs, idx+1);
        }
    };

    class operator_greater_impl{
        size_t const size_lhs;
        size_t const size_rhs;

    public:
        constexpr operator_greater_impl(size_t sl, size_t sr)
            : size_lhs(sl), size_rhs(sr) {}

        template<class ArrayL, class ArrayR>
        constexpr bool operator()(ArrayL const& lhs, ArrayR const& rhs, size_t idx) const
        {
            return idx == size_lhs ? false :
                   idx == size_rhs ? true :
                   lhs[idx] < rhs[idx] ? false :
                   lhs[idx] > rhs[idx] ? true :
                                         operator()(lhs, rhs, idx+1);
        }
    };

    constexpr size_type size_impl(size_type idx) const
    {
        return elems[idx] == '\0' || !(idx < N) ?
            0 : 1 + size_impl(idx+1);
    }

private:
    detail::array_wrapper<Char, N> const elems;

}; // class basic_string

} // namespace istring


#endif    // ISTRING_BASIC_STRING_HPP_INCLUDED
