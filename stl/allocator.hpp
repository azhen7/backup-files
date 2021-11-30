#ifndef _STD_COPY_ALLOCATOR
#define _STD_COPY_ALLOCATOR

#include <new>

namespace std_copy
{
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
                if (n == 0)
                    return;
                ::operator delete(ptr, n * sizeof(T));
            }
    };
    
}

#endif /* _STD_COPY_ALLOCATOR */