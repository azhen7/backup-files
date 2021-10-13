#ifndef _STD_COPY_ALLOCATOR
#define _STD_COPY_ALLOCATOR

#include "move.hpp"
#include "type_traits.hpp"
#include <new>

namespace std_copy {
    /**
     * Constructs an object at a particular location in memory.
     * @param location The location to construct the object.
     * @param args The arguments forwarded to the object's constructor.
    */
    template <class T, class ...Args>
    constexpr void construct_at(T* location, Args&&... args) {
        ::new (static_cast<void*>(location)) T(std_copy::forward<Args>(args)...);
    }
    /**
     * Destroys an object at a particular location in memory.
     * @param ptr The location in memory.
    */
    template <class T>
    constexpr void destroy_at(T* ptr) {
        if (is_array<T>::value) {
            for (T& elem : *ptr) {
                destroy_at(std_copy::addressof(elem));
            }
        }
        else {
            ptr->~T();
        }
    }

    /**
     * This is my implementation of std::allocator, defined in the 
     * <memory> header file.
    */
    template <class T>
    class allocator {
        public:
            typedef T                   value_type;
            typedef unsigned long long  size_type;
            typedef long long           difference_type;

            /**
             * This function allocates n elements and returns a 
             * pointer to the first element.
             * @param n The amount of element to allocate.
            */
            [[nodiscard]] static value_type* allocate(size_type n) {
                if (n == 0)
                    return nullptr;

                if (n > static_cast<size_type>(-1) / sizeof(T)) {
                    throw std::bad_array_new_length("Requested size to allocate exceeded the maximum allocatable amount of memory");
                }

                return new value_type[n];
            }
            /**
             * This function deallocates n elements starting from ptr.
             * @param ptr The element to start deallocating from.
             * @param n The number of elements after ptr to start deallocating.
            */
            static constexpr void deallocate(value_type* ptr, size_type n) {
                for (size_type i = 0; i < n; i++) {
                    (ptr + i)->~value_type();
                }
            }
    };
    /**
     * My own implementation of std::allocator_traits, defined in the 
     * <memory> header file.
    */
    template <class Alloc>
    class allocator_traits {
        private:
            //Check if allocator object has construct function
            template <class T>
            struct _has_construct {
                private:
                    typedef int yes;
                    typedef char no;

                    template <class C>
                    static yes& test(decltype(&C::construct));

                    template <class C>
                    static no& test(...);
                
                public:
                    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
            };

            //Check if allocator object has destroy function
            template <class C>
            struct _has_destroy {
                private:
                    typedef int yes;
                    typedef char no;

                    template <class T>
                    static yes& test(decltype(&T::destroy));

                    template <class T>
                    static no& test(...);
                
                public:
                    static const bool value = sizeof(test<C>(0)) == sizeof(yes);
            };
            

        public:
            typedef Alloc                                    allocator_type;
            typedef typename Alloc::value_type               value_type;
            typedef typename Alloc::pointer                  pointer;
            typedef typename Alloc::const_pointer            const_pointer;
            typedef typename Alloc::void_pointer             void_pointer;
            typedef typename Alloc::const_void_pointer       const_void_pointer;
            typedef typename Alloc::size_type                size_type;
            typedef typename Alloc::difference_type          difference_type;

            /**
             * This function allocates n elements and returns a 
             * pointer to the first element.
             * @param a The allocator object used to allocate the memory.
             * @param n The amount of element to allocate.
            */
            [[nodiscard]] static constexpr pointer allocate(allocator_type& a, size_type n) {
                a.allocate(n);
            }
            /**
             * This function deallocates n elements starting from ptr.
             * @param a The allocator object used to deallocate the memory.
             * @param ptr The element to start deallocating from.
             * @param n The number of elements after ptr to start deallocating.
            */
            static constexpr void deallocate(allocator_type& a, pointer ptr, size_type n) {
               a.deallocate(ptr, n);
            }
            /**
             * This function constructs an element at ptr.
             * @param a The allocator object used to construct the object.
             * @param ptr The location to construct the element at.
             * @param args The arguments that are forwarded to the constructor of the 
             * type of the object.
            */
            template <class ...Args>
            static constexpr void construct(allocator_type& a, pointer ptr, Args&&... args) {
                if (_has_construct<allocator_type>::value) {
                    a.construct(ptr, std_copy::forward<Args>(args)...);
                }
                else {
                    construct_at(ptr, std_copy::forward<Args>(args)...);
                }
            }
            /**
             * This function destroys an object.
             * @param a The allocator object used to destroy the object.
             * @param ptr The location of the object to destroy.
            */
            static constexpr void destroy(allocator_type& a, pointer ptr) {
                if (_has_destroy<allocator_type>::value) {
                    a.destroy(ptr);
                }
                else {
                    destroy_at(ptr);
                }
            }
    };
}

#endif /* _STD_COPY_ALLOCATOR */