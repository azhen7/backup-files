#ifndef _STD_COPY_TYPE_TRAITS
#define _STD_COPY_TYPE_TRAITS

#include <type_traits>

namespace std_copy {
    //integral_constant
    template <class T, T v>
    struct integral_constant {
        static constexpr T value = v;
        typedef T                   value_type;
        typedef integral_constant   type;

        constexpr operator value_type() {
            return value;
        }
        constexpr operator()() {
            return value;
        }
    };
    //true_type
    typedef integral_constant<bool, true>   true_type;
    //false_type
    typedef integral_constant<bool, false>  false_type;

    //remove_reference
    template <class T>
    struct remove_reference {
        typedef T   type;
    };
    template <class T>
    struct remove_reference<T&> {
        typedef T   type;
    };
    template <class T>
    struct remove_reference<T&&> {
        typedef T   type;
    };
    template <class T>
    using remove_reference_t = typename remove_reference<T>::type;

    //add_lvalue_reference
    template <class T>
    struct add_lvalue_reference {
        typedef typename remove_reference<T>::type&  type;
    };
    template <>
    struct add_lvalue_reference<void> {
        typedef void    type;
    };

    //add_rvalue_reference
    template <class T>
    struct add_rvalue_reference {
        typedef T&&     type;
    };
    template <class T>
    struct add_rvalue_reference<T&> {
        typedef T&      type;
    };
    template <class T>
    struct add_rvalue_reference<T&&> {
        typedef T&&     type;
    };
    template <>
    struct add_rvalue_reference<void> {
        typedef void    type;
    };
    //remove_cv
    template <class T>
    struct remove_cv {
        typedef T   type;
    };
    template <class T>
    struct remove_cv<const T> {
        typedef T   type;
    };
    template <class T>
    struct remove_cv<volatile T> {
        typedef T   type;
    };
    template <class T>
    struct remove_cv<const volatile T> {
        typedef T   type;
    };
    template <class T>
    using remove_cv_t = typename remove_cv<T>::type;

    //remove_const
    template <class T>
    struct remove_const {
        typedef T   type;
    };
    template <class T>
    struct remove_const<const T> {
        typedef T   type;
    };
    template <class T>
    using remove_const_t = typename remove_const<T>::type;

    //remove_volatile
    template <class T>
    struct remove_volatile {
        typedef T   type;
    };
    template <class T>
    struct remove_volatile<volatile T> {
        typedef T   type;
    };
    template <class T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    //add_cv, add_const, add_volatile
    template <class T>
    struct add_cv {
        typedef const volatile T    type;
    };
    template <class T>
    struct add_const {
        typedef const T             type;
    };
    template <class T>
    struct add_volatile {
        typedef volatile T          type;
    };
    template <class T>
    using add_cv_t = typename add_cv<T>::type;
    template <class T>
    using add_const_t = typename add_const<T>::type;
    template <class T>
    using add_volatile_t = typename add_volatile<T>::type;

    //make_signed
    template <class T>
    struct make_signed {
        typedef signed      type;
    };
    template <class T>
    using make_signed_t = typename make_signed<T>::type;

    //make_unsigned
    template <class T>
    struct make_unsigned {
        typedef unsigned      type;
    };
    template <class T>
    using make_unsigned_t = typename make_unsigned<T>::type;

    //remove_pointer
    template <class T>
    struct remove_pointer {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<T*> {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<const T*> {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<volatile T*> {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<const volatile T*> {
        typedef T   type;
    };

    //add_pointer
    template <class T>
    struct add_pointer {
        typedef typename remove_reference<T>::type*  type;
    };
}

#endif