#ifndef _STD_COPY_ITERATOR_FUNCS
#define _STD_COPY_ITERATOR_FUNCS

#include "iterator_traits.hpp"
#include <cstdint>
#include <stdexcept>
#include <cmath>

namespace _std_copy_hidden
{
    namespace _std_copy_stl_containers
    {
        template <class T>
        class _iterator
        {
            public:
                typedef typename T::value_type                  value_type;
                typedef typename T::pointer                     pointer;
                typedef typename T::reference                   reference;
                typedef typename T::difference_type             difference_type;
                typedef std_copy::random_access_iterator_tag    iterator_category;

            protected:
                typedef _iterator<T>                            _iterator_type;

                pointer _internalPtr;

            public:
                _iterator() {}
                _iterator(pointer ptr)
                    : _internalPtr(ptr) {}
                
                /**
                 * Overloaded postfix increment operator
                */
                _iterator_type operator++()
                {
                    _internalPtr++;
                    return *this;
                }
                /**
                 * Overloaded prefix increment operator
                */
                _iterator_type operator++(int)
                {
                    _iterator_type ptrBeforeIncrement = *this;
                    _internalPtr++;
                    return ptrBeforeIncrement;
                }
                /**
                 * Overloaded postfix decrement operator
                */
                _iterator_type operator--()
                {
                    _internalPtr--;
                    return *this;
                }
                /**
                 * Overloaded prefix decrement operator
                */
                _iterator_type operator--(int)
                {
                    _iterator_type ptrBeforeDecrement = _internalPtr;
                    _internalPtr--;
                    return ptrBeforeDecrement;
                }
                /**
                 * Overloaded equality operator. Compares against 
                 * another iterator.
                 * @param it The iterator to compare against.
                */
                bool operator==(_iterator_type it)
                {
                    return _internalPtr == it._internalPtr;
                }
                /**
                 * Overloaded inequality operator.
                 * @param it The iterator to compare against.
                */
                bool operator!=(_iterator_type it)
                {
                    return !(*this == it);
                }
                /**
                 * Overloaded dereference operator
                */
                reference operator*()
                {
                    return *_internalPtr;
                }
                /**
                 * Overloaded arrow operator
                */
                pointer operator->()
                {
                    return _internalPtr;
                }
                /**
                 * Returns the iterator's internal pointer
                */
                pointer base()
                {
                    return _internalPtr;
                }
                /**
                 * Overloaded assignment operator -> assigns 
                 * the current iterator to a provided iterator.
                */
                void operator=(_iterator_type it)
                {
                    _internalPtr = it._internalPtr;
                }
                /**
                 * Overloaded += operator
                */
                void operator+=(difference_type n)
                {
                    _internalPtr += n;
                }
                /**
                 * Overloaded + operator
                */
                _iterator_type operator+(difference_type n)
                {
                    return _iterator_type(_internalPtr + n);
                }
                /**
                 * Overloaded -= operator
                */
                void operator-=(difference_type n)
                {
                    _internalPtr -= n;
                }
                /**
                 * Overloaded - operator; decrements the iterator by a certain amount.
                */
                _iterator_type operator-(difference_type n)
                {
                    return _iterator_type(_internalPtr - n);
                }
                /**
                 * Overloaded - operator; finds the std_copy::distance between two iterators.
                */
                difference_type operator-(_iterator_type it)
                {
                    return _internalPtr - it._internalPtr;
                }
                /**
                 * Overloaded < operator
                */
                bool operator<(_iterator_type i)
                {
                    return _internalPtr < i._internalPtr;
                }
                /**
                 * Overloaded > operator
                */
                bool operator>(_iterator_type i)
                {
                    return _internalPtr > i._internalPtr;
                }
                /**
                 * Overloaded >= operator
                */
                bool operator>=(_iterator_type i)
                {
                    return _internalPtr >= i._internalPtr;
                }
                /**
                 * Overloaded <= operator
                */
                bool operator<=(_iterator_type i)
                {
                    return _internalPtr <= i._internalPtr;
                }
                /**
                 * Overloaded ! operator
                */
                bool operator!()
                {
                    return !_internalPtr;
                }
        };
    }
}

namespace std_copy
{
    /**
     * This function advances the iterator by a 
     * specified number.
     * @param it The iterator to advance.
     * @param n The number to advance the iterator by.
    */
    template <class InputIterator>
    constexpr void advance(InputIterator& it, std::ptrdiff_t n = 1)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        using _iter_category = typename std_copy::iterator_traits<InputIterator>::iterator_category;
        using _random_access_tag = std_copy::random_access_iterator_tag;
        
        if constexpr(std_copy::is_same<_iter_category, _random_access_tag>::value)
            it += n;
        else
        {
            if (n == 1)
                it++;
            else
            {
                for (std::size_t i = 0; i < std::abs(n); i++)
                {
                    if (n < 0)
                        it--;
                    else if (n > 0)
                        it++;
                }
            }
        }
    }
    /**
     * This function returns the std_copy::distance between 
     * two iterators.
     * @param first The first iterator.
     * @param second The second iterator.
    */
    template <class InputIterator>
    constexpr std::size_t distance(InputIterator start, InputIterator last)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        using _iter_category = std_copy::iterator_traits<InputIterator>::iterator_category;
        using _random_access_tag = std_copy::random_access_iterator_tag;

        if constexpr(std_copy::is_same<_iter_category, _random_access_tag>::value)
            return last - start;
        
        std::size_t n = 0;
        while (start != last)
        {
            if (n == std::size_t(-1))
                throw std::length_error("Range is too long");
            n++;
            start++;
        }
        return n;
        
    }
    /**
     * This function returns an iterator to the element n positions 
     * after it.
     * @param it The starting iterator position.
     * @param n The amount to add to the iterator.
    */
    template <class InputIterator>
    constexpr InputIterator next(InputIterator it, std::ptrdiff_t n)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        using _iter_category = std_copy::iterator_traits<InputIterator>::iterator_category;
        using _random_access_tag = std_copy::random_access_iterator_tag;

        if constexpr(std_copy::is_same<_iter_category, _random_access_tag>::value)
            return it + n;
        
        for (std::size_t i = 0; i < std::abs(n); i++)
        {
            if (n < 0)
                it--;
            else if (n > 0)
                it++;
        }
        return it;
    }
    /**
     * This function returns an iterator to the element n positions 
     * before it.
     * @param it The starting iterator position.
     * @param n The amount to subtract from the iterator.
    */
    template <class InputIterator>
    constexpr InputIterator prev(InputIterator it, std::ptrdiff_t n = 1)
#if __cplusplus > 201703L
    requires bidirectional_iterator<InputIterator>
#endif
    {
        using _iter_category = std_copy::iterator_traits<InputIterator>::iterator_category;
        using _random_access_tag = std_copy::random_access_iterator_tag;

        if constexpr(std_copy::is_same<_iter_category, _random_access_tag>::value)
            return it - n;
        for (std::size_t i = 0; i < std::abs(n); i++)
        {
            if (n < 0)
                it--;
            else if (n > 0)
                it++;
        }
        return it;
    }
    /**
     * Returns a pointer to the beginning of a C-style array.
     * @param arr The array.
    */
    template <class T, std::size_t N>
    T* begin(T (&arr)[N])
    {
        return arr;
    }
    /**
     * Returns a pointer to the end of a C-style array.
     * @param arr The array.
    */
    template <class T, std::size_t N>
    T* end(T (&arr)[N])
    {
        return arr + N;
    }
}

#endif /* _STD_COPY_ITERATOR_FUNCS */