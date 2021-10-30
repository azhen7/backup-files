#ifndef _STD_COPY_VECTOR
#define _STD_COPY_VECTOR

#include <stdexcept>
#include <cmath>
#include "algorithm.hpp"
#include "allocator.hpp"
#include "move.hpp"

#include "iterator.hpp"

namespace std_copy
{
    /**
     * My own implementation of the STL vector container, defined in
     * the <vector> header. This implementation contains a few new functions, 
     * aside from the ones in the original vector implementation, like pop_front(), 
     * push_front(), and some others.
     * @param T The type of the values the vector will contain.
     * @param Alloc The type of the object used to allocate the underlying buffer
     * used for containing the values.
    */
    template <class T, class Alloc = std_copy::allocator<T>>
    class vector
    {
        private:
            typedef vector<T, Alloc>                                vector_type;
            typedef iterator<vector_type>                           iterator_type;

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
            pointer internalBuffer_;
            size_type numberOfElements_;
            size_type capacity_;
            allocator_type allocator;

            inline size_type calculateSmallestPowerOfTwoLargerThan(int x)
            {
                return std::pow(2, (int) (std::log(x) / std::log(2)) + 1);
            }

            inline constexpr void realloc(size_type newAmount, size_type previousAmount, size_type copyUpTo)
            {
                pointer temp = internalBuffer_;
                internalBuffer_ = allocator.allocate(newAmount);
                std_copy::move(temp, temp + copyUpTo, internalBuffer_);
                allocator.deallocate(temp, previousAmount);
            }

        public:
            //Default constructor
            vector()
                : numberOfElements_(0),
                capacity_(0),
                internalBuffer_(nullptr)
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
            explicit vector(size_type size, const allocator_type& alloc)
                : capacity_(size),
                numberOfElements_(size)
            {
                internalBuffer_ = alloc.allocate(size);
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
                std_copy::fill_n(internalBuffer_, size, val);
            }
            explicit vector(size_type size, const_reference val, const allocator_type& alloc) 
                : capacity_(size),
                numberOfElements_(size)
            {
                internalBuffer_ = alloc.allocate(size);
                std_copy::fill_n(internalBuffer_, size, val);
            }
            /**
             * This constructor constructs the vector with the contents 
             * of the range [start, end).
             * @param start The start of the sequence.
             * @param end The end of the sequence.
            */
            template <class InputIt>
            vector(InputIt start, InputIt end)
                : numberOfElements_(std_copy::distance(start, end))
            {
                capacity_ = numberOfElements_;
                internalBuffer_ = allocator.allocate(numberOfElements_);
                std_copy::move(start, end, internalBuffer_);
            }
            template <class InputIt>
            vector(InputIt start, InputIt end, const allocator_type& alloc)
                : numberOfElements_(std_copy::distance(start, end))
            {
                capacity_ = numberOfElements_;
                internalBuffer_ = alloc.allocate(numberOfElements_);
                std_copy::move(start, end, internalBuffer_);
            }
            /**
             * This constructor constructs the vector to contain all 
             * the arguments passed in.
             * @param args The arguments passed in.
            */
            template <class ...Args>
            vector(Args ...args)
                : capacity_(sizeof...(args)),
                numberOfElements_(sizeof...(args))
            {
                internalBuffer_ = allocator.allocate(numberOfElements_);
                size_type i = 0;
                (void(internalBuffer_[i++] = args), ...);
            }
            template <class ...Args>
            vector(Args... args, const allocator_type& alloc)
                : capacity_(sizeof...(args)),
                numberOfElements_(sizeof...(args))
            {
                internalBuffer_ = alloc.allocate(numberOfElements_);
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
                std_copy::move(copy.internalBuffer_, copy.internalBuffer_ + numberOfElements_, internalBuffer_);
            }

            /**
             * This function initializes the vector with the contents 
             * of copy.
             * @param copy The vector to copy the elements from. It is an 
             * rvalue reference, allowing for efficient transportation of 
             * resources.
            */
            vector(vector_type&& copy)
                : capacity_(copy.capacity_),
                numberOfElements_(copy.numberOfElements_),
                internalBuffer_(copy.internalBuffer_)
            {
            }

            //Destructor
            virtual ~vector()
            {
                this->clear();
            }
            
            /**
             * This function returns the size of the vector, 
             * i.e., how many elements are in the vector.
            */
            constexpr size_type size() const noexcept
            {
                return numberOfElements_;
            }
            /**
             * This function returns the capacity of the
             * vector, i.e., how many elements the vector
             * has space allocated for.
            */
            constexpr size_type capacity() const noexcept
            {
                return capacity_;
            }
            /**
             * This function returns the underlying
             * internal buffer of the array.
            */
            constexpr pointer data() const noexcept
            {
                return internalBuffer_;
            }
            /**
             * This function returns the maximum capacity
             * of the vector.
            */
            constexpr size_type max_size() const noexcept
            {
                size_type first = std::pow(2, (int) (8 * sizeof(size_type) / sizeof(value_type)));
                size_type second = std::pow(2, (8 * sizeof(difference_type)));
                if (first < second)
                    return first;
                return second;
            }
            /**
             * This functions clears the vector, i.e., 
             * destroys all the elements and sets the
             * size to 0.
            */
            constexpr void clear()
            {
                numberOfElements_ = 0;
                capacity_ = 0;
                allocator.deallocate(internalBuffer_, capacity_);
            }
            /**
             * This function pushes an element onto the end of 
             * the vector, i.e., adds an element at the end of it.
             * @param elem The element to add to the end of the vector.
            */
            constexpr void push_back(const_reference elem)
            {
                if (numberOfElements_ + 1 > capacity_)
                {
                    capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
                    realloc(capacity_, capacity_ / 2, numberOfElements_);
                }
                internalBuffer_[numberOfElements_] = elem;
                numberOfElements_++;
            }
            /**
             * This function has the same functionality as push_back(const T&), 
             * except it pushes rvalue references.
             * @param elem The rvalue reference to push back.
            */
            constexpr void push_back(T&& elem)
            {
                this->emplace_back(std_copy::move(elem));
            }
            /**
             * This function adds an element at the beginning of the vector. 
             * This function is new.
             * @param elem The element to add to the front of the vector.
            */
            constexpr void push_front(const_reference elem)
            {
                this->insert(begin(), elem);
            }
            /**
             * This function removes the last element in the vector.
             * If the vector is empty, the function does nothing, whereas in the original,
             * undefined behavior happens.
            */
            constexpr void pop_back()
            {
                if (numberOfElements_ == 0)
                    throw std::length_error("Cannot delete element in empty vector");

                numberOfElements_--;
                (internalBuffer_ + numberOfElements_)->~value_type();
            }
            /**
             * This function removes the element at the beginning of the vector.
             * If the vector is empty, a call to this function does nothing.
             * This function is new.
            */
            constexpr void pop_front()
            {
                if (numberOfElements_ == 0)
                    throw std::length_error("Cannot delete element in empty vector");
                
                std_copy::move(internalBuffer_ + 1, internalBuffer_ + numberOfElements_, internalBuffer_);
                this->pop_back();
            }
            /**
             * This function constructs an element at pos in place.
             * @param pos The position to construct the element.
             * @param args The arguments to forward to the element's constructor.
            */
            template <class ...Args>
            constexpr reference emplace(iterator pos, Args&& ...args)
            {
                const difference_type addToGetPos = pos - this->begin();
                if (numberOfElements_ + 1 > capacity_)
                {
                    pointer temp = internalBuffer_;
                    capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
                    internalBuffer_ = allocator.allocate(capacity_);

                    std_copy::move(temp, temp + addToGetPos, internalBuffer_);
                    std_copy::move(temp + addToGetPos, temp + numberOfElements_, internalBuffer_ + addToGetPos + 1);

                    pos = this->begin() + addToGetPos;
                }
                else
                    std_copy::move_backward(internalBuffer_ + (pos - this->begin()), internalBuffer_ + numberOfElements_ - 1, internalBuffer_ + numberOfElements_);

                numberOfElements_++;
                
                std_copy::construct_at(internalBuffer_ + addToGetPos, std_copy::forward<Args>(args)...);

                return *(internalBuffer_ + numberOfElements_ - 1);
            }
            /**
             * This function constructs elements in place.
             * @param args The elements to construct in place.
            */
            template <class ...Args>
            constexpr reference emplace_back(Args&&... args)
            {
                return this->emplace(this->end(), args...);
            }
            /**
             * This function returns a reference to 
             * the element at a specified index in 
             * the vector.
             * @param index The index of the element to retrieve.
            */
            constexpr reference at(size_type index)
            {
                if (index >= numberOfElements_)
                {
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
            constexpr reference operator[](size_type index) const noexcept
            {
                return internalBuffer_[index];
            }
            /**
             * This function assigns the vector newSize 
             * elements with value val. It discards all 
             * elements previously in the vector.
             * @param newSize The new size of the vector.
             * @param val The value which is assigned to each element in the vector.
            */
            constexpr void assign(size_type newSize, const_reference val)
            {
                allocator.deallocate(internalBuffer_, capacity_);
                numberOfElements_ = newSize;
                capacity_ = newSize;
                internalBuffer_ = allocator.allocate(newSize);
                std_copy::fill(internalBuffer_, internalBuffer_ + newSize, val);
            }
            /**
             * Copies the elements from the range [first, last) into the vector.
             * @param first An iterator to the start of the range.
             * @param last An iterator to the end of the range.
            */
            template <class InputIt>
            constexpr void assign(InputIt first, InputIt last)
            {
                allocator.deallocate(internalBuffer_, capacity_);
                numberOfElements_ = std_copy::distance(first, last);
                capacity_ = numberOfElements_;
                internalBuffer_ = allocator.allocate(numberOfElements_);
                std_copy::move(first, last, internalBuffer_);
            }
            /**
             * Copies all the arguments in args into the vector.
             * @param args The arguments that are copied into the vector.
            */
            template <class ...Args>
            constexpr void assign(Args ...args)
            {
                allocator.deallocate(internalBuffer_, capacity_);
                numberOfElements_ = sizeof...(args);
                capacity_ = numberOfElements_;
                internalBuffer_ = allocator.allocate(numberOfElements_);
                size_type i = 0;
                (void(internalBuffer_[i++] = args), ...);
            }
            /**
             * This function changes the capacity to
             * fit at least size elements.
             * @param size The new capacity of the vector.
            */
            constexpr void reserve(size_type size)
            {
                if (size <= capacity_)
                    return;
                
                size_type originalCapacity = capacity_;
                capacity_ = size;
                realloc(size, originalCapacity, numberOfElements_);
            }
            /**
             * This function resizes the vector to contain 
             * n elements of type T. The vector is populated 
             * with val.
             * @param n The new size to resize the vector with.
             * @param val The value used to populate the vector.
            */
            constexpr void resize(size_type n, const_reference val)
            {
                size_type upTo = (n > numberOfElements_) ? numberOfElements_ : n;
                realloc(n, capacity_, upTo);
                numberOfElements_ = upTo;
                capacity_ = upTo;
            }
            /**
             * This function resizes the vector to contain 
             * n elements of type T. The elements in the vector 
             * are uninitialized.
             * @param n The new size to resize the vector with.
             * @param val The value used to populate the vector.
            */
            constexpr void resize(size_type n)
            {
                allocator.deallocate(internalBuffer_);
                numberOfElements_ = n;
                capacity_ = n;
                internalBuffer_ = allocator.allocate(capacity_)
;            }
            /**
             * This function returns a reference to the
             * first element in the array. If the vector
             * is empty, this function throws an exception.
            */
            constexpr reference front()
            {
                if (numberOfElements_ == 0)
                    throw std::length_error("Cannot access element in empty vector");
                
                return *internalBuffer_;
            }
            /**
             * This function returns a reference to the
             * last element in the array. If the vector 
             * is empty, this function throws an exception.
            */
            constexpr reference back()
            {
                if (numberOfElements_ == 0)
                    throw std::length_error("Cannot access element in empty vector");

                return *(internalBuffer_ + numberOfElements_ - 1);
            }
            /**
             * This function shrinks the vector's capacity
             * to fit its size.
            */
            constexpr void shrink_to_fit()
            {
                pointer temp = internalBuffer_;
                internalBuffer_ = allocator.allocate(numberOfElements_);
                std_copy::move(temp, temp + numberOfElements_, internalBuffer_);
                allocator.deallocate(internalBuffer_, capacity_);
                capacity_ = numberOfElements_;
            }
            /**
             * This function returns a copy of the allocator
             * object associated with the vector.
            */
            constexpr allocator_type get_allocator() const noexcept
            {
                return allocator;
            }
            /**
             * This function returns an iterator to the front of the vector.
            */
            constexpr iterator begin()
            {
                return iterator(internalBuffer_);
            }
            /**
             * This function returns an iterator to
             * the theoretical element after the last
             * element in the vector.
            */
            constexpr iterator end()
            {
                return iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * This function returns a const iterator to the 
             * first element in the vector.
            */
            constexpr const_iterator cbegin()
            {
                return this->begin();
            }
            /**
             * This function returns a const iterator to 
             * the theoretical element after the last element 
             * in the vector.
            */
            constexpr const_iterator cend()
            {
                return this->end();
            }
            /**
             * Overloaded assignment operator.
            */
            constexpr void operator=(const vector_type& t)
            {
                if (this == &t)
                    return;

                allocator.deallocate(internalBuffer_, numberOfElements_);
                numberOfElements_ = t.numberOfElements_;
                capacity_ = t.capacity_;
                internalBuffer_ = allocator.allocate(numberOfElements_);
                std_copy::move(t.internalBuffer_, t.internalBuffer_ + numberOfElements_, internalBuffer_);
            }
            /**
             * This function inserts an element at the position pointed to by pos.
             * @param pos The position to insert the element at.
             * @param val The value to insert.
            */
            constexpr iterator insert(iterator pos, const_reference val)
            {
                if (numberOfElements_ + 1 > capacity_)
                {
                    pointer temp = internalBuffer_;
                    difference_type addToGetPos = pos - this->begin();
                    capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
                    internalBuffer_ = allocator.allocate(capacity_);

                    std_copy::move(temp, temp + addToGetPos, internalBuffer_);
                    std_copy::move(temp + addToGetPos, temp + numberOfElements_, internalBuffer_ + addToGetPos + 1);

                    pos = this->begin() + addToGetPos;
                }
                else
                    std_copy::move_backward(pos.base(), internalBuffer_ + numberOfElements_, internalBuffer_ + numberOfElements_ + 1);

                numberOfElements_++;
                
                *pos = std_copy::move(val);
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
            constexpr iterator insert(iterator pos, InputIt first, InputIt last)
            {
                const difference_type dist = std_copy::distance(first, last);
                if (dist == 0)
                    return pos;
                numberOfElements_ += dist;
                difference_type addToGetPos = pos - this->begin();
                if (numberOfElements_ > capacity_)
                {
                    pointer temp = internalBuffer_;
                    capacity_ = calculateSmallestPowerOfTwoLargerThan(numberOfElements_);
                    internalBuffer_ = allocator.allocate(capacity_);
                    
                    std_copy::move(temp, temp + addToGetPos, internalBuffer_);
                    std_copy::move(temp + addToGetPos, temp + numberOfElements_ - dist, internalBuffer_ + addToGetPos + dist);

                    pos = this->begin() + addToGetPos;
                }

                while (first != last)
                    internalBuffer_[addToGetPos++] = std_copy::move(*first++);

                return pos;
            }
            /**
             * This function erases the elements in the range [index1, index2). Note that index1 and 
             * index2 are integers. 
             * This function is new.
             * @param index1 The start of the block to erase.
             * @param index2 The end of the block to erase.
            */
            constexpr vector_type& erase(size_type index1, size_type index2)
            {
                if (index1 >= numberOfElements_)
                {
                    std::string err = "index1 (which is " + std::to_string(index1) 
                                      + ") >= this->size() (which is " + 
                                      std::to_string(numberOfElements_) + ")";
                    throw std::out_of_range(err);
                }
                if (index2 >= numberOfElements_)
                {
                    std::string err = "index2 (which is " + std::to_string(index2) 
                                      + ") >= this->size() (which is " + 
                                      std::to_string(numberOfElements_) + ")";
                    throw std::out_of_range(err);
                }
                size_type j = 0;
                for (size_type i = 0; i < numberOfElements_; i++)
                {
                    if (i < index1 || i >= index2)
                        internalBuffer_[j++] = internalBuffer_[i];
                }
                for (; j < numberOfElements_; j++)
                    (internalBuffer_ + j)->~value_type();

                numberOfElements_ -= index2 - index1;
                return *this;
            }
            /**
             * This function erases the elements in the range [start, end). Note that start and 
             * end are iterators.
             * @param first The start of the block to erase.
             * @param last The end of the block to erase.
            */
            constexpr vector_type& erase(iterator first, iterator last)
            {
                size_type i = 0;
                for (iterator it = this->begin(); it != this->end(); it++)
                {
                    if (it < first || it >= last)
                        internalBuffer_[i++] = *it;
                }
                for (; i < numberOfElements_; i++)
                    (internalBuffer_ + i)->~value_type();

                numberOfElements_ -= std_copy::distance(first, last);
                return *this;
            }
            /**
             * This function erases the element pointed to by pos.
             * @param pos The iterator pointing to the element to be erased.
            */
            constexpr vector_type& erase(iterator pos)
            {
                size_type i = 0;
                for (iterator it = this->begin(); it != this->end(); it++)
                {
                    if (it != pos)
                        internalBuffer_[i++] = *it;
                }
                this->pop_back();
                return *this;
            }
            /**
             * This function checks for whether the vector contains an 
             * element. This function is new.
             * @param elem The element to check for.
            */
            constexpr bool contains(const_reference elem)
            {
                return this->count(elem) != 0;
            }
            /**
             * This function returns an iterator to the first occurrence 
             * of an element. If the element doesn't exist, the function 
             * returns end().
             * @param elem The element to find.
            */
            constexpr iterator find(const_reference elem)
            {
                return std_copy::find(internalBuffer_, internalBuffer_ + numberOfElements_, elem);
            }
            /**
             * This function finds how many occurrences of an element exist 
             * inside the vector.
             * @param elem The element of which to count the number of occurrences.
            */
            constexpr size_type count(const_reference elem)
            {
                return std_copy::count(internalBuffer_, internalBuffer_ + numberOfElements_, elem);
            }
            /**
             * This function swaps the contents of *this and s.
             * @param s The vector to swap the contents with.
            */
            constexpr void swap(vector_type& s)
            {
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
    template <class T, class Alloc = std_copy::allocator<T>>
    constexpr bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        if (rhs.size() != lhs.size()) 
            return false;

        for (int i = 0; i < rhs.size(); i++)
        {
            if (lhs.at(i) != rhs.at(i)) 
                return false;
        }
        return true;
    }
    /**
     * This function swaps the contents of two vectors.
     * @param lhs The first vector.
     * @param rhs The second vector.
    */
    template <class T, class Alloc = std_copy::allocator<T>>
    constexpr void swap(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        lhs.swap(rhs);
    }
    /**
     * Erases all the values that compares equal to val.
     * @param vec The vector from which the values are erased.
     * @param val The value to erase.
    */
    template <class T, class Alloc = std_copy::allocator<T>>
    unsigned long long erase(const vector<T, Alloc>& vec, const T& val) {
        auto it = std_copy::remove(vec.begin(), vec.end(), val);
        auto dist = std_copy::distance(it, vec.end());
        vec.erase(it, vec.end());
        return dist;
    }
    /**
     * Erases all the values such that func returns true for them.
     * @param val The vector from which the values are erased.
     * @param func The function used to determine which values are 
     * erased.
    */
    template <class T, class Alloc = std_copy::allocator<T>, class Function>
    unsigned long long erase_if(const vector<T, Alloc>& vec, Function func) {
        auto it = std_copy::remove_if(vec.begin(), vec.end(), func);
        auto dist = std_copy::distance(it, vec.end());
        vec.erase(it, vec.end());
        return dist;
    }
}

#endif /* _STD_COPY_VECTOR */