#include <algorithm>

namespace std_copy {
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
            /**
             * This function returns the underlying
             * internal buffer of the array.
            */
            pointer data() {
                return internalBuffer_;
            }
            /**
             * This function removes the element at the beginning of the vector.
             * If the vector is empty, a call to this function does nothing.
             * This function is new.
            */
            void pop_front() {
                if (numberOfElements_ == 0) return;
                internalBuffer_++;
                numberOfElements_--;
            }
            /**
             * This function returns a reference to the
             * first element in the array. If the vector
             * is empty, this function throws an exception.
            */
            reference front() {
                if (numberOfElements_ == 0) {
                    std::cout << "Cannot access element in empty vector\n";
                    exit(EXIT_FAILURE);
                }
                return internalBuffer_[0];
            }
            /**
             * This function returns a reference to the
             * last element in the array. If the vector 
             * is empty, this function throws an exception.
            */
            reference back() {
                if (numberOfElements_ == 0) {
                    std::cout << "Cannot access element in empty vector\n";
                    exit(EXIT_FAILURE);
                }
                return internalBuffer_[numberOfElements_ - 1];
            }
    };
}