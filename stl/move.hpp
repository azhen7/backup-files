#ifndef _STD_COPY_MOVE
#define _STD_COPY_MOVE

#include "type_traits.hpp"

namespace std_copy {
    template <class T>
    constexpr typename remove_reference<T>::type&& move(T&& val) {
        return static_cast<typename remove_reference<T>::type&&>(val);
    }
}

#endif /* _STD_COPY_MOVE */