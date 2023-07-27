#ifndef _STD_COPY_ALLOCATOR_TRAITS
#define _STD_COPY_ALLOCATOR_TRAITS

#include <cstdint>

#include "allocator.hpp"
#include "pointer_traits.hpp"
#include "construct_destroy.hpp"
#include "type_traits.hpp"
#include "move.hpp"

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
                protected:
                    typedef wchar_t yes;
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
                protected:
                    typedef wchar_t yes;
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
                protected:
                    typedef wchar_t yes;
                    typedef char no;

                    template <class T>
                    static yes& test(decltype(&T::select_on_container_copy_construction));

                    template <class T>
                    static no& test(...);

                public:
                    static constexpr bool value = sizeof(test<C>(0)) == sizeof(yes);
            };

            template <class T, class U, typename = void>
            struct _rebind : _std_copy_hidden::_std_copy_type_traits::_replace_first_arg<T, U>
            {
            };

            template <class T, class U>
            struct _rebind<T, U, void_t<typename T::rebind<U>::other>>
            {
                typedef typename T::rebind<U>::other type;
            };
            
            //_pointer_traits_rebind
            template <class Ptr, class T>
            using _pointer_traits_rebind = typename pointer_traits<Ptr>::rebind<T>;

            template <class T>
            using _pointer             =    typename T::pointer;

        public:
            using pointer              =    _std_copy_hidden::_detector_t<value_type*, _pointer, Alloc>;

        private:
            template <class T>
            using _const_pointer       =    typename T::const_pointer;
            template <class T>
            using _void_pointer        =    typename T::void_pointer;
            template <class T>
            using _const_void_pointer  =    typename T::const_void_pointer;

            template <template<typename> class P, class T, typename = void>
            struct _pointer
            {
                using type = pointer_traits<pointer>::rebind<T>;
            };
            template <template<typename> class P, class T>
            struct _pointer<P, T, void_t<P<Alloc>>>
            {
                using type = P<Alloc>;
            };

            //difference_type
            template <class T, class P, typename = void>
            struct _diff
            {
                using type = pointer_traits<P>::difference_type;
            };
            template <class T, class P>
            struct _diff<T, P, void_t<typename T::difference_type>>
            {
                using type = typename T::difference_type;
            };

            //size_type
            template <class T, class P, typename = void>
            struct _size
            {
                using type = make_unsigned_t<typename _diff<T, P>::type>;
            };
            template <class T, class P>
            struct _size<T, P, void_t<typename T::size_type>>
            {
                using type = typename T::size_type;
            };

        public:
            using allocator_type       =    Alloc;
            using value_type           =    typename Alloc::value_type;
            using const_pointer        =    typename _pointer<_const_pointer, const value_type>::type;
            using void_pointer         =    typename _pointer<_void_pointer, void>::type;
            using const_void_pointer   =    typename _pointer<_const_void_pointer, const void>::type;
            using difference_type      =    typename _diff<Alloc, pointer>::type;
            using size_type            =    typename _size<Alloc, pointer>::type;

            template <class U>
            using rebind_alloc         =    _rebind<Alloc, U>::type;
            template <class U>
            using rebind_traits        =    allocator_traits<rebind_alloc<U>>;

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
            typedef std::size_t             size_type;
            typedef std::ptrdiff_t          difference_type;

            template <class U>
            using rebind_alloc          =   allocator<U>;
            template <class U>
            using rebind_traits         =   allocator_traits<allocator<U>>;

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