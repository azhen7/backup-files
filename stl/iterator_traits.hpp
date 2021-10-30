#ifndef _STD_COPY_ITERATOR_TRAITS
#define _STD_COPY_ITERATOR_TRAITS

namespace std_copy
{
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};

    template <class T>
    struct iterator_traits
    {
        typedef typename T::value_type              value_type;
        typedef typename T::pointer                 pointer;
        typedef typename T::reference               reference;
        typedef typename T::difference_type         difference_type;
        typedef typename T::iterator_category       iterator_category;
    };

    /**
     * Partial specialization for pointer types
    */
    template <class T>
    struct iterator_traits<T*>
    {
        typedef T                                       value_type;
        typedef T*                                      pointer;
        typedef T&                                      reference;
        typedef long long                               difference_type;
        typedef std_copy::random_access_iterator_tag    iterator_category;
    };
}

#endif