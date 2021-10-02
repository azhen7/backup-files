#ifndef _STD_COPY_TYPE_TRAITS
#define _STD_COPY_TYPE_TRAITS

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
        constexpr T operator()() {
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
    struct type_identity {
        typedef T   type;
    };
    template <class T>
    using type_identity_t = typename type_identity<T>::type;

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

    //remove_cvref
    template <class T>
    struct remove_cvref {
        typedef remove_reference_t<remove_cv_t<T>>  type;
    };
    template <class T>
    using remove_cvref_t = typename remove_cvref<T>::type;

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

    //remove_extent
    template <class T>
    struct remove_extent {
        typedef T   type;
    };
    template <class T>
    struct remove_extent<T[]> {
        typedef T   type;
    };
    template <class T, unsigned long long N>
    struct remove_extent<T[N]> {
        typedef T   type;
    };
    template <class T>
    using remove_extent_t = typename remove_extent<T>::type;

    //remove_all_extents
    template <class T>
    struct remove_all_extents {
        typedef T   type;
    };
    template <class T>
    struct remove_all_extents<T[]> {
        typedef T   type;
    };
    template <class T, unsigned long long N>
    struct remove_all_extents<T[N]> {
        typedef T   type;
    };
    template <class T>
    using remove_all_extents_t = typename remove_all_extents<T>::type;

    //add_pointer
    template <class T>
    struct add_pointer {
        typedef typename remove_reference<T>::type*  type;
    };
    
    //extent
    template <class T, unsigned long long N>
    struct extent
        : integral_constant<unsigned long long, 0>
    {
    };
    template <class T, unsigned long long I>
    struct extent<T[I], 0>
        : integral_constant<unsigned long long, I>
    {
    };
    template <class T, unsigned long long N>
    struct extent<T[], N> 
        : extent<T, N - 1>
    {
    };
    template <class T, unsigned long long I, unsigned long long N>
    struct extent<T[I], N>
        : extent<T, N - 1>
    {
    };

    //Type properties

    //is_void
    template <class T>
    struct is_void
        : false_type
    {
    };
    template <>
    struct is_void<void>
        : true_type
    {
    };
    template <class T>
    using is_void_v = is_void<T>::value;

    //is_array
    template <class T>
    struct is_array
        : false_type
    {
    };
    template <class T>
    struct is_array<T[]>
        : true_type
    {
    };
    template <class T, unsigned long long N>
    struct is_array<T[N]>
        : true_type
    {
    };
    template <class T>
    using is_array_v = is_array<T>::value;

    //is_bounded_array
    template <class T>
    struct is_bounded_array
        : false_type
    {
    };
    template <class T, unsigned long long N>
    struct is_bounded_array<T[N]>
        : true_type
    {
    };
    template <class T>
    using is_bounded_array_v = is_bounded_array<T>::value;

    //is_unbounded_array
    template <class T>
    struct is_unbounded_array
        : false_type
    {
    };
    template <class T>
    struct is_unbounded_array<T[]>
        : true_type
    {
    };
    template <class T>
    using is_unbounded_array_v = is_unbounded_array<T>::value;

    //is_lvalue_reference
    template <class T>
    struct is_lvalue_reference
        : false_type
    {
    };
    template <class T>
    struct is_lvalue_reference<T&>
        : true_type
    {
    };
    template <class T>
    using is_lvalue_reference_v = is_lvalue_reference<T>::value;

    //is_rvalue_reference
    template <class T>
    struct is_rvalue_reference
        : false_type
    {
    };
    template <class T>
    struct is_rvalue_reference<T&&>
        : true_type
    {
    };
    template <class T>
    using is_rvalue_reference_v = is_rvalue_reference<T>::value;

    //is_reference
    template <class T>
    struct is_reference
        : false_type
    {
    };
    template <class T>
    struct is_reference<T&>
        : true_type
    {
    };
    template <class T>
    struct is_reference<T&&>
        : true_type
    {
    };
    template <class T>
    using is_reference_v = is_reference<T>::value;

    //is_const
    template <class T>
    struct is_const
        : false_type
    {
    };
    template <class T>
    struct is_const<const T>
        : true_type
    {
    };
    template <class T>
    using is_const_v = is_const<T>::value;

    //is_volatile
    template <class T>
    struct is_volatile
        : false_type
    {
    };
    template <class T>
    struct is_volatile<volatile T>
        : true_type
    {
    };
    template <class T>
    using is_volatile_v = is_volatile<T>::value;

    //Miscellaneous transformations

    //conditional
    template <bool B, class ifTrue, class ifFalse>
    struct conditional {
        typedef ifTrue  type;
    };
    template <class ifTrue, class ifFalse>
    struct conditional<false, ifTrue, ifFalse> {
        typedef ifFalse  type;
    };

    //Operations of traits

    //negation
    template <class B>
    struct negation
        : bool_constant<!bool(B::value)>
    {
    };

}

#endif /* _STD_COPY_TYPE_TRAITS */