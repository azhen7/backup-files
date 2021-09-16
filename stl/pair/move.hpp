#ifndef _STD_COPY_MOVE
#define _STD_COPY_MOVE

namespace std_copy {
    template <class T>
    constexpr T&& move(T&& val) {
        return static_cast<T&&>(val);
    }
}

#endif /* _STD_COPY_MOVE */