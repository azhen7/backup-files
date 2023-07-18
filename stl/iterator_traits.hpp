#ifndef _STD_COPY_ITERATOR_TRAITS
#define _STD_COPY_ITERATOR_TRAITS

#include "concepts.hpp"
#include "iterator_concepts.hpp"
#include "type_traits.hpp"

#include <cstdint>

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
        protected:
            template <class T>
            using _pointer = typename T::pointer;

        public:
            typedef typename Iterator::value_type                               value_type;
            typedef _std_copy_hidden::_detector_t<void, _pointer, Iterator>     pointer;
            typedef typename Iterator::reference                                reference;
            typedef typename Iterator::difference_type                          difference_type;
            typedef typename Iterator::iterator_category                        iterator_category;
    };
    /**
     * Partial specialization for pointer types
    */
    template <class T>
    struct iterator_traits<T*>
    {
        typedef remove_cv_t<T>                          value_type;
        typedef T*                                      pointer;
        typedef T&                                      reference;
        typedef std::ptrdiff_t                          difference_type;
        typedef std_copy::random_access_iterator_tag    iterator_category;
    };
    template <class T>
    struct iterator_traits<T* const> : iterator_traits<T*> {};
    template <class T>
    struct iterator_traits<T* volatile> : iterator_traits<T*> {};
    template <class T>
    struct iterator_traits<T* const volatile> : iterator_traits<T*> {};

    template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef Category            iterator_category;
        typedef T                   value_type;
        typedef Distance            difference_type;
        typedef Pointer             pointer;
        typedef Reference           reference;
    };
}

#if __cplusplus > 201703L
namespace _std_copy_hidden
{
    namespace _std_copy_iterator_traits
    {
        namespace _detail
        {
            template <class T>
            using _value_type = typename std_copy::iterator_traits<T>::value_type;

            template <class T, class U>
            concept _is_same = std_copy::same_as<std_copy::remove_reference_t<T>, std_copy::remove_reference_t<U>>;
            //Checks if Iterator is actually an iterator/pointer
            template <class Iterator>
            concept _is_iterator =
            requires(Iterator it)
            {
                {*it} -> _is_same<_value_type<Iterator>>;
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
        requires(OutputIterator it, _detail::_value_type<OutputIterator> val)
        {
            {*it = val};
        };
        //Checks if BidirectionalIterator it a bidirectional iterator
        template <class BidirectionalIterator>
        concept _is_bidirectional_iterator = _is_input_iterator<BidirectionalIterator> &&
        requires(BidirectionalIterator it)
        {
            {--it};
            {it--};
        };
    }
}

namespace std_copy
{
    template <class InputOrOutpuIterator>
    concept input_or_output_iterator = std_copy::weakly_incrementable<InputOrOutpuIterator> &&
    requires(InputOrOutpuIterator i)
    {
        {*i};
    };

    template <class InputIterator>
    concept input_iterator = _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>;

    template <class OutputIterator>
    concept output_iterator = _std_copy_hidden::_std_copy_iterator_traits::_is_output_iterator<OutputIterator>;

    template <class BidirectionalIterator>
    concept bidirectional_iterator = _std_copy_hidden::_std_copy_iterator_traits::_is_bidirectional_iterator<BidirectionalIterator>;

    template <class RandomAccessIterator>
    concept random_access_iterator = bidirectional_iterator<RandomAccessIterator> &&
    requires(RandomAccessIterator it, const RandomAccessIterator constIt, typename iterator_traits<RandomAccessIterator>::difference_type n)
    {
        {it += n} -> std_copy::same_as<RandomAccessIterator&>;
        {constIt + n} -> std_copy::same_as<RandomAccessIterator>;
        {n + constIt} -> std_copy::same_as<RandomAccessIterator>;
        {it -= n} -> std_copy::same_as<RandomAccessIterator&>;
        {constIt - n} -> std_copy::same_as<RandomAccessIterator>;
        {constIt[n]} -> std_copy::same_as<typename iterator_traits<RandomAccessIterator>::reference>;
    };
}
#endif

#endif