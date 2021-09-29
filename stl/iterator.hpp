#ifndef _STD_COPY_ITERATOR
#define _STD_COPY_ITERATOR

namespace std_copy {
    template <class T>
    struct iterator_traits {
        //typedefs
        typedef typename T::value_type              value_type;
        typedef typename T::pointer                 pointer;
        typedef typename T::const_pointer           const_pointer;
        typedef typename T::reference               reference;
        typedef typename T::const_reference         const_reference;
        typedef typename T::size_type               size_type;
        typedef typename T::difference_type         difference_type;
    };
    
    template <class T>
    class iterator {
        private:
            typedef typename T::value_type              value_type;
            typedef typename T::pointer                 pointer;
            typedef typename T::const_pointer           const_pointer;
            typedef typename T::reference               reference;
            typedef typename T::const_reference         const_reference;
            typedef typename T::size_type               size_type;
            typedef typename T::difference_type         difference_type;
            typedef iterator<T>                         iterator_t;
            typedef iterator_t&                         iterator_reference;
            typedef const iterator_t&                   const_iterator_reference;

            pointer internalPtr_;

        public:
            iterator(pointer ptr = nullptr)
                : internalPtr_(ptr) {}

            iterator(const_iterator_reference it)
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
             * Overloaded + operator
            */
            iterator_t operator+(difference_type n) {
                return iterator_t(internalPtr_ + n);
            }
            /**
             * Overloaded -= operator
            */
            void operator-=(size_type n) {
                internalPtr_ -= n;
            }
            /**
             * Overloaded - operator; decrements the iterator by a certain amount.
            */
            iterator_t operator-(difference_type n) {
                return iterator_t(internalPtr_ - n);
            }
            /**
             * Overloaded - operator; finds the distance between two iterators.
            */
            difference_type operator-(const_iterator_reference it) {
                return internalPtr_ - it.internalPtr_;
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
     * @param first The first iterator.
     * @param second The second iterator.
    */
    template <class Iterator>
    long long distance(Iterator start, Iterator last) {
        long long n = 0;
        while (start != last) {
            start++;
            n++;
        }
        return n;
    }
    /**
     * This function returns an iterator to the element n positions 
     * after it.
     * @param it The starting iterator position.
     * @param n The amount to add to the iterator.
    */
    template <class Iterator>
    Iterator next(Iterator it, long long n = 1) {
        return it + n;
    }
    /**
     * This function returns an iterator to the element n positions 
     * before it.
     * @param it The starting iterator position.
     * @param n The amount to subtract from the iterator.
    */
    template <class Iterator>
    Iterator prev(Iterator it, long long n = 1) {
        return it - n;
    }
}

#endif /* _STD_COPY_ITERATOR */