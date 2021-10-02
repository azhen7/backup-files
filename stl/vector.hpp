#ifndef _STD_COPY_VECTOR
#define _STD_COPY_VECTOR

#include <stdexcept>
#include <cmath>
#include "algorithm.hpp"
#include <memory>

#include "iterator.hpp"

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
    class vector {
        private:
            typedef iterator<vector<T, Alloc>>                      iterator_type;
        public:
            //typedefs
            typedef T                                               value_type;
            typedef T*                                              pointer;
            typedef const T*                                        const_pointer;
            typedef T&                                              reference;
            typedef const T&                                        const_reference;
            typedef unsigned long long                              size_type;
            typedef long long                                       difference_type;
            typedef Alloc                                           allocator_type;
            typedef iterator_type                                   iterator;
            typedef const iterator                                  const_iterator;

        private:
            typedef vector<value_type, allocator_type>                  vector_type;

            pointer internalBuffer_;
            size_type numberOfElements_;
            size_type capacity_;
            allocator_type allocator;

            size_type calculateSmallestPowerOfTwoLargerThan(int x) {
                return std::pow(2, (int) (std::log(x) / std::log(2) + 1));
            }
            
        public:
            //Default constructor
            vector()
                : numberOfElements_(0),
                capacity_(0)
            {
            }
            /**
             * This constructor allocates size number of elements of 
             * uninitialized memory.
             * @param size The amount of elements of memory to allocate.
            */
            explicit vector(size_type size)
                : capacity_(size),
                numberOfElements_(size)
            {
                internalBuffer_ = allocator.allocate(size);
            }
            /**
             * This constructor allocates size number of elements of 
             * memory, with all elements initialized to val.
             * @param size The number of elements of memory to initialize.
             * @param val The value to initialize all the elements to.
            */
            explicit vector(size_type size, const_reference val)
                : capacity_(size)
            {
                numberOfElements_ = size;
                internalBuffer_ = allocator.allocate(size);
                for (int i = 0; i < numberOfElements_; i++) {
                    internalBuffer_[i] = val;
                }
            }
            /**
             * This constructor constructs the vector with the contents 
             * of the range [start, end).
             * @param start The start of the sequence.
             * @param end The end of the sequence.
            */
            template <class InputIt>
            vector(InputIt start, InputIt end)
                : numberOfElements_(distance(start, end)),
                capacity_(distance(start, end))
            {
                internalBuffer_ = new value_type[numberOfElements_];
                size_type i = 0;
                while (start != end)
                    internalBuffer_[i++] = *start++;
            }
            /**
             * This constructor constructs the vector to contain all 
             * the arguments passed in.
             * @param args The arguments passed in.
            */
            template <class ...Args>
            vector(Args ...args)
                : capacity_(calculateSmallestPowerOfTwoLargerThan(sizeof...(Args))),
                numberOfElements_(sizeof...(Args))
            {
                internalBuffer_ = allocator.allocate(numberOfElements_);
                size_type i = 0;
                (void(internalBuffer_[i++] = args), ...);
            }

            /**
             * This function initializes the vector with the contents 
             * of copy.
             * @param copy The vector to copy the elements from.
            */
            vector(const vector_type& copy)
                : numberOfElements_(copy.numberOfElements_),
                capacity_(copy.capacity_)
            {
                internalBuffer_ = allocator.allocate(capacity_);
                std_copy::copy(copy.internalBuffer_, copy.internalBuffer_ + numberOfElements_, internalBuffer_);
            }

            /**
             * This function initializes the vector with the contents 
             * of copy.
             * @param copy The vector to copy the elements from. It is an 
             * rvalue reference, allowing for efficient transportation of 
             * resources.
            */
            vector(vector_type&& copy)
                :capacity_(copy.capacity_),
                numberOfElements_(copy.numberOfElements_),
                internalBuffer_(copy.internalBuffer_)
            {
            }

            //Destructor
            virtual ~vector() = default;
            
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
             * This function returns the underlying
             * internal buffer of the array.
            */
            pointer data() {
                return internalBuffer_;
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
                allocator.deallocate(internalBuffer_, capacity_);
            }
            /**
             * This function pushes an element onto the end of 
             * the vector, i.e., adds an element at the end of it.
             * @param elem The element to add to the end of the vector.
            */
            void push_back(const_reference elem) {
                if (!capacity_) {
                    internalBuffer_ = allocator.allocate(1);
                    capacity_ = 1;
                }
                else if (numberOfElements_ + 1 > capacity_) {
                    capacity_ *= 2;

                    pointer temp = internalBuffer_;
                    internalBuffer_ = allocator.allocate(capacity_);
                    std_copy::copy(temp, temp + numberOfElements_, internalBuffer_);
                    allocator.deallocate(temp, (int) capacity_ / 2);
                }
                internalBuffer_[numberOfElements_++] = elem;
            }
            /**
             * This function adds an element at the beginning of the vector. 
             * This function is new.
             * @param elem The element to add to the front of the vector.
            */
            void push_front(const_reference elem) {
                pointer temp = internalBuffer_;

                if (numberOfElements_ == capacity_)
                    capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;

                internalBuffer_ = allocator.allocate(capacity_);
                std_copy::copy(temp, temp + numberOfElements_, internalBuffer_ + 1);
                internalBuffer_[0] = elem;
                allocator.deallocate(temp, (int) capacity_ / 2);
                numberOfElements_++;
            }
            /**
             * This function removes the last element in the vector.
             * If the vector is empty, the function does nothing, whereas in the original,
             * undefined behavior happens.
            */
            void pop_back() {
                if (numberOfElements_ == 0) return;
                pointer t = internalBuffer_;
                numberOfElements_--;

                if (numberOfElements_ < capacity_ / 2)
                    capacity_ /= 2;

                internalBuffer_ = allocator.allocate(capacity_);
                std_copy::copy(t, t + numberOfElements_, internalBuffer_);
                size_type deallocateAmount = (capacity_ == 0) ? 1 : capacity_ * 2;
                allocator.deallocate(t, deallocateAmount);
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
            reference operator[](size_type index) {
                return internalBuffer_[index];
            }
            /**
             * This function assigns the vector newSize
             * elements with value val. It discards all
             * elements previously in the vector.
             * @param newSize The new size of the vector.
             * @param val The value which is assigned to each element in the vector.
            */
            void assign(size_type newSize, const_reference val) {
                allocator.deallocate(internalBuffer_, numberOfElements_);
                for (int i = 0; i < newSize; i++) {
                    push_back(val);
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
                std_copy::copy(temp, temp + numberOfElements_, internalBuffer_);
                allocator.deallocate(temp, capacity_);
            }
            /**
             * This function resizes the vector to contain 
             * n elements of size T.
             * @param n The new size to resize the vector with.
             * @param val The value used to populate the vector.
            */
            void resize(size_type n, const_reference val = value_type()) {
                pointer temp = internalBuffer_;
                internalBuffer_ = allocator.allocate(n);
                size_type upTo = (n > numberOfElements_) ? numberOfElements_ : n;
                std_copy::copy(temp, temp + upTo, internalBuffer_);
                allocator.deallocate(temp, capacity_);
                numberOfElements_ = n;
                capacity_ = n;
            }
            /**
             * This function returns a reference to the
             * first element in the array. If the vector
             * is empty, this function throws an exception.
            */
            reference front() {
                if (numberOfElements_ == 0) {
                    throw std::length_error("Cannot access element in empty vector");
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
                    throw std::length_error("Cannot access element in empty vector");
                }
                return internalBuffer_[numberOfElements_ - 1];
            }
            /**
             * This function shrinks the vector's capacity
             * to fit its size.
            */
            void shrink_to_fit() {
                pointer temp = internalBuffer_;
                internalBuffer_ = allocator.allocate(numberOfElements_);
                std_copy::copy(temp, temp + numberOfElements_, internalBuffer_);
                allocator.deallocate(temp, capacity_);
                capacity_ = numberOfElements_;
            }
            /**
             * This function returns a copy of the allocator
             * object associated with the vector.
            */
            allocator_type get_allocator() const {
                return allocator;
            }
            /**
             * This overloaded operator adds an element 
             * onto the end of the vector. 
             * This function is new.
             * @param val The element to add onto the
             * end of the vector.
            */
            void operator+=(const_reference val) {
                this->push_back(val);
            }
            /**
             * This function returns an iterator to the front of the vector.
            */
            iterator begin() {
                return iterator(internalBuffer_);
            }
            /**
             * This function returns an iterator to
             * the theoretical element after the last
             * element in the vector.
            */
            iterator end() {
                return iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * This function returns a const iterator to the 
             * first element in the vector.
            */
            const_iterator cbegin() {
                return (const_iterator) iterator(internalBuffer_);
            }
            /**
             * This function returns a const iterator to 
             * the theoretical element after the last element 
             * in the vector.
            */
            const_iterator cend() {
                return (const_iterator) iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * Overloaded assignment operator.
            */
            void operator=(const vector_type& t) {
                if (this == &t) return;

                allocator.deallocate(internalBuffer_, numberOfElements_);
                numberOfElements_ = t.numberOfElements_;
                capacity_ = t.capacity_;
                internalBuffer_ = allocator.allocate(numberOfElements_);
                std_copy::copy(t.internalBuffer_, t.internalBuffer_ + numberOfElements_, internalBuffer_);
            }
            /**
             * This function inserts an element at the position pointed to by pos.
             * @param pos The position to insert the element at.
             * @param val The value to insert.
            */
            iterator insert(iterator pos, const T& val) {
                if (numberOfElements_ + 1 > capacity_) {
                    capacity_ *= 2;

                    pointer temp = internalBuffer_;
                    internalBuffer_ = allocator.allocate(capacity_);
                    std_copy::copy(temp, temp + numberOfElements_, internalBuffer_);
                    allocator.deallocate(temp, (int) capacity_ / 2);
                }
                numberOfElements_++;

                for (iterator it = end() - 1; ; it--) {
                    *it = *(it - 1);
                    if (it == pos) {
                        break;
                    }
                }
                *pos = val;
                return pos;
            }
            /**
             * This function inserts the elements in the range [start, end) to the position pointed 
             * to by pos.
             * @param pos The position to insert the elements at.
             * @param start The start of the sequence of elements to insert.
             * @param end The end of the sequence of elements to insert.
            */
            template <class InputIt>
            iterator insert(iterator pos, InputIt first, InputIt last) {
                const difference_type dist = distance(first, last);
                if (dist == 0)
                    return pos;
                numberOfElements_ += dist;
                if (numberOfElements_ > capacity_) {
                    difference_type addToGetPos = distance(begin(), pos);
                    size_type originalCapacity = capacity_;
                    capacity_ = calculateSmallestPowerOfTwoLargerThan(numberOfElements_);

                    pointer temp = internalBuffer_;
                    internalBuffer_ = allocator.allocate(capacity_);
                    std_copy::copy(temp, temp + numberOfElements_ - dist, internalBuffer_);
                    allocator.deallocate(temp, originalCapacity);
                    pos = begin() + addToGetPos;
                }

                size_type i = 0;
                for (iterator it = end() - 1; ; it--) {
                    *it = *(it - dist);
                    i++;
                    if (i == dist)
                        break;
                }
                i = distance(begin(), pos);
                while (first != last) {
                    internalBuffer_[i++] = *first++;
                }
                return pos;
            }
            /**
             * This function erases the elements in the range [index1, index2). Note that index1 and 
             * index2 are integers. 
             * This function is new.
             * @param index1 The start of the block to erase.
             * @param index2 The end of the block to erase.
            */
            vector_type& erase(size_type index1, size_type index2) {
                if (index1 >= numberOfElements_) {
                    std::string err = "index1 (which is " + std::to_string(index1) 
                                      + ") >= this->size() (which is " + 
                                      std::to_string(numberOfElements_) + ")";
                    throw std::out_of_range(err);
                }
                if (index2 >= numberOfElements_) {
                    std::string err = "index2 (which is " + std::to_string(index2) 
                                      + ") >= this->size() (which is " + 
                                      std::to_string(numberOfElements_) + ")";
                    throw std::out_of_range(err);
                }
                pointer temp = internalBuffer_;
                size_type newCapacity = calculateSmallestPowerOfTwoLargerThan(numberOfElements_ - index2 + index1);
                internalBuffer_ = allocator.allocate(newCapacity);
                for (int i = 0, j = 0; i < numberOfElements_; i++) {
                    if (i < index1 || i >= index2) {
                        internalBuffer_[j++] = temp[i];
                    }
                }
                numberOfElements_ -= index2 - index1;
                allocator.deallocate(temp, capacity_);
                capacity_ = calculateSmallestPowerOfTwoLargerThan(numberOfElements_);
                return *this;
            }
            /**
             * This function erases the elements in the range [start, end). Note that start and 
             * end are iterators.
             * @param start The start of the block to erase.
             * @param end The end of the block to erase.
            */
            vector_type& erase(iterator start, iterator end) {
                pointer temp = internalBuffer_;
                const difference_type dist = distance(start, end);
                size_type newCapacity = calculateSmallestPowerOfTwoLargerThan(numberOfElements_ - dist);
                internalBuffer_ = allocator.allocate(newCapacity);
                int j = 0;
                for (iterator it = iterator(temp); it != iterator(temp + numberOfElements_); it++) {
                    if (it < start || it >= end) {
                        internalBuffer_[j++] = *it;
                    }
                }
                numberOfElements_ -= dist;
                allocator.deallocate(temp, capacity_);
                capacity_ = newCapacity;
                return *this;
            }
            /**
             * This function erases the element pointed to by pos.
             * @param pos The iterator pointing to the element to be erased.
            */
            vector_type& erase(iterator pos) {
                pointer temp = internalBuffer_;
                numberOfElements_--;
                size_type newCapacity = calculateSmallestPowerOfTwoLargerThan(numberOfElements_);
                internalBuffer_ = allocator.allocate(newCapacity);
                int j = 0;
                for (iterator it = iterator(temp); it != iterator(temp + numberOfElements_); it++) {
                    if (it != pos) {
                        internalBuffer_[j++] = *it;
                    }
                }
                allocator.deallocate(temp, capacity_);
                capacity_ = newCapacity;
                return *this;
            }
            /**
             * This function swaps the contents of *this and s.
             * @param s The vector to swap the contents with.
            */
            void swap(vector_type& s) {
                pointer temp = s.internalBuffer_;
                s.internalBuffer_ = internalBuffer_;
                internalBuffer_ = temp;

                size_type tempCapacity = s.capacity_;
                s.capacity_ = capacity_;
                capacity_ = tempCapacity;

                size_type tempNumberOfElems = s.numberOfElements_;
                s.numberOfElements_ = numberOfElements_;
                numberOfElements_ = tempNumberOfElems;
            }
    };
    //Overloaded == operator
    template <class T, class Alloc = std::allocator<T>>
    bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        if (rhs.size() != lhs.size()) 
            return false;

        for (int i = 0; i < rhs.size(); i++) {
            if (lhs.at(i) != rhs.at(i)) 
                return false;
        }
        return true;
    }
    //Overloaded < operator
    template <class T, class Alloc = std::allocator<T>>
    bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        int sizeL = lhs.size();
        int sizeR = rhs.size();
        if (sizeL != sizeR)
            return sizeL < sizeR;

        for (int i = 0; i < sizeL; i++) {
            if (lhs.at(i) < rhs.at(i)) 
                return true;

            else if (lhs.at(i) > rhs.at(i)) 
                return false;
        }
        return false;
    }
    //Overloaded != operator
    template <class T, class Alloc = std::allocator<T>>
    bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs == rhs);
    }
    //Overloaded > operator
    template <class T, class Alloc = std::allocator<T>>
    bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return rhs < lhs;
    }
    //Overloaded <= operator
    template <class T, class Alloc = std::allocator<T>>
    bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(rhs < lhs);
    }
    //Overloaded >= operator
    template <class T, class Alloc = std::allocator<T>>
    bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs < rhs);
    }
    /**
     * This function swaps the contents of two vectors.
     * @param lhs The first vector.
     * @param rhs The second vector.
    */
    template <class T, class Alloc>
    void swap(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        lhs.swap(rhs);
    }
}

#endif /* _STD_COPY_VECTOR */