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
        constexpr operator()() {
            return value;
        }
    };
    //true_type
    typedef integral_constant<bool, true>   true_type;
    //false_type
    typedef integral_constant<bool, false>  false_type;

    //remove reference
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

    //remove pointer
    template <class T>
    struct remove_pointer {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<T*> {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<T* const> {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<T* volatile> {
        typedef T   type;
    };
    template <class T>
    struct remove_pointer<T* const volatile> {
        typedef T   type;
    };

    //add pointer
    template <class T>
    struct add_pointer {
        typedef typename remove_reference<T>::type*  type;
    };
}

#endif