#ifndef _STD_COPY_MOVE
#define _STD_COPY_MOVE

#include "type_traits.hpp"

namespace _std_copy_hidden
{
    namespace _std_copy_move
    {
        template <class T, class U = T&&>
        U _declval_helper(int);

        template <class T>
        T _declval_helper(long);
    }
}

namespace std_copy
{
    /**
     * This function returns an rvalue reference to the argument 
     * passed in, allowing for efficient transportation.
     * @param val The object to "move".
    */
    template <class T>
    constexpr remove_reference_t<T>&& move(T&& val)
    {
        return static_cast<remove_reference_t<T>&&>(val);
    } 
    /**
     * This function forwards an lvalue. This function is used to 
     * implement "perfect forwarding".
     * @param val The object to forward.
    */
    template <class T>
    constexpr remove_reference_t<T>&& forward(remove_reference_t<T>& val)
    {
        return static_cast<remove_reference_t<T>&&>(val);
    }
    /**
     * This function forwards an rvalue. This function is used to 
     * implement "perfect forwarding".
     * @param val The object to forward.
    */
    template <class T>
    constexpr remove_reference_t<T>&& forward(remove_reference_t<T>&& val)
    {
        static_assert(!is_lvalue_reference<T>::value, 
                     "template argument substituting T is an lvalue reference type");
        return static_cast<remove_reference_t<T>&&>(val);
    }
    /**
     * Converts any type T to a reference type, allowing it 
     * to be used in decltype expressions.
    */
    template <class T>
    auto declval() -> decltype(_std_copy_hidden::_std_copy_move::_declval_helper<T>(0))
    {
        return _std_copy_hidden::_std_copy_move::_declval_helper<T>(0);
    }
}

#endif /* _STD_COPY_MOVE */