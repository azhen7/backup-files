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
    void swap(T& a, T& b) {
        T temp = move(a);
        a = move(b);
        b = move(temp);
    }
    /**
     * This function swaps the values of the elements of 
     * two arrays.
     * @param a The first array.
     * @param b The second array.
    */
    template <class T, unsigned long long N>
    void swap(T (&a)[N], T (&b)[N]) {
        for (unsigned long long i = 0; i < N; i++) {
            T temp = move(a[i]);
            a[i] = move(b[i]);
            b[i] = move(temp);
        }
    }
}

#endif /* _STD_COPY_UTILITY */