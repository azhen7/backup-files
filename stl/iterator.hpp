#ifndef _STD_COPY_ITERATOR
#define _STD_COPY_ITERATOR

#include "iterator_traits.hpp"
#include "type_traits.hpp"

namespace std_copy
{
    template <class T>
    class iterator
    {
        public:
            typedef typename T::value_type                  value_type;
            typedef typename T::pointer                     pointer;
            typedef typename T::reference                   reference;
            typedef typename T::difference_type             difference_type;
            typedef std_copy::random_access_iterator_tag    iterator_category;

        private:
            typedef iterator<T>                             iterator_type;

            pointer internalPtr_;

        public:
            iterator(pointer ptr = nullptr)
                : internalPtr_(ptr) {}
            
            /**
             * Overloaded postfix increment operator
            */
            iterator_type operator++()
            {
                internalPtr_++;
                return *this;
            }
            /**
             * Overloaded prefix increment operator
            */
            iterator_type operator++(int)
            {
                iterator_type ptrBeforeIncrement = *this;
                internalPtr_++;
                return ptrBeforeIncrement;
            }
            /**
             * Overloaded postfix decrement operator
            */
            iterator_type operator--()
            {
                internalPtr_--;
                return *this;
            }
            /**
             * Overloaded prefix decrement operator
            */
            iterator_type operator--(int)
            {
                iterator_type ptrBeforeDecrement = internalPtr_;
                internalPtr_--;
                return ptrBeforeDecrement;
            }
            /**
             * Overloaded equality operator. Compares against 
             * another iterator.
             * @param it The iterator to compare against.
            */
            bool operator==(iterator_type it)
            {
                return internalPtr_ == it.internalPtr_;
            }
            /**
             * Overloaded inequality operator.
             * @param it The iterator to compare against.
            */
            bool operator!=(iterator_type it)
            {
                return !(*this == it);
            }
            /**
             * Overloaded dereference operator
            */
            reference operator*()
            {
                return *internalPtr_;
            }
            /**
             * Overloaded arrow operator
            */
            pointer operator->()
            {
                return internalPtr_;
            }
            /**
             * Returns the iterator's internal pointer
            */
            pointer base()
            {
                return internalPtr_;
            }
            /**
             * Overloaded assignment operator -> assigns 
             * the current iterator to a provided iterator.
            */
            void operator=(iterator_type it)
            {
                internalPtr_ = it.internalPtr_;
            }
            /**
             * Overloaded += operator
            */
            void operator+=(difference_type n)
            {
                internalPtr_ += n;
            }
            /**
             * Overloaded + operator
            */
            iterator_type operator+(difference_type n)
            {
                return iterator_type(internalPtr_ + n);
            }
            /**
             * Overloaded -= operator
            */
            void operator-=(difference_type n)
            {
                internalPtr_ -= n;
            }
            /**
             * Overloaded - operator; decrements the iterator by a certain amount.
            */
            iterator_type operator-(difference_type n)
            {
                return iterator_type(internalPtr_ - n);
            }
            /**
             * Overloaded - operator; finds the distance between two iterators.
            */
            difference_type operator-(iterator_type it)
            {
                return internalPtr_ - it.internalPtr_;
            }
            /**
             * Overloaded < operator
            */
            bool operator<(iterator_type i)
            {
                return internalPtr_ < i.internalPtr_;
            }
            /**
             * Overloaded > operator
            */
            bool operator>(iterator_type i)
            {
                return internalPtr_> i.internalPtr_;
            }
            /**
             * Overloaded >= operator
            */
            bool operator>=(iterator_type i)
            {
                return internalPtr_ >= i.internalPtr_;
            }
            /**
             * Overloaded <= operator
            */
            bool operator<=(iterator_type i)
            {
                return internalPtr_ <= i.internalPtr_;
            }
            /**
             * Overloaded ! operator
            */
            bool operator!()
            {
                return !internalPtr_;
            }
    };
    /**
     * This function advances the iterator by a 
     * specified number.
     * @param it The iterator to advance.
     * @param n The number to advance the iterator by.
    */
    template <class InputIt>
    void advance(InputIt& it, unsigned long long n = 1)
    {
        using _iter_category = std_copy::iterator_traits<InputIt>::iterator_category;
        using _random_access_tag = std_copy::random_access_iterator_tag;
        
        if constexpr(std_copy::is_same<_iter_category, _random_access_tag>::value)
            it += n;
        else
        {
            for (unsigned long long i = 0; i < n; i++)
                it++;
        }
    }
    /**
     * This function returns the distance between 
     * two iterators.
     * @param first The first iterator.
     * @param second The second iterator.
    */
    template <class InputIt>
    long long distance(InputIt start, InputIt last)
    {
        using _iter_category = std_copy::iterator_traits<InputIt>::iterator_category;
        using _random_access_tag = std_copy::random_access_iterator_tag;

        if constexpr(std_copy::is_same<_iter_category, _random_access_tag>::value)
            return last - start;
        long long n = 0;
        while (start++ != last)
            n++;
        return n;
        
    }
    /**
     * This function returns an iterator to the element n positions 
     * after it.
     * @param it The starting iterator position.
     * @param n The amount to add to the iterator.
    */
    template <class InputIt>
    InputIt next(InputIt it, unsigned long long n)
    {
        using _iter_category = std_copy::iterator_traits<InputIt>::iterator_category;
        using _random_access_tag = std_copy::random_access_iterator_tag;

        if constexpr(std_copy::is_same<_iter_category, _random_access_tag>::value)
            return it + n;
        
        for (unsigned int i = 0; i < n; i++)
            it++;
        return it;
    }
    /**
     * This function returns an iterator to the element n positions 
     * before it.
     * @param it The starting iterator position.
     * @param n The amount to subtract from the iterator.
    */
    template <class InputIt>
    InputIt prev(InputIt it, unsigned long long n)
    {
        using _iter_category = std_copy::iterator_traits<InputIt>::iterator_category;
        using _random_access_tag = std_copy::random_access_iterator_tag;

        if constexpr(std_copy::is_same<_iter_category, _random_access_tag>::value)
            return it - n;
        
        for (unsigned int i = 0; i < n; i++)
            it--;
        return it;
    }
}

#endif /* _STD_COPY_ITERATOR */