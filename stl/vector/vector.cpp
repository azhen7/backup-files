//#pragma once

#include <iostream>
#include <vector>

#include <string>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <exception>

#include "stl.hpp"

namespace std_copy {
    /**
     * My own implementation of the STL vector container, defined in
     * the <vector> header. This implementation contains a few new functions, 
     * aside from the ones in the original vector implementation, like pop_front(), 
     * push_front(), and some others.
     * @param T The type of the values the vector will contain.
     * @param Alloc The type of the object used to allocate the underlying buffer
     * used for containing the values.
    */
    template <class T, class Alloc = std::allocator<T>>
    class vector : public STL_CONTAINER<T> {
        private:
            //typedefs
            typedef typename STL_CONTAINER<T>::value_type               value_type;
            typedef typename STL_CONTAINER<T>::pointer                  pointer;
            typedef typename STL_CONTAINER<T>::reference                reference;
            typedef typename STL_CONTAINER<T>::const_reference          const_reference;
            typedef typename STL_CONTAINER<T>::size_type                size_type;
            typedef Alloc                                               allocator_type;

            using STL_CONTAINER<T>::internalBuffer_;
            using STL_CONTAINER<T>::numberOfElements_;
            
            size_type capacity_;
            allocator_type allocator;

        public:
            vector(size_type size = 0, const_reference val = value_type())
                : capacity_(size)
            {
                numberOfElements_ = size;
                internalBuffer_ = allocator.allocate(size);
                std::fill_n(internalBuffer_, size, val);
            }

            template <class ...Args>
            vector(Args ...args)
                : capacity_(std::pow(2, (int) (std::log(sizeof...(Args)) / std::log(2) + 1)))
            {
                numberOfElements_ = sizeof...(Args);
                internalBuffer_ = allocator.allocate(capacity_);
                size_type i = 0;
                (void(internalBuffer_[i++] = args), ...);
            }

            vector(const vector<value_type, allocator_type>& copy) {
                this = copy;
            }

            //Destructor
            virtual ~vector() {
                allocator.deallocate(internalBuffer_, numberOfElements_);
            }
            /**
             * This function returns the size of the vector, 
             * i.e., how many elements are in the vector.
            */
            size_type size() const {
                return numberOfElements_;
            }
            /**
             * This function returns the capacity of the
             * vector, i.e., how many elements the vector
             * has space allocated for.
            */
            size_type capacity() const {
                return capacity_;
            }
            /**
             * This function returns the maximum capacity
             * of the vector.
            */
            size_type max_size() {
                return std::min(std::pow(2, (int) (8 * sizeof(size_type) / sizeof(value_type))),
                                std::pow(2, (8 * sizeof(std::ptrdiff_t))));
            }
            /**
             * This functions clears the vector, i.e., 
             * destroys all the elements and sets the
             * size to 0.
            */
            void clear() {
                numberOfElements_ = 0;
                internalBuffer_ = allocator.allocate(0);
            }
            /**
             * This function pushes an element onto the end of
             * the vector, i.e., adds an element at the end of it.
             * @param elem The element to add to the end of the vector.
            */
            void push_back(const_reference elem) {
                pointer temp;
                if (numberOfElements_ + 1 > capacity_ || capacity_ == 0) {
                    capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;

                    temp = internalBuffer_;
                    internalBuffer_ = new T[capacity_];
                    std::copy(temp, temp + numberOfElements_, internalBuffer_);
                }
                internalBuffer_[numberOfElements_] = elem;
                numberOfElements_++;
                delete temp;
                temp = nullptr;
            }
            /**
             * This function adds an element at the beginning of the vector. 
             * This function is new.
             * @param elem The element to add to the front of the vector.
            */
            void push_front(const_reference elem) {
                pointer temp;
                if (numberOfElements_ + 1 > capacity_ || capacity_ == 0) {
                    capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
                }
                temp = internalBuffer_;
                internalBuffer_ = allocator.allocate(capacity_);
                internalBuffer_[0] = elem;
                std::copy(temp, temp + numberOfElements_, internalBuffer_ + 1);
                numberOfElements_++;
                delete temp;
                temp = nullptr;
            }
            /**
             * This function removes the last element in the vector.
             * If the vector is empty, the function does nothing, whereas in the original,
             * undefined behavior happens.
            */
            void pop_back() {
                if (numberOfElements_ == 0) return;
                pointer temp = internalBuffer_;
                numberOfElements_--;
                if (numberOfElements_ < capacity_ / 2)
                    capacity_ = (capacity_ == 1) ? 0 : capacity / 2;
                internalBuffer_ = allocator.allocate(capacity_);
                std::copy(temp, temp + numberOfElements_, internalBuffer_);
                delete temp;
                temp = nullptr;
            }
            /**
             * This function assigns the vector newSize
             * elements with value val. It discards all the
             * elements previously in the vector.
             * @param newSize The new size of the vector.
             * @param val The value which is assigned to each element in the vector.
            */
            void assign(size_type newSize, const_reference val) {
                internalBuffer_ = allocator.allocate(0);
                for (int i = 0; i < newSize; i++) {
                    this->push_back(val);
                }
            }
            /**
             * This function changes the capacity to
             * fit at least size elements.
             * @param size The new capacity of the vector.
            */
            void reserve(size_type size) {
                if (size <= capacity_)
                    return;
                capacity_ = size;
                pointer temp = internalBuffer_;
                internalBuffer_ = allocator.allocate(size);
                std::copy(temp, temp + numberOfElements_, internalBuffer_);
                delete temp;
                temp = nullptr;
            }
            /**
             * This function resizes the vector to contain 
             * n elements of size T.
             * @param n The new size to resize the vector with.
             * @param val The value used to populate the vector.
            */
            void resize(size_type n, value_type val = value_type()) {
                pointer temp = internalBuffer_;
                delete internalBuffer_;
                internalBuffer_ = allocator.allocate(n);
                std::copy(temp, temp + numberOfElements_, internalBuffer_);
                if (n > numberOfElements_) {
                    for (int i = numberOfElements_; i < n; i++) {
                        internalBuffer_[i] = val;
                    }
                }
                numberOfElements_ = n;
                delete temp;
                temp = nullptr;
            }
            /**
             * This function shrinks the vector's capacity
             * to fit its size.
            */
            void shrink_to_fit() {
                capacity_ = numberOfElements_;
            }
            /**
             * This function returns a copy of the allocator
             * object associated with the vector.
            */
            allocator_type get_allocator() const {
                return allocator;
            }
    };
}

//Overloaded == operator
template <class T>
bool operator==(std_copy::vector<T> lhs, std_copy::vector<T> rhs) {
    if (rhs.size() != lhs.size()) return false;
    for (int i = 0; i < rhs.size(); i++) {
        if (lhs.at(i) != rhs.at(i)) return false;
    }
    return true;
}
//Overloaded < operator
template <class T>
bool operator<(std_copy::vector<T> lhs, std_copy::vector<T> rhs) {
    int sizeL = lhs.size();
    int sizeR = rhs.size();
    if (sizeL != sizeR) {
        return sizeL < sizeR;
    }

    for (int i = 0; i < sizeL; i++) {
        if (lhs.at(i) < rhs.at(i)) return true;
        else if (lhs.at(i) > rhs.at(i)) return false;
    }
    return false;
}
//Overloaded != operator
template <class T>
bool operator!=(std_copy::vector<T> lhs, std_copy::vector<T> rhs) {
    return !(lhs == rhs);
}
//Overloaded > operator
template <class T>
bool operator>(std_copy::vector<T> lhs, std_copy::vector<T> rhs) {
    return rhs < lhs;
}
//Overloaded <= operator
template <class T>
bool operator<=(std_copy::vector<T> lhs, std_copy::vector<T> rhs) {
    return !(rhs < lhs);
}
//Overloaded >= operator
template <class T>
bool operator>=(std_copy::vector<T> lhs, std_copy::vector<T> rhs) {
    return !(lhs < rhs);
}


int main() {
    std_copy::vector<int> test(3, 5, 2, 4);
    for (int i = 0; i < test.size(); i++) {
        std::cout << test.at(i) << "\n";
    }
}