#ifndef _STD_COPY_UTILITY
#define _STD_COPY_UTILITY

#include "move.hpp"
#include "pair.hpp"
#include <cstdint>
#include "type_traits.hpp"

namespace std_copy
{
    /**
     * This function swaps the values of two parameters.
     * @param a The first parameter.
     * @param b The second paremeter.
    */
    template <class T>
    constexpr void swap(T& a, T& b)
    {
        T temp = std_copy::move(a);
        a = std_copy::move(b);
        b = std_copy::move(temp);
    }
    /**
     * This function swaps the values of the elements of 
     * two arrays.
     * @param a The first array.
     * @param b The second array.
    */
    template <class T, std::size_t N>
    constexpr void swap(T (&a)[N], T (&b)[N])
    {
        for (std::size_t i = 0; i < N; i++)
        {
            T temp = std_copy::move(a[i]);
            a[i] = std_copy::move(b[i]);
            b[i] = std_copy::move(temp);
        }
    }
    /**
     * This function exchanges the value of obj with 
     * new_value and returns the old value of obj.
     * @param obj The object to exchange the value with new_value.
     * @param new_value The value to replace the old value of obj.
    */
    template <class T, class U = T>
    T exchange(T& obj, U&& new_value)
    {
        T old_val = std_copy::move(obj);
        obj = std_copy::move(new_value);
        return old_val;
    }
    /**
     * This function returns an lvalue reference to const type 
     * of t.
     * @param t The object to return as const.
    */
    template <class T>
    constexpr add_const_t<T>& as_const(T& t)
    {
        return t;
    }

    /**
     * Comparison functions between integer types. Negative numbers
     * are guaranteed to always compare less than nonnegative numbers.
    */
    template <class T, class U>
    constexpr bool cmp_equal(T a, U b) noexcept
    {
        using UT = make_unsigned_t<T>;
        using UU = make_unsigned_t<U>;
        if constexpr(is_signed_v<T> == is_signed_v<U>)
        {
            return a == b;
        }
        else if constexpr(is_signed_v<T>)
        {
            //U is unsigned
            return a < 0 ? false : static_cast<UT>(a) == b;
        }
        else
        {
            return b < 0 ? false : a == static_cast<UT>(b);
        }
    }
    template <class T, class U>
    constexpr bool cmp_not_equal(T a, U b) noexcept
    {
        return !cmp_equal(a, b);
    }
    template <class T, class U>
    constexpr bool cmp_greater(T a, U b) noexcept
    {
        using UT = make_unsigned_t<T>;
        using UU = make_unsigned_t<U>;
        if constexpr(is_signed_v<T> == is_signed_v<U>)
        {
            return a > b;
        }
        else if constexpr(is_signed_v<T>)
        {
            //U is unsigned
            return a < 0 ? false : static_cast<UT>(a) > b;
        }
        else
        {
            return b < 0 ? true : a > static_cast<UT>(b);
        }
    }
    template <class T, class U>
    constexpr bool cmp_less(T a, U b)
    {
        return cmp_greater(b, a);
    }
    template <class T, class U>
    constexpr bool cmp_less_equal(T a, U b)
    {
        return !cmp_greater(a, b);
    }
    template <class T, class U>
    constexpr bool cmp_greater_equal(T a, U b)
    {
        return !cmp_less(a, b);
    }
}

#endif /* _STD_COPY_UTILITY */