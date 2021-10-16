#ifndef _STD_COPY_MOVE
#define _STD_COPY_MOVE

#include "type_traits.hpp"

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
     * This function returns the actual address of an object referenced 
     * by val, even in the presence of an overloaded operator&.
    */
    template <class T>
    T* addressof(T& f)
    {
        return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(f)));
    }

}

#endif /* _STD_COPY_MOVE */