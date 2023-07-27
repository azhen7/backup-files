#ifndef _STD_COPY_POINTER_TRAITS
#define _STD_COPY_POINTER_TRAITS

#include "type_traits.hpp"
#include "construct_destroy.hpp"

namespace std_copy
{
    /**
     * General interface for all pointer types.
    */
    template <class Ptr>
    class pointer_traits
    {
        protected:
            /**
             * _undefined: Replicates the behaviour of the value from other languages 
             * with "undefined" property such as "None" from Python and "undefined" from JS.
            */
            struct _undefined;

            //Gets first argument of template parameters
            template <class T>
            struct _get_first_arg
            {
                using type = _undefined;
            };
            template <template <typename, typename...> class Template, class T, class ...Args>
            struct _get_first_arg<Template<T, Args...>>
            {
                using type = T;
            };


            template <class T>
            using _element_type     =   typename T::element_type;
            template <class T>
            using _diff_type        =   typename T::difference_type;
            template <class T, class U>
            using _rebind           =   typename _std_copy_hidden::_std_copy_type_traits::_replace_first_arg<T, U>::type;

            template <class T>
            using _get_first_arg_t   =   typename _get_first_arg<T>::type;
            template <class T, class U>
            using _replace_first_arg_t = typename _std_copy_hidden::_std_copy_type_traits::_replace_first_arg<T, U>::type;

        public:
            using pointer           =   Ptr;
            using element_type      =   _std_copy_hidden::_detector_t<_get_first_arg_t<Ptr>, _element_type, Ptr>;
            using difference_type   =   _std_copy_hidden::_detector_t<std::ptrdiff_t, _diff_type, Ptr>;

            template <class U>
            using rebind            =   _std_copy_hidden::_detector_t<_replace_first_arg_t<Ptr, U>, _rebind, Ptr, U>;

            /**
             * Constructs a dereferenceable pointer to its argument.
             * @param arg The argument from which a pointer is constructed.
            */
            static pointer pointer_to(element_type& arg)
            {
                return pointer::pointer_to(arg);
            }
    };
    /**
     * Template specialization for pointer_traits.
    */
    template <class T>
    class pointer_traits<T*>
    {
        public:
            //typedefs
            typedef T*              pointer;
            typedef T               element_type;
            typedef std::ptrdiff_t  difference_type;

            template <class U>
            using rebind =          U*;

            /**
             * Constructs a dereferenceable pointer to its argument.
             * @param arg The argument from which a pointer is constructed.
            */
            static pointer pointer_to(element_type& arg)
            {
                return addressof(arg);
            }
    };
}

#endif /* _STD_COPY_POINTER_TRAITS */