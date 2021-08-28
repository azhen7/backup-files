//#include <iterator>
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
            pointer internalPtr_;

        public:
            iterator_type(pointer ptr = nullptr)
                : internalPtr_(ptr) {}

            iterator_type(const iterator_type& it)
                : internalPtr_(it.internalPtr_) {}
            
            /**
             * Overloaded postfix increment operator
            */
            iterator_type& operator++() {
                internalPtr_++;
                return *this;
            }
            /**
             * Overloaded prefix increment operator
            */
            iterator_type operator++(int) {
                iterator_type ptrBeforeIncrement = *this;
                ++(*this);
                return *this;
            }
            /**
             * Overloaded postfix decrement operator
            */
            iterator_type& operator--() {
                internalPtr_--;
                return *this;
            }
            /**
             * Overloaded prefix decrement operator
            */
            iterator_type operator--(int) {
                iterator_type ptrBeforeDecrement = internalPtr_;
                --(*this);
                return ptrBeforeDecrement;
            }
            /**
             * Overloaded equality operator
             * @param it The iterator to compare against.
            */
            bool operator==(const iterator_type& it) {
                return internalPtr_ == it.internalPtr_;
            }
            /**
             * Overloaded inequality operator
             * @param it The iterator to compare against.
            */
            bool operator!=(const iterator_type& it) {
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
             * Overloaded assignment operator
            */
            void operator=(const iterator_type<T>& it) {
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
    };
    /**
     * This function advances the iterator by a 
     * specified number.
     * @param it The iterator to advance.
     * @param n The number to advance the iterator by.
    */
    template <class InputIterator>
    void advance(InputIterator& it, long long n = 1) {
        it += n;
    }
    /**
     * This function returns the distance between
     * two iterators.
    */
    template <class InputIterator>
    std::ptrdiff_t distance(InputIterator& it1, InputIterator& it2) {
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
    template <class InputIterator>
    InputIterator next(InputIterator& it, long long n = 1) {
        InputIterator newIterator = it;
        newIterator += n;
        return newIterator;
    }
    /**
     * This function returns an iterator to the element n positions 
     * before it.
     * @param it The starting iterator position.
     * @param n The amount to subtract from the iterator.
    */
    template <class InputIterator>
    InputIterator prev(InputIterator& it, long long n = 1) {
        InputIterator newIterator = it;
        newIterator -= n;
        return newIterator;
    }
}