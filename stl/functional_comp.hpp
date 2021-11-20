#ifndef _STD_COPY_FUNCTIONAL_COMP
#define _STD_COPY_FUNCTIONAL_COMP

namespace std_copy
{
    //Basic arithmetic operations
    /**
     * Struct object performing addition on two elements.
    */
    template <class T>
    struct plus
    {
        constexpr T operator()(const T& a, const T& b)
        {
            return a + b;
        }
    };
    /**
     * Partial specialization of plus performing 
     * type deduction.
    */
    template <>
    struct plus<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) + forward<U>(b))
        {
            return a + b;
        }
    };

    /**
     * Struct object performing subtraction on two elements.
    */
    template <class T>
    struct minus
    {
        constexpr T operator()(const T& a, const T& b)
        {
            return a - b;
        }
    };
    /**
     * Partial specialization of minus performing 
     * type deduction.
    */
    template <>
    struct minus<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) - forward<U>(b))
        {
            return a - b;
        }
    };

    /**
     * Struct object performing multiplication on two elements.
    */
    template <class T>
    struct multiplies
    {
        constexpr T operator()(const T& a, const T& b)
        {
            return a * b;
        }
    };
    /**
     * Partial specialization of multiplies performing 
     * type deduction.
    */
    template <>
    struct multiplies<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) * forward<U>(b))
        {
            return a * b;
        }
    };

    /**
     * Struct object performing division on two elements.
    */
    template <class T>
    struct divides
    {
        constexpr T operator()(const T& a, const T& b)
        {
            return a / b;
        }
    };
    /**
     * Partial specialization of divides performing 
     * type deduction.
    */
    template <>
    struct divides<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) / forward<U>(b))
        {
            return a / b;
        }
    };

    /**
     * Struct object performing mod on two elements.
    */
    template <class T>
    struct modulus
    {
        constexpr T operator()(const T& a, const T& b)
        {
            return a % b;
        }
    };
    /**
     * Partial specialization of modulus performing type 
     * deduction.
    */
    template <>
    struct modulus<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) % forward<U>(b))
        {
            return a % b;
        }
    };

    /**
     * Struct object negating an element.
    */
    template <class T>
    struct negate
    {
        constexpr T operator()(const T& a)
        {
            return -a;
        }
    };
    /**
     * Partial specialization of negate performing type 
     * deduction.
    */
    template <>
    struct negate<void>
    {
        template <class T>
        auto operator()(T&& a)
            -> decltype(forward<T>(a))
        {
            return -a;
        }
    };

    //Basic equality checks
    /**
     * Struct object checking equality between two values.
    */
    template <class T>
    struct equal_to
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a == b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct equal_to<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) == forward<U>(b))
        {
            return a == b;
        }
    };

    /**
     * Struct object checking inequality between two values.
    */
    template <class T>
    struct not_equal_to
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a != b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct not_equal_to<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) != forward<U>(b))
        {
            return a != b;
        }
    };

    /**
     * Struct object checking if a < b.
    */
    template <class T>
    struct less
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a < b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct less<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) < forward<U>(b))
        {
            return a < b;
        }
    };

    /**
     * Struct object checking if a > b.
    */
    template <class T>
    struct greater
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a > b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct greater<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) > forward<U>(b))
        {
            return a > b;
        }
    };

    /**
     * Struct object checking if a <= b.
    */
    template <class T>
    struct less_equal
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a <= b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct less_equal<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) <= forward<U>(b))
        {
            return a <= b;
        }
    };

    /**
     * Struct object checking if a >= b.
    */
    template <class T>
    struct greater_equal
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a >= b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct greater_equal<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) >= forward<U>(b))
        {
            return a >= b;
        }
    };

    //Logical operations
    /**
     * Struct object performing logical and on two elements.
    */
    template <class T>
    struct logical_and
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a && b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct logical_and<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) && forward<U>(b))
        {
            return a && b;
        }
    };

    /**
     * Struct object performing logical and on two elements.
    */
    template <class T>
    struct logical_or
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a || b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct logical_or<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b)
            -> decltype(forward<T>(a) || forward<U>(b))
        {
            return a || b;
        }
    };

    /**
     * Struct object performing logical and on two elements.
    */
    template <class T>
    struct logical_not
    {
        constexpr bool operator()(const T& a)
        {
            return !a;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct logical_not<void>
    {
        template <class T>
        auto operator()(T&& a)
            -> decltype(!forward<T>(a))
        {
            return !a;
        }
    };

    //Bitwise operations
    /**
     * Struct object performing bitwise and on two elements.
    */
    template <class T>
    struct bit_and
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a & b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct bit_and<void>
    {
        template <class T, class I>
        auto operator()(T&& a, I&& b)
            -> decltype(forward<T>(a) & forward<I>(b))
        {
            return a & b;
        }
    };

    /**
     * Struct object performing bitwise or on two elements.
    */
    template <class T>
    struct bit_or
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a | b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct bit_or<void>
    {
        template <class T, class I>
        auto operator()(T&& a, I&& b)
            -> decltype(forward<T>(a) | forward<I>(b))
        {
            return a | b;
        }
    };

    /**
     * Struct object performing bitwise xor on two elements.
    */
    template <class T>
    struct bit_xor
    {
        constexpr bool operator()(const T& a, const T& b)
        {
            return a ^ b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct bit_xor<void>
    {
        template <class T, class I>
        auto operator()(T&& a, I&& b)
            -> decltype(forward<T>(a) ^ forward<I>(b))
        {
            return a ^ b;
        }
    };

    /**
     * Struct object performing bitwise not on two elements.
    */
    template <class T>
    struct bit_not
    {
        constexpr bool operator()(const T& a)
        {
            return ~a;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct bit_not<void>
    {
        template <class T>
        auto operator()(T&& a)
            -> decltype(~forward<T>(a))
        {
            return ~a;
        }
    };

    //identity
    template <class T>
    struct identity
    {
        T operator()(const T& a)
        {
            return forward<T>(a);
        }
    };
}

#endif /* _STD_COPY_FUNCTIONAL_COMP */