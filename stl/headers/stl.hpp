#include <algorithm>
#include <string>

namespace std_copy {
    template <class T>
    class iterator {
        private:
            //typedefs
            typedef typename T::value_type                  value_type;
            typedef typename T::pointer                     pointer;
            typedef typename T::reference                   reference;
            typedef typename T::const_reference             const_reference;

            pointer internalPtr_;

        public:
            iterator(reference ptr)
                : internalPtr_(ptr) {}

            iterator(const iterator& it)
                : internalPtr_(it.internalPtr_) {}
            
            /**
             * Overloaded postfix increment operator
            */
            iterator& operator++() {
                internalPtr_++;
                return internalPtr_;
            }
            /**
             * Overloaded prefix increment operator
            */
            iterator operator++(int) {
                pointer ptrBeforeIncrement = internalPtr_;
                ++internalPtr_;
                return ptrBeforeIncrement;
            }
            /**
             * Overloaded postfix decrement operator
            */
            iterator& operator--() {
                internalPtr_--;
                return internalPtr_;
            }
            /**
             * Overloaded prefix decrement operator
            */
            iterator operator--(int) {
                pointer ptrBeforeDecrement = internalPtr_;
                --internalPtr_;
                return ptrBeforeDecrement;
            }
            /**
             * Overloaded equality operator
            */
            bool operator==(const iterator& it) {
                return internalPtr_ == it.internalPtr_;
            }
    };
    template <class T>
    class STL_CONTAINER {
        protected:
            typedef T               value_type;
            typedef T*              pointer;
            typedef T&              reference;
            typedef const T&        const_reference;
            typedef std::size_t     size_type;

            pointer internalBuffer_;
            size_type numberOfElements_; 
        
        public:
            /**
             * This function returns a reference to 
             * the element at a specified index in 
             * the vector.
             * @param index The index of the element to retrieve.
            */
            reference at(size_type index) {
                if (index >= numberOfElements_) {
                    std::string err = "index (which is " + std::to_string(index) + ") >= this->size() (which is " + 
                                    std::to_string(numberOfElements_) + ")";

                    throw std::out_of_range(err);
                }
                return internalBuffer_[index];
            }
            /**
             * The [] operator is overloaded to provide C-style array
             * indexing.
             * @param index The index of the element to retrieve.
            */
            reference operator[](size_type index) {
                return this->at(index);
            }
    };
}