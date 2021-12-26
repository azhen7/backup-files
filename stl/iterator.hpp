#ifndef _STD_COPY_ITERATOR
#define _STD_COPY_ITERATOR

#include "iterator_traits.hpp"
#include "iterator_funcs.hpp"
#include "iterator_concepts.hpp"

#include <cstdint>

namespace std_copy
{
    /**
     * Returns a pointer to the beginning of a C-style array.
     * @param arr The array.
    */
    template <class T, std::size_t N>
    T* begin(T (&arr)[N])
    {
        return arr;
    }
    /**
     * Returns a pointer to the end of a C-style array.
     * @param arr The array.
    */
    template <class T, std::size_t N>
    T* end(T (&arr)[N])
    {
        return arr + N;
    }
}

#endif /* _STD_COPY_ITERATOR */