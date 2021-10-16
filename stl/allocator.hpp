#ifndef _STD_COPY_ALLOCATOR
#define _STD_COPY_ALLOCATOR

#include <new>
#include "pointer_traits.hpp"

#define STATIC_CONSTEXPR static constexpr
#define NODISCARD [[nodiscard]]

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
            NODISCARD STATIC_CONSTEXPR value_type* allocate(size_type n)
            {
                if (n == 0)
                    return nullptr;

                if (n > static_cast<size_type>(-1) / sizeof(T))
                    throw std::bad_array_new_length();

                return new value_type[n];
            }
            /**
             * This function deallocates n elements starting from ptr.
             * @param ptr The element to start deallocating from.
             * @param n The number of elements after ptr to start deallocating.
            */
            STATIC_CONSTEXPR void deallocate(value_type* ptr, size_type n)
            {
                for (size_type i = 0; i < n; i++)
                    (ptr + i)->~value_type();
            }
    };
    /**
     * My own implementation of std::allocator_traits, defined in the 
     * <memory> header file.
    */
    template <class Alloc>
    class allocator_traits
    {
        private:
            //Check if allocator object has construct function
            template <class T>
            struct _has_construct
            {
                private:
                    typedef int yes;
                    typedef char no;

                    template <class C>
                    static yes& test(decltype(&C::construct));

                    template <class C>
                    static no& test(...);
                
                public:
                    STATIC_CONSTEXPR bool value = sizeof(test<T>(0)) == sizeof(yes);
            };

            //Check if allocator object has destroy function
            template <class C>
            struct _has_destroy
            {
                private:
                    typedef int yes;
                    typedef char no;

                    template <class T>
                    static yes& test(decltype(&T::destroy));

                    template <class T>
                    static no& test(...);
                
                public:
                    STATIC_CONSTEXPR bool value = sizeof(test<C>(0)) == sizeof(yes);
            };

            //Checks if allocator object has select_on_container_copy_construction function
            template <class C>
            struct _has_select_on_container_copy_construction
            {
                private:
                    typedef int yes;
                    typedef char no;

                    template <class T>
                    static yes& test(decltype(&T::select_on_container_copy_construction));

                    template <class T>
                    static no& test(...);

                public:
                    STATIC_CONSTEXPR bool value = sizeof(test<C>(0)) == sizeof(yes);
            };
            
            //pointer_traits_rebind_
            template <class Ptr, class T>
            using pointer_traits_rebind_ = typename pointer_traits<Ptr>::rebind<T>;

            
            template <class T>
            using _pointer             =    typename T::pointer;
            template <class T>
            using _const_pointer       =    typename T::const_pointer;
            template <class T>
            using _void_pointer        =    typename T::void_pointer;
            template <class T>
            using _const_void_pointer  =    typename T::const_void_pointer;
            template <class T>
            using _diff_type           =    typename T::difference_type;
            template <class T>
            using _size_type           =    typename T::size_type;

        public:
            using allocator_type       =    Alloc;
            using value_type           =    typename Alloc::value_type;
            using pointer              =    detector_t<value_type*, _pointer, Alloc>;
            using const_pointer        =    detector_t<pointer_traits_rebind_<pointer, const value_type*>, _const_pointer, Alloc>;
            using void_pointer         =    detector_t<pointer_traits_rebind_<pointer, void>, _void_pointer, Alloc>;
            using const_void_pointer   =    detector_t<pointer_traits_rebind_<pointer, const void>, _const_void_pointer, Alloc>;
            using difference_type      =    detector_t<long long, _diff_type, Alloc>;
            using size_type            =    detector_t<unsigned long long, _size_type, Alloc>;

            /**
             * This function allocates n elements and returns a 
             * pointer to the first element.
             * @param a The allocator object used to allocate the memory.
             * @param n The amount of element to allocate.
            */
            NODISCARD STATIC_CONSTEXPR pointer allocate(allocator_type& a, size_type n)
            {
                a.allocate(n);
            }
            /**
             * This function deallocates n elements starting from ptr.
             * @param a The allocator object used to deallocate the memory.
             * @param ptr The element to start deallocating from.
             * @param n The number of elements after ptr to start deallocating.
            */
            STATIC_CONSTEXPR void deallocate(allocator_type& a, pointer ptr, size_type n)
            {
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
            STATIC_CONSTEXPR void construct(allocator_type& a, pointer ptr, Args&&... args)
            {
                if constexpr(_has_construct<allocator_type>::value)
                    a.construct(ptr, std_copy::forward<Args>(args)...);
                else
                    construct_at(ptr, std_copy::forward<Args>(args)...);
            }
            /**
             * This function destroys an object.
             * @param a The allocator object used to destroy the object.
             * @param ptr The location of the object to destroy.
            */
            STATIC_CONSTEXPR void destroy(allocator_type& a, pointer ptr)
            {
                if constexpr(_has_destroy<allocator_type>::value)
                    a.destroy(ptr);
                else
                    destroy_at(ptr);
            }
            /**
             * This function obtains an allocator to be used for 
             * copy construction.
             * @param a The allocator type used.
            */
            STATIC_CONSTEXPR allocator_type select_on_container_copy_construction(allocator_type& a)
            {
                if constexpr(_has_select_on_container_copy_construction<allocator_type>::value)
                    return a.select_on_container_copy_construction();
                return a;
            }
    };
}

#endif /* _STD_COPY_ALLOCATOR */