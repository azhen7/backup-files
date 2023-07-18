#ifndef _STD_COPY_TYPE_TRAITS
#define _STD_COPY_TYPE_TRAITS

#include <type_traits>

namespace std_copy
{
    //integral_constant
    template <class T, T v>
    struct integral_constant
    {
        static constexpr T value = v;
        typedef T                   value_type;
        typedef integral_constant   type;

        constexpr operator value_type()
        {
            return value;
        }
        constexpr T operator()()
        {
            return value;
        }
    };
    //bool_constant
    template <bool B>
    using bool_constant = integral_constant<bool, B>;
    //true_type
    using true_type = bool_constant<true>;
    //false_type
    using false_type = bool_constant<false>;

    //type_identity
    template <class T>
    struct type_identity
    {
        typedef T   type;
    };
    template <class T>
    using type_identity_t = typename type_identity<T>::type;

    //remove_reference
    template <class T>
    struct remove_reference
    {
        typedef T   type;
    };
    template <class T>
    struct remove_reference<T&>
    {
        typedef T   type;
    };
    template <class T>
    struct remove_reference<T&&>
    {
        typedef T   type;
    };
    template <class T>
    using remove_reference_t = typename remove_reference<T>::type;

    //add_lvalue_reference
    template <class T>
    struct add_lvalue_reference
    {
        typedef typename remove_reference<T>::type&  type;
    };
    template <>
    struct add_lvalue_reference<void>
    {
        typedef void    type;
    };

    //add_rvalue_reference
    template <class T>
    struct add_rvalue_reference
    {
        typedef T&&     type;
    };
    template <class T>
    struct add_rvalue_reference<T&>
    {
        typedef T&      type;
    };
    template <class T>
    struct add_rvalue_reference<T&&>
    {
        typedef T&&     type;
    };
    template <>
    struct add_rvalue_reference<void>
    {
        typedef void    type;
    };
    //remove_cv
    template <class T>
    struct remove_cv
    {
        typedef T   type;
    };
    template <class T>
    struct remove_cv<const T>
    {
        typedef T   type;
    };
    template <class T>
    struct remove_cv<volatile T>
    {
        typedef T   type;
    };
    template <class T>
    struct remove_cv<const volatile T>
    {
        typedef T   type;
    };
    template <class T>
    using remove_cv_t = typename remove_cv<T>::type;

    //remove_const
    template <class T>
    struct remove_const
    {
        typedef T   type;
    };
    template <class T>
    struct remove_const<const T>
    {
        typedef T   type;
    };
    template <class T>
    using remove_const_t = typename remove_const<T>::type;

    //remove_volatile
    template <class T>
    struct remove_volatile
    {
        typedef T   type;
    };
    template <class T>
    struct remove_volatile<volatile T>
    {
        typedef T   type;
    };
    template <class T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    //remove_cvref
    template <class T>
    struct remove_cvref
    {
        typedef remove_reference_t<remove_cv_t<T>>  type;
    };
    template <class T>
    using remove_cvref_t = typename remove_cvref<T>::type;

    //add_cv, add_const, add_volatile
    template <class T>
    struct add_cv
    {
        typedef const volatile T    type;
    };
    template <class T>
    struct add_const
    {
        typedef const T             type;
    };
    template <class T>
    struct add_volatile
    {
        typedef volatile T          type;
    };
    template <class T>
    using add_cv_t = typename add_cv<T>::type;
    template <class T>
    using add_const_t = typename add_const<T>::type;
    template <class T>
    using add_volatile_t = typename add_volatile<T>::type;

    //remove_pointer
    template <class T>
    struct remove_pointer
    {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<T*>
    {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<const T*>
    {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<volatile T*>
    {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<const volatile T*>
    {
        typedef T   type;
    };

    //remove_extent
    template <class T>
    struct remove_extent
    {
        typedef T   type;
    };
    template <class T>
    struct remove_extent<T[]>
    {
        typedef T   type;
    };
    template <class T, unsigned long long N>
    struct remove_extent<T[N]>
    {
        typedef T   type;
    };
    template <class T>
    using remove_extent_t = typename remove_extent<T>::type;

    //remove_all_extents
    template <class T>
    struct remove_all_extents
    {
        typedef T   type;
    };
    template <class T>
    struct remove_all_extents<T[]>
    {
        typedef T   type;
    };
    template <class T, unsigned long long N>
    struct remove_all_extents<T[N]>
    {
        typedef T   type;
    };
    template <class T>
    using remove_all_extents_t = typename remove_all_extents<T>::type;

    //add_pointer
    template <class T>
    struct add_pointer
    {
        typedef typename remove_reference<T>::type*  type;
    };
    template <class T>
    struct add_pointer<T&> : add_pointer<T> {};
    template <class T>
    struct add_pointer<T&&> : add_pointer<T> {};
    template <class T>
    using add_pointer_t = typename add_pointer<T>::type;
    
    //extent
    template <class T, unsigned long long N>
    struct extent : integral_constant<unsigned long long, 0> {};
    template <class T, unsigned long long I>
    struct extent<T[I], 0> : integral_constant<unsigned long long, I> {};
    template <class T, unsigned long long N>
    struct extent<T[], N> : extent<T, N - 1> {};
    template <class T, unsigned long long I, unsigned long long N>
    struct extent<T[I], N> : extent<T, N - 1> {};

    //make_unsigned
    template <class T>
    struct make_unsigned
    {
        typedef T                   type;
    };
    template <>
    struct make_unsigned<short>
    {
        typedef unsigned short      type;
    };
    template <>
    struct make_unsigned<int>
    {
        typedef unsigned int        type;
    };
    template <>
    struct make_unsigned<long>
    {
        typedef unsigned long       type;
    };
    template <>
    struct make_unsigned<long long>
    {
        typedef unsigned long long  type;
    };
    template <>
    struct make_unsigned<char>
    {
        typedef unsigned char       type;
    };
    template <>
    struct make_unsigned<signed char>
    {
        typedef unsigned char       type;
    };
    template <class T>
    using make_unsigned_t = typename make_unsigned<T>::type;

    //make_signed
    template <class T>
    struct make_signed
    {
        typedef T                   type;
    };
    template <>
    struct make_signed<make_unsigned<char>>
    {
        typedef signed char         type;
    };
    template <>
    struct make_signed<unsigned short>
    {
        typedef signed short        type;
    };
    template <>
    struct make_signed<unsigned int>
    {
        typedef signed int          type;
    };
    template <>
    struct make_signed<unsigned long>
    {
        typedef signed long         type;
    };
    template <>
    struct make_signed<unsigned long long>
    {
        typedef signed long long    type;
    };
    template <class T>
    using make_signed_t = typename make_signed<T>::type;

    //Type properties

    //is_same
    template <class T, class U>
    struct is_same : false_type {};
    template <class T>
    struct is_same<T, T> : true_type {};
    template <class T, class U>
    constexpr bool is_same_v = is_same<T, U>::value;

    //is_void
    template <class T>
    struct is_void : is_same<T, void> {};
    template <class T>
    constexpr bool is_void_v = std_copy::is_void<T>::value;

    //is_integral
    template <class T>
    struct is_integral
        : bool_constant<
            is_same<unsigned short, make_unsigned_t<remove_cvref_t<T>>>::value     ||
            is_same<unsigned int, make_unsigned_t<remove_cvref_t<T>>>::value       ||
            is_same<unsigned long, make_unsigned_t<remove_cvref_t<T>>>::value      ||
            is_same<unsigned long long, make_unsigned_t<remove_cvref_t<T>>>::value ||
            is_same<bool, remove_cvref_t<T>>::value                                ||
            is_same<unsigned char, make_unsigned_t<remove_cvref_t<T>>>::value      ||
            is_same<char8_t, remove_cvref_t<T>>::value                             ||
            is_same<char16_t, remove_cvref_t<T>>::value                            ||
            is_same<char32_t, remove_cvref_t<T>>::value                            ||
            is_same<wchar_t, remove_cvref_t<T>>::value
        > {};
    template <class T>
    constexpr bool is_integral_v = is_integral<T>::value;

    //is_floating_point
    template <class T>
    struct is_floating_point
        : bool_constant<
            is_same<float, remove_cvref_t<T>>::value   ||
            is_same<double, remove_cvref_t<T>>::value  ||
            is_same<long double, remove_cvref_t<T>>::value> {};
    template <class T>
    constexpr bool is_floating_point_v = is_floating_point<T>::value;

    //is_null_pointer
    template <class T>
    struct is_null_pointer : is_same<decltype(nullptr), remove_cv_t<T>> {};
    template <class T>
    constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

    //is_pointer
    template <class T>
    struct is_pointer : false_type {};
    template <class T>
    struct is_pointer<T*> : true_type {};
    template <class T>
    struct is_pointer<const T> : is_pointer<T> {};
    template <class T>
    struct is_pointer<volatile T> : is_pointer<T> {};
    template <class T>
    struct is_pointer<const volatile T> : is_pointer<T> {};
    template <class T>
    constexpr bool is_pointer_v = is_pointer<T>::value;

    //is_arithmetic
    template <class T>
    struct is_arithmetic
        : bool_constant<
            is_integral<remove_cv_t<T>>::value      ||
            is_floating_point<remove_cv_t<T>>::value> {};
    template <class T>
    constexpr bool is_arithmetic_v = is_arithmetic<T>::value;

    //is_bounded_array
    template <class T>
    struct is_bounded_array : false_type {};
    template <class T, unsigned long long N>
    struct is_bounded_array<T[N]> : true_type {};
    template <class T>
    constexpr bool is_bounded_array_v = is_bounded_array<T>::value;

    //is_unbounded_array
    template <class T>
    struct is_unbounded_array : false_type {};
    template <class T>
    struct is_unbounded_array<T[]> : true_type {};
    template <class T>
    constexpr bool is_unbounded_array_v = is_unbounded_array<T>::value;

    //is_array
    template <class T>
    struct is_array
        : bool_constant<
            is_unbounded_array<T>::value ||
            is_bounded_array<T>::value> {};
    template <class T>
    constexpr bool is_array_v = is_array<T>::value;

    //is_lvalue_reference
    template <class T>
    struct is_lvalue_reference : false_type {};
    template <class T>
    struct is_lvalue_reference<T&> : true_type {};
    template <class T>
    constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

    //is_rvalue_reference
    template <class T>
    struct is_rvalue_reference : false_type {};
    template <class T>
    struct is_rvalue_reference<T&&> : true_type {};
    template <class T>
    constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

    //is_reference
    template <class T>
    struct is_reference
        : bool_constant<
            is_lvalue_reference<T>::value ||
            is_rvalue_reference<T>::value> {};
    template <class T>
    constexpr bool is_reference_v = is_reference<T>::value;

    //is_const
    template <class T>
    struct is_const : false_type {};
    template <class T>
    struct is_const<const T> : true_type {};
    template <class T>
    constexpr bool is_const_v = is_const<T>::value;

    //is_volatile
    template <class T>
    struct is_volatile : false_type {};
    template <class T>
    struct is_volatile<volatile T> : true_type {};
    template <class T>
    constexpr bool is_volatile_v = is_volatile<T>::value;

    //is_function
    template <class T>
    struct is_function : bool_constant<!is_const_v<T> && !is_reference_v<T>> {};
    template <class T>
    constexpr bool is_function_v = is_function<T>::value;

    //is_class
    template <class T>
    class is_class
    {
        private:
            typedef char     yes;
            typedef int      no;

            template <class C>
            static yes& test(int C::*);

            template <class C>
            static no& test(...);
        
        public:
            static const bool value = sizeof(test<T>(0)) == sizeof(yes);
    };
    template <class T>
    constexpr bool is_class_v = is_class<T>::value;

    //Miscellaneous transformations

    //conditional
    template <bool B, class ifTrue, class ifFalse>
    struct conditional
    {
        typedef ifTrue  type;
    };
    template <class ifTrue, class ifFalse>
    struct conditional<false, ifTrue, ifFalse>
    {
        typedef ifFalse  type;
    };
    template <bool B, class ifTrue, class ifFalse>
    using conditional_t = typename conditional<B, ifTrue, ifFalse>::type;

    //enable_if
    template <bool B, class T = void>
    struct enable_if {};
    template <class T>
    struct enable_if<true, T>
    {
        typedef T   type;
    };
    template <bool B, class T = void>
    using enable_if_t = typename enable_if<B, T>::type;

    //void_t
    template <class ...>
    using void_t = void;

    //decay
    template <class T>
    struct decay
    {
        private:
            typedef remove_reference_t<T>     _type_without_ref;
        public:
            typedef conditional_t<
                is_array_v<_type_without_ref>,
                remove_extent_t<T>*,
                conditional_t<
                    is_function_v<T>,
                    add_pointer_t<T>,
                    remove_cv_t<T>
                >
            >   type;
    };

    //Operations on traits

    //negation
    template <class B>
    struct negation : bool_constant<!bool(B::value)> {};
}

namespace _std_copy_hidden
{
    template <class ...>
    using _void_t = void;

    namespace _type_traits_detail
    {
        template <class Default, class AlwaysVoid, template <typename...> class Template, class ...Args>
        struct _detector
        {
            using type = Default;
        };
        template <class Default, template <typename...> class Template, class ...Args>
        struct _detector<Default, _void_t<Template<Args...>>, Template, Args...>
        {
            using type = Template<Args...>;
        };
    }

    template <class Default, template <typename...> class Template, class ...Args>
    using _detector_t = typename _type_traits_detail::_detector<Default, void, Template, Args...>::type;

    namespace _std_copy_type_traits
    {
        template <class T, bool = std_copy::is_arithmetic_v<T>>
        struct _is_signed_helper
            : std_copy::is_same<std_copy::make_signed_t<std_copy::remove_cv_t<T>>, std_copy::remove_cv_t<T>>
        {
        };
        template <class T>
        struct _is_signed_helper<T, false>
            : std_copy::false_type
        {
        };
        template <class T, bool = std_copy::is_arithmetic_v<T>>
        struct _is_unsigned_helper
            : std_copy::is_same<std_copy::make_unsigned_t<std_copy::remove_cv_t<T>>, std_copy::remove_cv_t<T>>
        {
        };
        template <class T>
        struct _is_unsigned_helper<T, false>
            : std_copy::false_type
        {
        };
        template <class T>
        std_copy::true_type test_if_ptr_convertible(const volatile T*);
        template <class>
        std_copy::false_type test_if_ptr_convertible(const volatile void*);

        template <class T, class D>
        auto test_if_base(...) -> std_copy::true_type;
        template <class T, class D>
        auto test_if_base(int) -> decltype(test_if_ptr_convertible<T>(static_cast<D*>(nullptr)));

        namespace _detail
        {
            template <class T, bool B, class... Args>
            struct _select;

            template <class T, class IntT, class... Args>
            struct _select<T, true, IntT, Args...>
            {
                typedef IntT type;
            };
            template <class T, class IntT, class NextIntT, class... Args>
            struct _select<T, false, IntT, NextIntT, Args...>
                : _select<T, sizeof(T) < sizeof(NextIntT), NextIntT, Args...>
            {
            };
            template <class T, class IntT>
            struct _select<T, false, IntT>
            {
                typedef T type;
            };
        }

        template <class T>
        struct _find_uleast
        {
            using type = typename _detail::_select<T, sizeof(T) < sizeof(unsigned int),
                                                unsigned int,
                                                unsigned long,
                                                unsigned long long,
                                                __uint128_t>::type;
        };

        template <class T>
        struct _find_least_floating_point
        {
            using type = typename _detail::_select<T, sizeof(T) < sizeof(float),
                                                float,
                                                double,
                                                long double>::type;
        };
    }
}

namespace std_copy
{
    //is_signed
    template <class T>
    struct is_signed
        : _std_copy_hidden::_std_copy_type_traits::_is_signed_helper<T> {};
    template <class T>
    constexpr bool is_signed_v = is_signed<T>::value;

    //is_unsigned
    template <class T>
    struct is_unsigned
        : _std_copy_hidden::_std_copy_type_traits::_is_unsigned_helper<T> {};
    template <class T>
    constexpr bool is_unsigned_v = is_unsigned<T>::value;

    //is_base_of
    template <class T, class U>
    struct is_base_of
        : bool_constant<
            is_class<T>::value && is_class<U>::value &&
            decltype(_std_copy_hidden::_std_copy_type_traits::test_if_base<T, U>(0))::value
        >
    {};
}

#endif /* _STD_COPY_TYPE_TRAITS */