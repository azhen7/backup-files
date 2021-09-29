#ifndef _STD_COPY_MOVE
#define _STD_COPY_MOVE

#include "type_traits.hpp"

namespace std_copy {
    /**
     * This function returns an rvalue reference to the argument 
     * passed in, allowing for efficient transportation.
     * @param val The object to "move".
    */
    template <class T>
    constexpr remove_reference_t<T>&& move(T&& val) {
        return static_cast<remove_reference_t<T>&&>(val);
    }
}

#endif /* _STD_COPY_MOVE */