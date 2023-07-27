#ifndef _STD_COPY_ITERATOR_FUNCS
#define _STD_COPY_ITERATOR_FUNCS

#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include <cstdint>
#include <stdexcept>
#include <cmath>

namespace _std_copy_hidden
{
    namespace _std_copy_stl_containers
    {
        template <class P, class T>
        class _iterator
        {
            private:
                typedef std_copy::iterator_traits<P>                _iterator_traits;
            public:
                typedef typename _iterator_traits::value_type       value_type;
                typedef typename _iterator_traits::pointer          pointer;
                typedef typename _iterator_traits::reference        reference;
                typedef typename _iterator_traits::difference_type  difference_type;
                typedef std_copy::random_access_iterator_tag        iterator_category;

            protected:
                //typedef _iterator<P, T>                            _iterator;

                P _internalPtr;

            public:
                _iterator() {}
                _iterator(const P& ptr)
                    : _internalPtr(ptr) {}

                template <class _Ptr>
                _iterator(const _iterator<_Ptr, T>& p)
                    : _internalPtr(p.base()) {}
                
                /**
                 * Overloaded postfix increment operator
                */
                _iterator& operator++() noexcept
                {
                    _internalPtr++;
                    return *this;
                }
                /**
                 * Overloaded prefix increment operator
                */
                _iterator operator++(int) noexcept
                {
                    return _iterator(_internalPtr++);
                }
                /**
                 * Overloaded postfix decrement operator
                */
                _iterator& operator--() noexcept
                {
                    _internalPtr--;
                    return *this;
                }
                /**
                 * Overloaded prefix decrement operator
                */
                _iterator operator--(int) noexcept
                {
                    return _iterator(_internalPtr--);
                }
                /**
                 * Overloaded equality operator. Compares against 
                 * another iterator.
                 * @param it The iterator to compare against.
                */
                bool operator==(_iterator it) const noexcept
                {
                    return _internalPtr == it._internalPtr;
                }
                /**
                 * Overloaded inequality operator.
                 * @param it The iterator to compare against.
                */
                bool operator!=(_iterator it) const noexcept
                {
                    return !(*this == it);
                }
                /**
                 * Overloaded dereference operator
                */
                reference operator*() const noexcept
                {
                    return *_internalPtr;
                }
                /**
                 * Overloaded arrow operator
                */
                P operator->() const noexcept
                {
                    return _internalPtr;
                }
                /**
                 * Returns the iterator's internal pointer
                */
                const P& base() const noexcept
                {
                    return _internalPtr;
                }
                /**
                 * Overloaded assignment operator -> assigns 
                 * the current iterator to a provided iterator.
                */
                void operator=(_iterator it) noexcept
                {
                    _internalPtr = it._internalPtr;
                }
                /**
                 * Overloaded += operator
                */
                _iterator& operator+=(difference_type n) noexcept
                {
                    _internalPtr += n;
                    return *this;
                }
                /**
                 * Overloaded + operator
                */
                _iterator operator+(difference_type n) noexcept
                {
                    return _iterator(_internalPtr + n);
                }
                /**
                 * Overloaded -= operator
                */
                _iterator& operator-=(difference_type n) noexcept
                {
                    _internalPtr -= n;
                    return *this;
                }
                /**
                 * Overloaded - operator; decrements the iterator by a certain amount.
                */
                _iterator operator-(difference_type n) noexcept
                {
                    return _iterator(_internalPtr - n);
                }
                /**
                 * Overloaded - operator; finds the std_copy::distance between two iterators.
                */
                difference_type operator-(_iterator it) noexcept
                {
                    return _internalPtr - it._internalPtr;
                }
                /**
                 * Overloaded < operator
                */
                bool operator<(_iterator i) const noexcept
                {
                    return _internalPtr < i._internalPtr;
                }
                /**
                 * Overloaded > operator
                */
                bool operator>(_iterator i) const noexcept
                {
                    return _internalPtr > i._internalPtr;
                }
                /**
                 * Overloaded >= operator
                */
                bool operator>=(_iterator i) const noexcept
                {
                    return _internalPtr >= i._internalPtr;
                }
                /**
                 * Overloaded <= operator
                */
                bool operator<=(_iterator i) const noexcept
                {
                    return _internalPtr <= i._internalPtr;
                }
                /**
                 * Overloaded ! operator
                */
                bool operator!() const noexcept
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
        using _iter_category = typename std_copy::iterator_traits<InputIterator>::iterator_category;
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
        using _iter_category = typename std_copy::iterator_traits<InputIterator>::iterator_category;
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
        using _iter_category = typename std_copy::iterator_traits<InputIterator>::iterator_category;
        using _random_access_tag = std_copy::random_access_iterator_tag;

        if constexpr(std_copy::is_same<_iter_category, _random_access_tag>::value)
            return it - n;
        for (std::size_t i = 0; i < std::abs(n); i++)
        {
            if (n < 0)
                it++;
            else if (n > 0)
                it--;
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