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


    // Primary categories
    template<class T>
    using is_void = typename std::is_void<T>::type;

    template<class T>
    using is_floating_point = typename std::is_floating_point<T>::type;

    template<class T>
    using is_array = typename std::is_array<T>::type;

    template<class T>
    using is_enum = typename std::is_enum<T>::type;

    template<class T>
    using is_union = typename std::is_union<T>::type;

    template<class T>
    using is_class = typename std::is_class<T>::type;

    template<class T>
    using is_function = typename std::is_function<T>::type;

    template<class T>
    using is_pointer = typename std::is_pointer<T>::type;

    template<class T>
    using is_lvalue_reference = typename std::is_lvalue_reference<T>::type;

    template<class T>
    using is_rvalue_reference = typename std::is_rvalue_reference<T>::type;

    template<class T>
    using is_member_object_pointer = typename std::is_member_object_pointer<T>::type;

    template<class T>
    using is_member_function_pointer = typename std::is_member_function_pointer<T>::type;


    // Composite type categories
    template<class T>
    using is_fundamental = typename std::is_fundamental<T>::type;

    template<class T>
    using is_arithmetic = typename std::is_arithmetic<T>::type;

    template<class T>
    using is_scalar = typename std::is_scalar<T>::type;

    template<class T>
    using is_object = typename std::is_object<T>::type;

    template<class T>
    using is_compound = typename std::is_compound<T>::type;

    template<class T>
    using is_reference = typename std::is_reference<T>::type;

    template<class T>
    using is_member_pointer = typename std::is_member_pointer<T>::type;


    // Type properties
    template<class T>
    using is_const = typename std::is_const<T>::type;

    template<class T>
    using is_volatile = typename std::is_volatile<T>::type;

    template<class T>
    using is_trivial = typename std::is_trivial<T>::type;

    // gcc-4.8.1 seems not to implement is_trivially_copyable
    // template<class T>
    // using is_trivially_copyable = typename std::is_trivially_copyable<T>::type;

    template<class T>
    using is_standard_layout = typename std::is_standard_layout<T>::type;

    template<class T>
    using is_pod = typename std::is_pod<T>::type;

    template<class T>
    using is_literal_type = typename std::is_literal_type<T>::type;

    template<class T>
    using is_empty = typename std::is_empty<T>::type;

    template<class T>
    using is_polymorphic = typename std::is_polymorphic<T>::type;

    template<class T>
    using is_abstract = typename std::is_abstract<T>::type;

    template<class T>
    using is_signed = typename std::is_signed<T>::type;

    template<class T>
    using is_unsigned = typename std::is_unsigned<T>::type;


    // Supported operations
    template<class T>
    using is_constructible = typename std::is_constructible<T>::type;

    // template<class T>
    // using is_trivially_constructible = typename std::is_trivially_constructible<T>::type;

    template<class T>
    using is_nothrow_constructible = typename std::is_nothrow_constructible<T>::type;

    template<class T>
    using is_default_constructible = typename std::is_default_constructible<T>::type;

    // template<class T>
    // using is_trivially_default_constructible = typename std::is_trivially_default_constructible<T>::type;

    template<class T>
    using is_nothrow_default_constructible = typename std::is_nothrow_default_constructible<T>::type;

    template<class T>
    using is_copy_constructible = typename std::is_copy_constructible<T>::type;

    // template<class T>
    // using is_trivially_copy_constructible = typename std::is_trivially_copy_constructible<T>::type;

    template<class T>
    using is_nothrow_copy_constructible = typename std::is_nothrow_copy_constructible<T>::type;

    template<class T>
    using is_move_constructible = typename std::is_move_constructible<T>::type;

    // template<class T>
    // using is_trivially_move_constructible = typename std::is_trivially_move_constructible<T>::type;

    template<class T>
    using is_nothrow_move_constructible = typename std::is_nothrow_move_constructible<T>::type;

    template<class T, class U>
    using is_assignable = typename std::is_assignable<T, U>::type;

    // template<class T, class U>
    // using is_trivially_assignable = typename std::is_trivially_assignable<T, U>::type;

    template<class T, class U>
    using is_nothrow_assignable = typename std::is_nothrow_assignable<T, U>::type;

    template<class T>
    using is_copy_assignable = typename std::is_copy_assignable<T>::type;

    // template<class T>
    // using is_trivially_copy_assignable = typename std::is_trivially_copy_assignable<T>::type;

    template<class T>
    using is_nothrow_copy_assignable = typename std::is_nothrow_copy_assignable<T>::type;

    template<class T>
    using is_move_assignable = typename std::is_move_assignable<T>::type;

    // template<class T>
    // using is_trivially_move_assignable = typename std::is_trivially_move_assignable<T>::type;

    template<class T>
    using is_nothrow_move_assignable = typename std::is_nothrow_move_assignable<T>::type;

    template<class T>
    using is_destructible = typename std::is_destructible<T>::type;

    // template<class T>
    // using is_trivially_destructible = typename std::is_trivially_destructible<T>::type;

    template<class T>
    using is_nothrow_destructible = typename std::is_nothrow_destructible<T>::type;

    template<class T>
    using has_virtual_destructor = typename std::has_virtual_destructor<T>::type;


    // Type relationships
    template<class T, class U>
    using is_same = typename std::is_same<T, U>::type;

    template<class B, class D>
    using is_base_of = typename std::is_base_of<B, D>::type;

    template<class F, class T>
    using is_convertible = typename std::is_convertible<F, T>::type;

} // namespace alias
} // namespace frozen

#endif // FROZEN_TYPE_TRAITS_ALIASES_HPP_INCLUDED
