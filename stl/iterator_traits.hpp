#ifndef _STD_COPY_ITERATOR_TRAITS
#define _STD_COPY_ITERATOR_TRAITS

namespace _std_copy_hidden
{
    namespace _std_copy_iterator_traits
    {
        namespace _detail
        {
            template <class T, class U>
            concept _is_same = std_copy::same_as<std_copy::remove_reference_t<T>, U>;
            //Checks if Iterator is actually an iterator/pointer
            template <class Iterator>
            concept _is_iterator =
            requires(Iterator it)
            {
                {*it} -> _is_same<typename std_copy::iterator_traits<Iterator>::value_type>;
                {it++};
                {++it};
            };
        }
        
        //Checks if InputIterator is an input iterator
        template <class InputIterator>
        concept _is_input_iterator = _detail::_is_iterator<InputIterator> &&
        requires(InputIterator it, InputIterator it2)
        {
            {it == it2};
            {it != it2};
        };
        //Checks if OutputIterator is an output iterator
        template <class OutputIterator>
        concept _is_output_iterator = _detail::_is_iterator<OutputIterator> &&
        requires(OutputIterator it, typename std_copy::iterator_traits<OutputIterator>::value_type val)
        {
            {*it = val};
        };
        //Checks if BidirectionalIterator it a bidirectional iterator
        template <class BidirectionalIterator>
        concept _is_bidirectional_iterator = _is_input_iterator<BidirectionalIterator> && _is_output_iterator<BidirectionalIterator> &&
        requires(BidirectionalIterator it)
        {
            {--it};
            {it--};
        };
    }
}

namespace std_copy
{
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};

    template <class Iterator>
    struct iterator_traits
    {
        private:
            template <class T>
            using _pointer = typename T::pointer;

        public:
            typedef typename Iterator::value_type              value_type;
            using pointer       =       _std_copy_hidden::_detector_t<void, _pointer, Iterator>;
            typedef typename Iterator::reference               reference;
            typedef typename Iterator::difference_type         difference_type;
            typedef typename Iterator::iterator_category       iterator_category;
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

    template <class Category, class T, class Distance = long long, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef Category            iterator_category;
        typedef T                   value_type;
        typedef Distance            difference_type;
        typedef Pointer             pointer;
        typedef Reference           reference;
    };
}

#endif