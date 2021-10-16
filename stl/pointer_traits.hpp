#ifndef _STD_COPY_POINTER_TRAITS
#define _STD_COPY_POINTER_TRAITS

#include "type_traits.hpp"
#include "move.hpp"

namespace std_copy
{
    /**
     * General interface for all pointer types.
    */
    template <class Ptr>
    class pointer_traits
    {
        private:
            /**
             * undefined_: Replicates the behaviour of the value from other languages 
             * with "undefined" property such as "None" from Python and "undefined" from JS.
            */
            struct undefined_;

            //Gets first argument of template parameters
            template <class T>
            struct get_first_arg_
            {
                using type = undefined_;
            };
            template <template <typename, typename...> class Template, class T, class ...Args>
            struct get_first_arg_<Template<T, Args...>>
            {
                using type = T;
            };

            //Replace first argument of template parameters; used for rebind
            template <class T, class U>
            struct replace_first_arg_ 
            {
            };
            template <template <typename, typename...> class Template, class T, class U, class ...Args>
            struct replace_first_arg_<Template<T, Args...>, U>
            {
                using type = Template<U, Args...>;
            };


            template <class T>
            using _element_type     =   typename T::element_type;
            template <class T>
            using _diff_type        =   typename T::difference_type;
            template <class T, class U>
            using _rebind           =   typename replace_first_arg_<T, U>::type;

            template <class T>
            using get_first_arg_t   =   typename get_first_arg_<T>::type;
            template <class T, class U>
            using replace_first_arg_t = typename replace_first_arg_<T, U>::type;

            
        public:
            using pointer           =   Ptr;
            using element_type      =   detector_t<get_first_arg_t<Ptr>, _element_type, Ptr>;
            using difference_type   =   detector_t<long long, _diff_type, Ptr>;

            template <class U>
            using rebind            =   detector_t<replace_first_arg_t<Ptr, U>, _rebind, Ptr, U>;

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
            typedef long long       difference_type;

            template <class U>
            using rebind =          U*;

            /**
             * Constructs a dereferenceable pointer to its argument.
             * @param arg The argument from which a pointer is constructed.
            */
            static pointer pointer_to(element_type& arg)
            {
                return std_copy::addressof(arg);
            }
    };
}

#endif