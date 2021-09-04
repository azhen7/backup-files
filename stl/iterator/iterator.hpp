#ifndef _STD_COPY_ITERATOR
#define _STD_COPY_ITERATOR

#include <cstddef>

namespace std_copy {
    template <class T>
    class iterator_type {
        public:
            //typedefs
            typedef typename T::value_type              value_type;
            typedef typename T::pointer                 pointer;
            typedef typename T::reference               reference;
            typedef typename T::const_reference         const_reference;

        private:
            typedef iterator_type<T>                    iterator_t;
            typedef iterator_t&                         iterator_reference;
            typedef const iterator_t&                   const_iterator_reference;

            pointer internalPtr_;

        public:
            iterator_type(pointer ptr = nullptr)
                : internalPtr_(ptr) {}

            iterator_type(const_iterator_reference it)
                : internalPtr_(it.internalPtr_) {}
            
            /**
             * Overloaded postfix increment operator
            */
            iterator_reference operator++() {
                internalPtr_++;
                return *this;
            }
            /**
             * Overloaded prefix increment operator
            */
            iterator_t operator++(int) {
                iterator_t ptrBeforeIncrement = *this;
                ++(*this);
                return *this;
            }
            /**
             * Overloaded postfix decrement operator
            */
            iterator_reference operator--() {
                internalPtr_--;
                return *this;
            }
            /**
             * Overloaded prefix decrement operator
            */
            iterator_t operator--(int) {
                iterator_t ptrBeforeDecrement = internalPtr_;
                --(*this);
                return ptrBeforeDecrement;
            }
            /**
             * Overloaded equality operator
             * @param it The iterator to compare against.
            */
            bool operator==(const_iterator_reference it) {
                return internalPtr_ == it.internalPtr_;
            }
            /**
             * Overloaded inequality operator
             * @param it The iterator to compare against.
            */
            bool operator!=(const_iterator_reference it) {
                return !(*this == it);
            }
            /**
             * Overloaded dereference operator
            */
            reference operator*() {
                return *internalPtr_;
            }
            /**
             * Overloaded arrow operator
            */
            pointer operator->() {
                return internalPtr_;
            }
            /**
             * Overloaded assignment operator -> assigns 
             * the current iterator to a provided iterator.
            */
            void operator=(const_iterator_reference it) {
                internalPtr_ = it.internalPtr_;
            }
            /**
             * Overloaded += operator
            */
            void operator+=(std::size_t n) {
                internalPtr_ += n;
            }
            /**
             * Overloaded -= operator
            */
            void operator-=(std::size_t n) {
                internalPtr_ -= n;
            }
            /**
             * Overloaded < operator
            */
            bool operator<(const_iterator_reference i) {
                return internalPtr_ < i.internalPtr_;
            }
            /**
             * Overloaded > operator
            */
            bool operator>(const_iterator_reference i) {
                return internalPtr_> i.internalPtr_;
            }
            /**
             * Overloaded >= operator
            */
            bool operator>=(const_iterator_reference i) {
                return internalPtr_ >= i.internalPtr_;
            }
            /**
             * Overloaded <= operator
            */
            bool operator<=(const_iterator_reference i) {
                return internalPtr_ <= i.internalPtr_;
            }
    };
    /**
     * This function advances the iterator by a 
     * specified number.
     * @param it The iterator to advance.
     * @param n The number to advance the iterator by.
    */
    template <class Iterator>
    void advance(Iterator& it, long long n = 1) {
        it += n;
    }
    /**
     * This function returns the distance between
     * two iterators.
    */
    template <class Iterator>
    std::ptrdiff_t distance(Iterator& it1, Iterator& it2) {
        std::ptrdiff_t diff = (std::ptrdiff_t) (it1.operator->() - it2.operator->());
        diff += (diff < 0) ? -1 : 1;
        return diff;
    }
    /**
     * This function returns an iterator to the element n positions 
     * after it.
     * @param it The starting iterator position.
     * @param n The amount to add to the iterator.
    */
    template <class Iterator>
    Iterator next(Iterator& it, long long n = 1) {
        Iterator newIterator = it;
        newIterator += n;
        return newIterator;
    }
    /**
     * This function returns an iterator to the element n positions 
     * before it.
     * @param it The starting iterator position.
     * @param n The amount to subtract from the iterator.
    */
    template <class Iterator>
    Iterator prev(Iterator& it, long long n = 1) {
        Iterator newIterator = it;
        newIterator -= n;
        return newIterator;
    }
}

#endif /* _STD_COPY_ITERATOR */