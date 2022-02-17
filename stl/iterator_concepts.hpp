#ifndef _STD_COPY_ITERATOR_CONCEPTS
#define _STD_COPY_ITERATOR_CONCEPTS

#if __cplusplus > 201703L

#include "concepts.hpp"
#include "type_traits.hpp"
#include "iterator_traits.hpp"

namespace std_copy
{
    //incrementable_traits
    template <class T>
    struct incrementable_traits {};
    template <class T>
    struct incrementable_traits<T*>
    {
        using difference_type = long long;  
    };
    template <class T>
    requires requires { typename T::difference_type; }
    struct incrementable_traits<T>
    {
        using difference_type = typename T::difference_type;
    };
    template <class T>
    struct incrementable_traits<const T> : incrementable_traits<T> {};


    //indirectly_readable_traits
    template <class T>
    struct indirectly_readable_traits {};
    template <class T>
    struct indirectly_readable_traits<T*>
    {
        using value_type = remove_cv_t<T>;
    };
    template <class T>
    requires is_array_v<T>
    struct indirectly_readable_traits<T>
    {
        using value_type = remove_cv_t<remove_extent_t<T>>;
    };
    template <class T>
    struct indirectly_readable_traits<const T> : indirectly_readable_traits<T> {};
    template <class T>
    requires requires { typename T::value_type; }
    struct indirectly_readable_traits<T>
    {
        using value_type = remove_cv_t<typename T::value_type>;
    };
    template <class T>
    requires requires { typename T::element_type; }
    struct indirectly_readable_traits<T>
    {
        using value_type = remove_cv_t<typename T::element_type>;
    };
    template <class T>
    requires requires { typename T::element_type; typename T::value_type; } 
             && same_as<remove_cv_t<typename T::value_type>, 
                        remove_cv_t<typename T::element_type>>
    struct indirectly_readable_traits<T>
    {
        using value_type = remove_cv_t<typename T::value_type>;
    };

    //weakly_incrementable
    template <class Iterator>
    concept weakly_incrementable =
    requires(Iterator i)
    {
        typename Iterator::difference_type;
        {++i} -> std_copy::same_as<Iterator&>;
        i++;
    };
}
#endif

#endif /* _STD_COPY_ITERATOR_CONCEPTS */