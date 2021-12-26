#ifndef _STD_COPY_ALLOCATOR
#define _STD_COPY_ALLOCATOR

#include <new>
#include <cstdint>
#include "type_traits.hpp"

#if __cplusplus > 201703L
namespace _std_copy_hidden
{
    namespace _std_copy_allocator
    {
        template <class Allocator>
        concept _is_valid_allocator =
        requires(typename Allocator::value_type* randomPtr)
        {
            typename Allocator::size_type;
            typename Allocator::difference_type;
            {Allocator()};
            {Allocator::allocate(0)};
            {Allocator::deallocate(randomPtr, 0)};
        };
    }
}
#endif

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
            typedef std::size_t         size_type;
            typedef std::ptrdiff_t      difference_type;
            typedef true_type           propagate_on_container_move_assignment;

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