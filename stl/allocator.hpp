#ifndef _STD_COPY_ALLOCATOR
#define _STD_COPY_ALLOCATOR

#include <new>
#include "pointer_traits.hpp"
#include "type_traits.hpp"
#include "move.hpp"

namespace std_copy
{
    /**
     * Constructs an object at a particular location in memory.
     * @param location The location to construct the object.
     * @param args The arguments forwarded to the object's constructor.
    */
    template <class T, class ...Args>
    constexpr void construct_at(T* location, Args&&... args)
    {
        ::new (static_cast<void*>(location)) T(std_copy::forward<Args>(args)...);
    }
    /**
     * Destroys an object at a particular location in memory.
     * @param ptr The location in memory.
    */
    template <class T>
    constexpr void destroy_at(T* ptr)
    {
        if constexpr(is_array<T>::value)
        {
            for (T& elem : *ptr)
                destroy_at(std_copy::addressof(elem));
        }
        else
            ptr->~T();
    }

    /**
     * This is my implementation of std::allocator, defined in the 
     * <memory> header file.
    */
    template <class T>
    class allocator
    {
        public:
            typedef T                   value_type;
            typedef unsigned long long  size_type;
            typedef long long           difference_type;

            /**
             * This function allocates n elements and returns a 
             * pointer to the first element.
             * @param n The amount of element to allocate.
            */
            [[nodiscard]] static constexpr value_type* allocate(size_type n)
            {
                if (n == 0)
                    return nullptr;

                if (n > size_type(-1) / sizeof(T))
                    throw std::bad_array_new_length();

                return new value_type[n];
            }
            /**
             * This function deallocates n elements starting from ptr.
             * @param ptr The element to start deallocating from.
             * @param n The number of elements after ptr to start deallocating.
            */
            static constexpr void deallocate(value_type* ptr, size_type n)
            {
                for (size_type i = 0; i < n; i++)
                    (ptr + i)->~value_type();
            }
    };
    
}

#endif /* _STD_COPY_ALLOCATOR */