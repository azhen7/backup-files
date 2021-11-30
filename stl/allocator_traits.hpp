#ifndef _STD_COPY_ALLOCATOR_TRAITS
#define _STD_COPY_ALLOCATOR_TRAITS

#include "allocator.hpp"
#include "pointer_traits.hpp"
#include "construct_destroy.hpp"
#include "type_traits.hpp"

namespace std_copy
{
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
            class _has_construct
            {
                private:
                    typedef int yes;
                    typedef char no;

                    template <class C>
                    static yes& test(decltype(&C::construct));

                    template <class C>
                    static no& test(...);
                
                public:
                    static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
            };

            //Check if allocator object has destroy function
            template <class C>
            class _has_destroy
            {
                private:
                    typedef int yes;
                    typedef char no;

                    template <class T>
                    static yes& test(decltype(&T::destroy));

                    template <class T>
                    static no& test(...);
                
                public:
                    static constexpr bool value = sizeof(test<C>(0)) == sizeof(yes);
            };

            //Checks if allocator object has select_on_container_copy_construction function
            template <class C>
            class _has_select_on_container_copy_construction
            {
                private:
                    typedef int yes;
                    typedef char no;

                    template <class T>
                    static yes& test(decltype(&T::select_on_container_copy_construction));

                    template <class T>
                    static no& test(...);

                public:
                    static constexpr bool value = sizeof(test<C>(0)) == sizeof(yes);
            };
            
            //_pointer_traits_rebind
            template <class Ptr, class T>
            using _pointer_traits_rebind = typename pointer_traits<Ptr>::rebind<T>;

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
            using pointer              =    _std_copy_hidden::_detector_t<value_type*, _pointer, Alloc>;
            using const_pointer        =    _std_copy_hidden::_detector_t<_pointer_traits_rebind<pointer, const value_type*>, _const_pointer, Alloc>;
            using void_pointer         =    _std_copy_hidden::_detector_t<_pointer_traits_rebind<pointer, void>, _void_pointer, Alloc>;
            using const_void_pointer   =    _std_copy_hidden::_detector_t<_pointer_traits_rebind<pointer, const void>, _const_void_pointer, Alloc>;
            using difference_type      =    _std_copy_hidden::_detector_t<long long, _diff_type, Alloc>;
            using size_type            =    _std_copy_hidden::_detector_t<unsigned long long, _size_type, Alloc>;

            /**
             * This function allocates n elements and returns a 
             * pointer to the first element.
             * @param a The allocator object used to allocate the memory.
             * @param n The amount of element to allocate.
            */
            [[nodiscard]] static constexpr pointer allocate(allocator_type& a, size_type n)
            {
                a.allocate(n);
            }
            /**
             * This function deallocates n elements starting from ptr.
             * @param a The allocator object used to deallocate the memory.
             * @param ptr The element to start deallocating from.
             * @param n The number of elements after ptr to start deallocating.
            */
            static constexpr void deallocate(allocator_type& a, pointer ptr, size_type n)
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
            static constexpr void construct(allocator_type& a, pointer ptr, Args&&... args)
            {
                if constexpr(_has_construct<allocator_type>::value)
                    a.construct(ptr, forward<Args>(args)...);
                else
                    construct_at(ptr, forward<Args>(args)...);
            }
            /**
             * This function destroys an object.
             * @param a The allocator object used to destroy the object.
             * @param ptr The location of the object to destroy.
            */
            static constexpr void destroy(allocator_type& a, pointer ptr)
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
            static constexpr allocator_type select_on_container_copy_construction(allocator_type& a)
            {
                if constexpr(_has_select_on_container_copy_construction<allocator_type>::value)
                    return a.select_on_container_copy_construction();
                return a;
            }
    };
    /**
     * Partial specialization for allocator<T>.
    */
    template <class T>
    class allocator_traits<allocator<T>>
    {
        public:
            typedef allocator<T>            allocator_type;
            typedef T                       value_type;
            typedef T*                      pointer;
            typedef const T*                const_pointer;
            typedef void*                   void_pointer;
            typedef const void*             const_void_pointer;
            typedef unsigned long long      size_type;
            typedef long long               difference_type;

            /**
             * This function allocates n elements and returns a 
             * pointer to the first element.
             * @param a The allocator object used to allocate the memory.
             * @param n The amount of element to allocate.
            */
            [[nodiscard]] static constexpr pointer allocate(allocator_type& a, size_type n)
            {
                a.allocate(n);
            }
            /**
             * This function deallocates n elements starting from ptr.
             * @param a The allocator object used to deallocate the memory.
             * @param ptr The element to start deallocating from.
             * @param n The number of elements after ptr to start deallocating.
            */
            static constexpr void deallocate(allocator_type& a, pointer ptr, size_type n)
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
            static constexpr void construct(allocator_type& a, pointer ptr, Args&&... args)
            {
                construct_at(ptr, forward<Args>(args)...);
            }
            /**
             * This function destroys an object.
             * @param a The allocator object used to destroy the object.
             * @param ptr The location of the object to destroy.
            */
            static constexpr void destroy(allocator_type& a, pointer ptr)
            {
                destroy_at(ptr);
            }
            /**
             * This function obtains an allocator to be used for 
             * copy construction.
             * @param a The allocator type used.
            */
            static constexpr allocator_type select_on_container_copy_construction(allocator_type& a)
            {
                return a;
            }
    };
}

#endif