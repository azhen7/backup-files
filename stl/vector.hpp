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
            typedef vector<T, Alloc>                                _vector_type;
            typedef iterator<_vector_type>                          _iterator_type;

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
            typedef _iterator_type                                  iterator;
            typedef const iterator                                  const_iterator;

        private:
            pointer _internalBuffer;
            size_type _numberOfElements;
            size_type _capacity;

            size_type _exponent(size_type x, size_type y)
            {
                size_type result = 1;
                while (y > 0)
                {
                    if (y % 2 == 0)
                    {
                        x *= x;
                        y /= 2;
                    }
                    else
                    {
                        result *= x;
                        y--;
                    }
                }
                return result;
            }
            inline size_type _calculateSmallestPowerOfTwoGreaterThan(size_type x)
            {
                return _exponent(2, (size_type) (std::log(x) / std::log(2)) + 1);
            }
            constexpr void _realloc(size_type newAmount, size_type previousAmount, size_type copyUpTo)
            {
                pointer temp = _internalBuffer;
                _internalBuffer = allocator_type::allocate(newAmount);
                std_copy::move(temp, temp + copyUpTo, _internalBuffer);
                allocator_type::deallocate(temp, previousAmount);
            }

        public:
            //Default constructor
            vector()
                : _numberOfElements(0),
                _capacity(0),
                _internalBuffer(nullptr)
            {
            }
            /**
             * This constructor allocates size number of elements of 
             * uninitialized memory.
             * @param size The amount of elements of memory to allocate.
            */
            explicit vector(size_type size)
                : _capacity(size),
                _numberOfElements(size)
            {
                _internalBuffer = allocator_type::allocate(size);
            }
            explicit vector(size_type size, const allocator_type& alloc)
                : _capacity(size),
                _numberOfElements(size)
            {
                _internalBuffer = alloc.allocate(size);
            }
            /**
             * This constructor allocates size number of elements of 
             * memory, with all elements initialized to val.
             * @param size The number of elements of memory to initialize.
             * @param val The value to initialize all the elements to.
            */
            explicit vector(size_type size, const_reference val)
                : _capacity(size)
            {
                _numberOfElements = size;
                _internalBuffer = allocator_type::allocate(size);
                std_copy::fill_n(_internalBuffer, size, val);
            }
            explicit vector(size_type size, const_reference val, const allocator_type& alloc) 
                : _capacity(size),
                _numberOfElements(size)
            {
                _internalBuffer = alloc.allocate(size);
                std_copy::fill_n(_internalBuffer, size, val);
            }
            /**
             * This constructor constructs the vector with the contents 
             * of the range [start, end).
             * @param start The start of the sequence.
             * @param end The end of the sequence.
            */
            template <class InputIt>
            vector(InputIt start, InputIt end)
                : _numberOfElements(std_copy::distance(start, end))
            {
                _capacity = _numberOfElements;
                _internalBuffer = allocator_type::allocate(_numberOfElements);
                std_copy::move(start, end, _internalBuffer);
            }
            template <class InputIt>
            vector(InputIt start, InputIt end, const allocator_type& alloc)
                : _numberOfElements(std_copy::distance(start, end))
            {
                _capacity = _numberOfElements;
                _internalBuffer = alloc.allocate(_numberOfElements);
                std_copy::move(start, end, _internalBuffer);
            }
            /**
             * This constructor constructs the vector to contain all 
             * the arguments passed in.
             * @param args The arguments passed in.
            */
            template <class ...Args>
            vector(Args ...args)
                : _capacity(sizeof...(args)),
                _numberOfElements(sizeof...(args))
            {
                _internalBuffer = allocator_type::allocate(_numberOfElements);
                size_type i = 0;
                (void(_internalBuffer[i++] = args), ...);
            }
            template <class ...Args>
            vector(Args... args, const allocator_type& alloc)
                : _capacity(sizeof...(args)),
                _numberOfElements(sizeof...(args))
            {
                _internalBuffer = alloc.allocate(_numberOfElements);
                size_type i = 0;
                (void(_internalBuffer[i++] = args), ...);
            }
            /**
             * This function initializes the vector with the contents 
             * of copy.
             * @param copy The vector to copy the elements from.
            */
            vector(const _vector_type& copy)
                : _numberOfElements(copy._numberOfElements),
                _capacity(copy._capacity)
            {
                _internalBuffer = allocator_type::allocate(_capacity);
                std_copy::move(copy._internalBuffer, copy._internalBuffer + _numberOfElements, _internalBuffer);
            }

            /**
             * This function initializes the vector with the contents 
             * of copy.
             * @param copy The vector to copy the elements from. It is an 
             * rvalue reference, allowing for efficient transportation of 
             * resources.
            */
            vector(_vector_type&& copy)
                : _capacity(copy._capacity),
                _numberOfElements(copy._numberOfElements)
            {
                _internalBuffer = allocator_type::allocate(_capacity);
                std_copy::move(copy._internalBuffer, copy._internalBuffer + _numberOfElements, _internalBuffer);
            }
            vector(_vector_type&& copy, const allocator_type& a)
                : _capacity(copy._capacity),
                _numberOfElements(copy._numberOfElements)
            {
                _internalBuffer = a.allocate(_capacity);
                std_copy::move(copy._internalBuffer, copy._internalBuffer + _numberOfElements, _internalBuffer);
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
            [[nodiscard]] constexpr size_type size() noexcept
            {
                return _numberOfElements;
            }
            /**
             * Returns a bool corresponding to whether the vector 
             * is empty.
            */
            [[nodiscard]] constexpr bool empty() noexcept
            {
                return _numberOfElements == 0;
            }
            /**
             * This function returns the capacity of the
             * vector, i.e., how many elements the vector
             * has space allocated for.
            */
            constexpr size_type capacity() noexcept
            {
                return _capacity;
            }
            /**
             * This function returns the underlying
             * internal buffer of the array.
            */
            constexpr pointer data() noexcept
            {
                return _internalBuffer;
            }
            /**
             * This function returns the maximum capacity
             * of the vector.
            */
            constexpr size_type max_size() noexcept
            {
                size_type first = _exponent(2, (int) (8 * sizeof(size_type) / sizeof(value_type)));
                size_type second = _exponent(2, (8 * sizeof(difference_type)));
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
                _numberOfElements = 0;
                _capacity = 0;
                allocator_type::deallocate(_internalBuffer, _capacity);
            }
            /**
             * This function pushes an element onto the end of 
             * the vector, i.e., adds an element at the end of it.
             * @param elem The element to add to the end of the vector.
            */
            constexpr void push_back(const_reference elem)
            {
                if (_numberOfElements + 1 > _capacity)
                {
                    _capacity = (_capacity == 0) ? 1 : _capacity * 2;
                    _realloc(_capacity, _capacity / 2, _numberOfElements);
                }
                _internalBuffer[_numberOfElements] = elem;
                _numberOfElements++;
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
                this->insert(this->begin(), elem);
            }
            /**
             * This function removes the last element in the vector.
             * If the vector is empty, the function does nothing, whereas in the original,
             * undefined behavior happens.
            */
            constexpr void pop_back()
            {
                if (_numberOfElements == 0)
                    throw std::length_error("vector::pop_back: Cannot delete element in empty vector");

                _numberOfElements--;
                (_internalBuffer + _numberOfElements)->~value_type();
            }
            /**
             * This function removes the element at the beginning of the vector.
             * If the vector is empty, a call to this function does nothing.
             * This function is new.
            */
            constexpr void pop_front()
            {
                if (_numberOfElements == 0)
                    throw std::length_error("vector::pop_front: Cannot delete element in empty vector");
                
                std_copy::move(_internalBuffer + 1, _internalBuffer + _numberOfElements, _internalBuffer);
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
                if (_numberOfElements + 1 > _capacity)
                {
                    pointer temp = _internalBuffer;
                    _capacity = (_capacity == 0) ? 1 : _capacity * 2;
                    _internalBuffer = allocator_type::allocate(_capacity);

                    std_copy::move(temp, temp + addToGetPos, _internalBuffer);
                    std_copy::move(temp + addToGetPos, temp + _numberOfElements, _internalBuffer + addToGetPos + 1);

                    pos = this->begin() + addToGetPos;
                }
                else
                    std_copy::move_backward(_internalBuffer + (pos - this->begin()), _internalBuffer + _numberOfElements - 1, _internalBuffer + _numberOfElements);

                _numberOfElements++;
                
                std_copy::construct_at(_internalBuffer + addToGetPos, std_copy::forward<Args>(args)...);

                return *(_internalBuffer + _numberOfElements - 1);
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
                if (index >= _numberOfElements)
                {
                    std::string err = "vector::at: index (which is " + std::to_string(index) + ") >= this->size() (which is " + 
                                    std::to_string(_numberOfElements) + ")";

                    throw std::out_of_range(err);
                }
                return *(_internalBuffer + index);
            }
            /**
             * The [] operator is overloaded to provide C-style array
             * indexing.
             * @param index The index of the element to retrieve.
            */
            constexpr reference operator[](size_type index) noexcept
            {
                return _internalBuffer[index];
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
                allocator_type::deallocate(_internalBuffer, _capacity);
                _numberOfElements = newSize;
                _capacity = newSize;
                _internalBuffer = allocator_type::allocate(newSize);
                std_copy::fill(_internalBuffer, _internalBuffer + newSize, val);
            }
            /**
             * Copies the elements from the range [first, last) into the vector.
             * @param first An iterator to the start of the range.
             * @param last An iterator to the end of the range.
            */
            template <class InputIt>
            constexpr void assign(InputIt first, InputIt last)
            {
                allocator_type::deallocate(_internalBuffer, _capacity);
                _numberOfElements = std_copy::distance(first, last);
                _capacity = _numberOfElements;
                _internalBuffer = allocator_type::allocate(_numberOfElements);
                std_copy::move(first, last, _internalBuffer);
            }
            /**
             * Copies all the arguments in args into the vector.
             * @param args The arguments that are copied into the vector.
            */
            template <class ...Args>
            constexpr void assign(Args ...args)
            {
                allocator_type::deallocate(_internalBuffer, _capacity);
                _numberOfElements = sizeof...(args);
                _capacity = _numberOfElements;
                _internalBuffer = allocator_type::allocate(_numberOfElements);
                size_type i = 0;
                (void(_internalBuffer[i++] = args), ...);
            }
            /**
             * This function changes the capacity to
             * fit at least size elements.
             * @param size The new capacity of the vector.
            */
            constexpr void reserve(size_type size)
            {
                if (size <= _capacity)
                    return;
                
                size_type originalCapacity = _capacity;
                _capacity = size;
                _realloc(size, originalCapacity, _numberOfElements);
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
                size_type upTo = (n > _numberOfElements) ? _numberOfElements : n;
                _realloc(n, _capacity, upTo);
                _numberOfElements = upTo;
                _capacity = upTo;
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
                pointer temp = _internalBuffer;
                _internalBuffer = allocator_type::allocate(_capacity);
                size_type copyUpTo = (n > _numberOfElements) ? _numberOfElements : n;
                std_copy::move(temp, temp + copyUpTo, _internalBuffer);
                allocator_type::deallocate(temp, _capacity);
                _numberOfElements = n;
                _capacity = n;
            }
            /**
             * This function returns a reference to the
             * first element in the array. If the vector
             * is empty, this function throws an exception.
            */
            constexpr reference front()
            {
                if (_numberOfElements == 0)
                    throw std::length_error("vector::front: Cannot access element in empty vector");
                
                return *_internalBuffer;
            }
            /**
             * This function returns a reference to the
             * last element in the array. If the vector 
             * is empty, this function throws an exception.
            */
            constexpr reference back()
            {
                if (_numberOfElements == 0)
                    throw std::length_error("vector::back: Cannot access element in empty vector");

                return *(_internalBuffer + _numberOfElements - 1);
            }
            /**
             * This function shrinks the vector's capacity
             * to fit its size.
            */
            constexpr void shrink_to_fit()
            {
                pointer temp = _internalBuffer;
                _internalBuffer = allocator_type::allocate(_numberOfElements);
                std_copy::move(temp, temp + _numberOfElements, _internalBuffer);
                allocator_type::deallocate(temp, _capacity);
                _capacity = _numberOfElements;
            }
            /**
             * This function returns a copy of the _allocator
             * object associated with the vector.
            */
            constexpr allocator_type get_allocator() noexcept
            {
                return allocator_type();
            }
            /**
             * This function returns an iterator to the front of the vector.
            */
            constexpr iterator begin()
            {
                return iterator(_internalBuffer);
            }
            /**
             * This function returns an iterator to the theoretical element after the last element in the vector.
            */
            constexpr iterator end()
            {
                return iterator(_internalBuffer + _numberOfElements);
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
            constexpr void operator=(const _vector_type& t)
            {
                if (this == &t)
                    return;

                allocator_type::deallocate(_internalBuffer, _numberOfElements);
                _numberOfElements = t._numberOfElements;
                _capacity = t._capacity;
                _internalBuffer = allocator_type::allocate(_numberOfElements);
                std_copy::move(t._internalBuffer, t._internalBuffer + _numberOfElements, _internalBuffer);
            }
            /**
             * This function inserts an element at the position pointed to by pos.
             * @param pos The position to insert the element at.
             * @param val The value to insert.
            */
            constexpr iterator insert(iterator pos, const_reference val)
            {
                if (_numberOfElements + 1 > _capacity)
                {
                    pointer temp = _internalBuffer;
                    difference_type addToGetPos = pos - this->begin();
                    _capacity = (_capacity == 0) ? 1 : _capacity * 2;
                    _internalBuffer = allocator_type::allocate(_capacity);

                    std_copy::move(temp, temp + addToGetPos, _internalBuffer);
                    std_copy::move(temp + addToGetPos, temp + _numberOfElements, _internalBuffer + addToGetPos + 1);

                    pos = this->begin() + addToGetPos;
                }
                else
                    std_copy::move_backward(pos.base(), _internalBuffer + _numberOfElements, _internalBuffer + _numberOfElements + 1);

                _numberOfElements++;
                
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
                _numberOfElements += dist;
                difference_type addToGetPos = pos - this->begin();
                if (_numberOfElements > _capacity)
                {
                    pointer temp = _internalBuffer;
                    _capacity = _calculateSmallestPowerOfTwoGreaterThan(_numberOfElements);
                    _internalBuffer = allocator_type::allocate(_capacity);
                    
                    std_copy::move(temp, temp + addToGetPos, _internalBuffer);
                    std_copy::move(temp + addToGetPos, temp + _numberOfElements - dist, _internalBuffer + addToGetPos + dist);

                    pos = this->begin() + addToGetPos;
                }

                while (first != last)
                    _internalBuffer[addToGetPos++] = std_copy::move(*first++);

                return pos;
            }
            /**
             * This function erases the elements in the range [index1, index2). Note that index1 and 
             * index2 are integers. 
             * This function is new.
             * @param index1 The start of the block to erase.
             * @param index2 The end of the block to erase.
            */
            constexpr _vector_type& erase(size_type index1, size_type index2)
            {
                if (index1 >= _numberOfElements)
                {
                    std::string err = "vector::erase: index1 (which is " + std::to_string(index1) 
                                      + ") >= this->size() (which is " + 
                                      std::to_string(_numberOfElements) + ")";
                    throw std::out_of_range(err);
                }
                if (index2 >= _numberOfElements)
                {
                    std::string err = "vector::erase: index2 (which is " + std::to_string(index2) 
                                      + ") >= this->size() (which is " + 
                                      std::to_string(_numberOfElements) + ")";
                    throw std::out_of_range(err);
                }
                size_type j = 0;
                for (size_type i = 0; i < _numberOfElements; i++)
                {
                    if (i < index1 || i >= index2)
                        _internalBuffer[j++] = _internalBuffer[i];
                }
                for (; j < _numberOfElements; j++)
                    (_internalBuffer + j)->~value_type();

                _numberOfElements -= index2 - index1;
                return *this;
            }
            /**
             * This function erases the elements in the range [start, end). Note that start and 
             * end are iterators.
             * @param first The start of the block to erase.
             * @param last The end of the block to erase.
            */
            constexpr _vector_type& erase(iterator first, iterator last)
            {
                size_type i = 0;
                for (iterator it = this->begin(); it != this->end(); it++)
                {
                    if (it < first || it >= last)
                        _internalBuffer[i++] = *it;
                }
                for (; i < _numberOfElements; i++)
                    (_internalBuffer + i)->~value_type();

                _numberOfElements -= std_copy::distance(first, last);
                return *this;
            }
            /**
             * This function erases the element pointed to by pos.
             * @param pos The iterator pointing to the element to be erased.
            */
            constexpr _vector_type& erase(iterator pos)
            {
                size_type i = 0;
                for (iterator it = this->begin(); it != this->end(); it++)
                {
                    if (it != pos)
                        _internalBuffer[i++] = *it;
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
                return std_copy::find(_internalBuffer, _internalBuffer + _numberOfElements, elem);
            }
            /**
             * This function finds how many occurrences of an element exist 
             * inside the vector.
             * @param elem The element of which to count the number of occurrences.
            */
            constexpr size_type count(const_reference elem)
            {
                return std_copy::count(_internalBuffer, _internalBuffer + _numberOfElements, elem);
            }
            /**
             * This function swaps the contents of *this and s.
             * @param s The vector to swap the contents with.
            */
            constexpr void swap(_vector_type& s)
            {
                pointer temp = s._internalBuffer;
                s._internalBuffer = _internalBuffer;
                _internalBuffer = temp;

                size_type tempCapacity = s._capacity;
                s._capacity = _capacity;
                _capacity = tempCapacity;

                size_type tempNumberOfElems = s._numberOfElements;
                s._numberOfElements = _numberOfElements;
                _numberOfElements = tempNumberOfElems;
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