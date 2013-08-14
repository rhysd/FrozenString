#ifndef FROZEN_TYPE_TRAITS_ALIASES_HPP_INCLUDED
#define FROZEN_TYPE_TRAITS_ALIASES_HPP_INCLUDED

#include <type_traits>

namespace frozen {
namespace alias {

    /*
     * 20.9.7 Transformations between types
     */

    // 20.9.7.1 Const-volatile modifications
    template <class T>
    using remove_cv = typename std::remove_cv<T>::type;

    template <class T>
    using remove_const = typename std::remove_const<T>::type;

    template <class T>
    using remove_volatile = typename std::remove_volatile<T>::type;

    template <class T>
    using add_cv = typename std::add_cv<T>::type;

    template <class T>
    using add_const = typename std::add_const<T>::type;

    template <class T>
    using add_volatile = typename std::add_volatile<T>::type;

    // 20.9.7.2 Reference modifications
    template <class T>
    using remove_reference = typename std::remove_reference<T>::type;

    template <class T>
    using add_lvalue_reference = typename std::add_lvalue_reference<T>::type;

    template <class T>
    using add_rvalue_reference = typename std::add_rvalue_reference<T>::type;

    // 20.9.7.4 Array modifications
    template <class T>
    using remove_extent = typename std::remove_extent<T>::type;

    template <class T>
    using remove_all_extents = typename std::remove_all_extents<T>::type;

    // 20.9.7.5 Pointer modifications
    template <class T>
    using remove_pointer = typename std::remove_pointer<T>::type;

    template <class T>
    using add_pointer = typename std::add_pointer<T>::type;

    // 20.9.7.6 Other transformations
    template <std::size_t Len, std::size_t Align>
    using aligned_storage = typename std::aligned_storage<Len, Align>::type;

    /* aligned_union is not implemented in std... (gcc-4.7.0)*/
    // template <std::size_t Len, class... Types>
    // using aligned_union = typename std::aligned_union<Len Types...>::type;

    template<class T>
    using decay = typename std::decay<T>::type;

    template<bool B, class T = void>
    using enable_if = typename std::enable_if<B, T>::type;

    template<bool B, class T, class U>
    using conditional = typename std::conditional<B, T, U>::type;

    template <class... T>
    using common_type = typename std::common_type<T...>::type;

    template <class T>
    using underlying_type = typename std::underlying_type<T>::type;

    template <class F, class... Args >
    using result_of = typename std::result_of<F(Args...)>::type;

    template<class T, class U>
    using is_same = typename std::is_same<T, U>::type;

    

} // namespace alias
} // namespace frozen

#endif // FROZEN_TYPE_TRAITS_ALIASES_HPP_INCLUDED
