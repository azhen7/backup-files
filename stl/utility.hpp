#ifndef _STD_COPY_UTILITY
#define _STD_COPY_UTILITY

#include "move.hpp"
#include "pair.hpp"

namespace std_copy {
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
    template <class T, unsigned long long N>
    constexpr void swap(T (&a)[N], T (&b)[N])
    {
        for (unsigned long long i = 0; i < N; i++)
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
        old_val = std_copy::move(new_value);
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
}

#endif /* _STD_COPY_UTILITY */