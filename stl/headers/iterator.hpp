#include <iterator>

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
            iterator_type() {}

            iterator_type(pointer ptr)
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
            pointer& operator->() {
                return internalPtr_;
            }
    };
    /**
     * This function advances the iterator by a 
     * specified number.
     * @param it The iterator to advance.
     * @param n The number to advance the iterator by.
    */
    template <class T>
    void advance(iterator_type<T>& it, long long s) {
        it.operator->() += s;
    }
}