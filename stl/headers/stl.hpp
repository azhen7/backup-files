#include <algorithm>
#include <string>
#include <stdexcept>

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
            reference operator[](long long index) {
                if (index < 0) {
                    index += numberOfElements_;
                    if (index < 0) {
                        std::string err = "absolute value of index (which is " + std::to_string(index * -1)
                                          + ") > this->size() (which is " + std::to_string(numberOfElements_) + ")";
                        throw std::out_of_range(err);
                    }
                }
                return this->at(index);
            }
    };
}
