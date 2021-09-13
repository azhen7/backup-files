#ifndef _STD_COPY_ARRAY
#define _STD_COPY_ARRAY

#include <array>
#include <iostream>

#include <exception>
#include <cstdlib>

#include "stl.hpp"

namespace std_copy {
    /**
     * My own implementation of the STL array container, which
     * is defined in the <array> header. There are some new functions,
     * such as add(), add_front(), and others.
     * @param T The type of the elements in the array.
     * @param s The size of the array.
     * The array STL container has the same functionality as normal
     * static-sized C arrays, except you can assign one std::array
     * to another, and you can return them from functions. They also
     * come with a lot of helpful functions.
    */
    template <class T, std::size_t s>
    class array : public STL_CONTAINER<T> {
        public:
            //typdefs
            typedef typename STL_CONTAINER<T>::value_type            value_type;
            typedef typename STL_CONTAINER<T>::pointer               pointer;
            typedef typename STL_CONTAINER<T>::reference             reference;
            typedef typename STL_CONTAINER<T>::const_reference       const_reference;
            typedef typename STL_CONTAINER<T>::size_type             size_type;
            typedef iterator_type<array<T, s>>                       iterator;
            typedef const iterator_type<array<T, s>>                 const_iterator;
            
        private:
            typedef array<T, s>         array_type;

            using STL_CONTAINER<T>::internalBuffer_;
            using STL_CONTAINER<T>::numberOfElements_;

            const size_type size_;

        public:
            array() 
                : size_(s)
            {
                numberOfElements_ = 0;
                internalBuffer_ = new value_type[size_];
            }
            array(const_reference val)
                : size_(s)
            {
                internalBuffer_ = new value_type[s];
                numberOfElements_ = s;
                std::fill_n(internalBuffer_, size_, val);
            }

            template <class ...Args>
            array(Args ...args)
                : size_(s)
            {
                internalBuffer_ = new value_type[s];
                size_type i = 0;
                numberOfElements_ = sizeof...(Args);
                if (sizeof...(Args) > size_) {
                    std::cout << "Too many elements in initialization list\n";
                    exit(EXIT_FAILURE);
                }
                (void(internalBuffer_[i++] = args), ...);
            }

            array(const array_type& copy)
                : size_(s)
            {
                internalBuffer_ = new value_type[size_];
                numberOfElements_ = copy.numberOfElements_;
                std::copy(copy.internalBuffer_, copy.internalBuffer_ + numberOfElements_, internalBuffer_);
            }

            array(array_type&& copy)
                : size_(s)
            {
                internalBuffer_ = copy.internalBuffer_;
                numberOfElements_ = copy.numberOfElements_;
            }

            virtual ~array() = default;

            /**
             * This function fills the array with the
             * designated value.
             * @param val The value used to fill the array.
            */
            void fill(const_reference val) {
                std::fill_n(internalBuffer_, size_, val);
            }
            /**
             * This function returns the number of elements
             * in the array. This function is new.
            */
            size_type quantity() {
                return numberOfElements_;
            }
            /**
             * This function returns the underlying
             * internal buffer of the array.
            */
            pointer data() {
                return internalBuffer_;
            }
            /**
             * This function returns a boolean, depending
             * on whether the array is empty or not, i.e.,
             * whether there are no elements in the array.
             * This function is new.
            */
            constexpr bool empty() {
                return numberOfElements_ == 0;
            }
            /**
             * This function returns the size of the
             * array.
            */
            size_type size() const {
                return size_;
            }
            /**
             * This function returns the maximum number
             * of elements in the array.
            */
            size_type max_size() const {
                return size_;
            }
            /**
             * This function returns an iterator to the first element 
             * in the array container.
            */
            iterator begin() {
                return iterator(internalBuffer_);
            }
            /**
             * This function returns an iterator to the theoretical element 
             * after the last element in the array container.
            */
            const_iterator end() {
                return iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * This function returns an const iterator to the first element 
             * in the array container.
            */
            const_iterator cbegin() {
                return iterator(internalBuffer_);
            }
            /**
             * This function returns an const iterator to the theoretical element 
             * after the last element in the array container.
            */
            iterator cend() {
                return iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * This function pushes an element onto the end of
             * the array, i.e., adds an element at the end of it.
             * This function is new.
             * @param elem The element to add to the end of the array.
            */
            void push_back(const_reference elem) {
                if (size_ == 0) {
                    throw std::out_of_range("Array was declared with size 0; cannot add any more elements");
                }
                if (numberOfElements_ >= size_) {
                    throw std::out_of_range("Array is full; cannot add any more elements");
                }
                internalBuffer_[numberOfElements_] = elem;
                numberOfElements_++;
            }
            /**
             * This function adds an element at the front of
             * the array. This function is new.
             * @param elem The element to add to the end of the array.
            */
            void push_front(const_reference elem) {
                if (size_ == 0) {
                    throw std::out_of_range("Array was declared with size 0; cannot add any more elements");
                }
                if (numberOfElements_ >= size_) {
                    throw std::out_of_range("Array is full; cannot add any more elements");
                }
                pointer temp = internalBuffer_;
                internalBuffer_[0] = elem;
                std::copy(temp, temp + numberOfElements_, internalBuffer_ + 1);
                numberOfElements_++;
            }
            /**
             * This function removes the element at the end of
             * the array. This function is new.
            */
            void pop_back() {
                if (numberOfElements_ == 0) return;
                pointer temp = internalBuffer_;
                numberOfElements_--;
                std::copy(temp, temp + numberOfElements_, internalBuffer_);
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
                return *(internalBuffer_ + index);
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

#endif /* _STD_COPY_ARRAY */