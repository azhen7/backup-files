#ifndef _STD_COPY_POINTER_TRAITS
#define _STD_COPY_POINTER_TRAITS

#include "type_traits.hpp"

namespace std_copy {
    /**
     * General interface for all pointer types.
    */
    template <class Ptr>
    struct pointer_traits {
        private:
            //Checks if Ptr class has member typedef element_type
            template <class T>
            struct _has_element_type {
                private:
                    typedef int     yes;
                    typedef char    no;

                    template <class C>
                    static constexpr yes& test(&C::element_type);

                    template <class C>
                    static constexpr no& test(...);
                
                public:
                    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
            };
            //Checks if Ptr class has member typedef difference_type
            template <class T>
            struct _has_difference_type {
                private:
                    typedef int     yes;
                    typedef char    no;

                    template <class C>
                    static constexpr yes& test(&C::difference_type);

                    template <class C>
                    static constexpr no& test(...);
                
                public:
                    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
            }

        public:
            using pointer = Ptr;
            using element_type = typename conditional<_has_element_type<Ptr>::value, Ptr::element_type, T>;
            using difference_type = typename conditional<_has_difference_type<Ptr>::value, Ptr::difference_type, long long>;
    };
}

#endif