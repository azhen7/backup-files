#include <memory>
#include <stdexcept>

#include "stl.hpp"

namespace std_copy {
    template <class T1, class T2>
    struct pair {
        T1  first;
        T2  second;

        pair(T1 f = T1(), T2 s = T2())
            : first(f), 
            second(s) 
        {}

        pair (const pair& p)
            : first(p.first),
            second(p.second)
        {}
    };
    template <class T1, class T2, class Alloc = std::allocator<pair<T1, T2>>>
    class map : public STL_CONTAINER<pair<T1, T2>> {
        public:
            typedef T1                                      key_type;
            typedef T2                                      mapped_type;
            typedef pair<T1, T2>                            value_type;
            typedef value_type*                             pointer;
            typedef value_type&                             reference;
            typedef const value_type&                       const_reference;
            typedef Alloc                                   allocator_type;
            typedef std::size_t                             size_type;

            class iterator {
                
            };
        
        private:
            using STL_CONTAINER<value_type>::internalBuffer_;
            using STL_CONTAINER<value_type>::numberOfElements_;

            size_type capacity_;
            allocator_type allocator;

        public:
            map() : capacity_(0) {
                numberOfElements_ = 0;
            }

            ~map() = default;

            /**
             * This function returns the number of elements 
             * in the map.
            */
            size_type size() const {
                return numberOfElements_;
            }
            /**
             * This function checks whether the map is empty (i.e. has no elements).
            */
            bool empy() const {
                return numberOfElements_ == 0;
            }
            /**
             * This function clears the map.
            */
            void clear() {
                allocator.deallocate(internalBuffer_, capacity_);
                numberOfElements_ = 0;
            }
            /**
             * This function returns an iterator to the first element in the container
            */
            iterator begin() {
                return iterator(internalBuffer_);
            }
            /**
             * This function returns an iterator to the theoretical element after the last 
             * element in the container;
            */
            iterator end() {
                return iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * This function returns a const iterator to the first element in the container
            */
            iterator begin() {
                return (const_iterator) iterator(internalBuffer_);
            }
            /**
             * This function returns a const iterator to the theoretical element after the last 
             * element in the container;
            */
            iterator end() {
                return (const_iterator) iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * Operator overload of operator[]. If the provided argument exists in the 
             * map, a reference to its mapped value is returned. Otherwise, the function
             * adds an element to the map with the key having the value of the argument.
            */
            mapped_type& operator[](const key_type& elem) {
                for (int i = 0; i < numberOfElements_; i++) {
                    if (internalBuffer_[i].first == elem) {
                        return internalBuffer_[i].second;
                    }
                }
                if (capacity_ == 0) {
                    capacity_ = 1;
                    internalBuffer_ = allocator.allocate(1);
                }
                else if (numberOfElements_ + 1 > capacity_) {
                    capacity_ *= 2;

                    pointer temp = new value_type[numberOfElements_];
                    std::copy(internalBuffer_, internalBuffer_ + numberOfElements_, temp);
                    allocator.deallocate(internalBuffer_, capacity_ / 2);
                    internalBuffer_ = allocator.allocate(capacity_);
                    std::copy(temp, temp + numberOfElements_, internalBuffer_);
                    delete temp;
                }
                internalBuffer_[numberOfElements_].first = elem;
                numberOfElements_++;
                return internalBuffer_[numberOfElements_ - 1].second;
            }
            /**
             * This function has the same functionality as operator[], except 
             * instead of creating a new element if the provided key doesn't 
             * exist, an out_of_range exception is thrown.
            */
            mapped_type& at(const key_type& key) {
                for (int i = 0; i < numberOfElements_; i++) {
                    if (internalBuffer_[i].first == key) {
                        return internalBuffer_[i].second;
                    }
                }
                throw std::out_of_range("map::at");
            }
    };
}