#ifndef _STD_COPY_VECTOR
#define _STD_COPY_VECTOR

#include <stdexcept>
#include <cstdint>

#include "algorithm.hpp"
#include "allocator.hpp"
#include "move.hpp"
#include "iterator_funcs.hpp"
#include "construct_destroy.hpp"
#include "uninitialized_algo.hpp"
#include "iterator_adaptors.hpp"

namespace std_copy
{
    /**
     * An implementation of the STL vector container, defined in
     * the <vector> header. This implementation contains a few new functions, 
     * aside from the ones in the original vector implementation, like pop_front(), 
     * push_front(), and some others.
     * @param T The type of the values the vector will contain.
     * @param Alloc The type of the object used to allocate the underlying buffer
     * used for containing the values.
    */
    template <class T, class Alloc = allocator<T>>
#if __cplusplus > 201703L
    requires _std_copy_hidden::_std_copy_allocator::_is_valid_allocator<Alloc>
#endif
    class vector
    {
        protected:
            typedef vector<T, Alloc>                                _vector_type;

        public:
            //typedefs
            typedef T                                               value_type;
            typedef T*                                              pointer;
            typedef const T*                                        const_pointer;
            typedef T&                                              reference;
            typedef const T&                                        const_reference;
            typedef std::size_t                                     size_type;
            typedef std::ptrdiff_t                                  difference_type;
            typedef Alloc                                           allocator_type;
            typedef _std_copy_hidden::_std_copy_stl_containers::_iterator<pointer, _vector_type> iterator;
            typedef _std_copy_hidden::_std_copy_stl_containers::_iterator<const_pointer, _vector_type> const_iterator;
            typedef reverse_iterator<pointer>                       reverse_iterator;
            typedef const reverse_iterator                          const_reverse_iterator;

        protected:
            pointer _internalBuffer;
            size_type _numberOfElements;
            size_type _capacity;

            inline size_type _power_of_smallest_power_of_two_greater_than(size_type x)
            {
                size_type count = 0ULL;
                while (x >>= 1ULL && x > 0ULL && (count++ || 1));
                
                return count;
            }
            void _realloc(size_type newAmount, size_type previousAmount, size_type copyUpTo)
            {
                if (_numberOfElements == 0)
                {
                    _internalBuffer = allocator_type::allocate(newAmount);
                    return;
                }
                pointer temp = _internalBuffer;
                _internalBuffer = allocator_type::allocate(newAmount);
                uninitialized_move(temp, temp + copyUpTo, _internalBuffer);
                allocator_type::deallocate(temp, previousAmount);
            }

            difference_type _realloc_create_insert_space(
                difference_type addToGetPos,
                difference_type copyFrom,
                size_type copyUpTo,
                size_type c
            )
            {
                difference_type secondCopy = addToGetPos;

                pointer temp = _internalBuffer;
                _capacity = c;
                _internalBuffer = allocator_type::allocate(_capacity);

                uninitialized_move(temp, temp + addToGetPos, _internalBuffer);
                uninitialized_move(temp + secondCopy, temp + copyUpTo, _internalBuffer + copyFrom);

                allocator_type::deallocate(temp, c >> 1ULL);

                return addToGetPos;
            }

            size_type _get_new_capacity()
            {
                return (_capacity == 0ULL) ? 1ULL : _capacity << 1ULL;
            }

            void _resize(size_type n, const_reference val)
            {
                pointer temp = _internalBuffer;
                _internalBuffer = allocator_type::allocate(n);
                size_type copyUpTo = (n > _numberOfElements) ? _numberOfElements : n;
                uninitialized_move(temp, temp + copyUpTo, _internalBuffer);
                allocator_type::deallocate(temp, _capacity);

                if (n > _numberOfElements)
                {
                    uninitialized_fill(_internalBuffer + _numberOfElements, _internalBuffer + n, val);
                }

                _numberOfElements = n;
                _capacity = n;
            }

        public:
            //Default constructor
            vector() : _numberOfElements(0), _capacity(0) {}
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
                fill_n(_internalBuffer, size, val);
            }
            explicit vector(size_type size, const_reference val, const allocator_type& alloc) 
                : _capacity(size),
                _numberOfElements(size)
            {
                _internalBuffer = alloc.allocate(size);
                fill_n(_internalBuffer, size, val);
            }
            /**
             * This constructor constructs the vector with the contents 
             * of the range [start, end).
             * @param start The start of the sequence.
             * @param end The end of the sequence.
            */
            template <class InputIterator>
        #if __cplusplus > 201703L
            requires input_iterator<InputIterator>
        #endif
            vector(InputIterator start, InputIterator end)
            {
                _numberOfElements = std_copy::distance(start, end);
                _capacity = _numberOfElements;
                _internalBuffer = allocator_type::allocate(_numberOfElements);
                uninitialized_move(start, end, _internalBuffer);
            }
            template <class InputIterator>
        #if __cplusplus > 201703L
            requires input_iterator<InputIterator>
        #endif
            vector(InputIterator start, InputIterator end, const allocator_type& alloc)
            {
                _numberOfElements = std_copy::distance(start, end);
                _capacity = _numberOfElements;
                _internalBuffer = alloc.allocate(_numberOfElements);
                uninitialized_move(start, end, _internalBuffer);
            }

        #if __cplusplus > 201103L
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
        #endif

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
                uninitialized_move(copy._internalBuffer, copy._internalBuffer + _numberOfElements, _internalBuffer);
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
                _numberOfElements(copy._numberOfElements),
                _internalBuffer(move(copy._internalBuffer))
            {
            }
            vector(_vector_type&& copy, const allocator_type& a)
                : _capacity(copy._capacity),
                _numberOfElements(copy._numberOfElements),
                _internalBuffer(move(copy._internalBuffer))
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
            size_type size() const noexcept { return _numberOfElements; }
            /**
             * Returns a bool corresponding to whether the vector 
             * is empty.
            */
            bool empty() const noexcept { return _numberOfElements == 0ULL; }
            /**
             * This function returns the capacity of the
             * vector, i.e., how many elements the vector
             * has space allocated for.
            */
            size_type capacity() const noexcept { return _capacity; }
            /**
             * This function returns the underlying
             * internal buffer of the array.
            */
            pointer data() const noexcept { return _internalBuffer; }
            /**
             * This function returns the maximum capacity
             * of the vector.
            */
            size_type max_size() const noexcept
            {
                size_type first = 1ULL << ((size_type) (8ULL * sizeof(size_type) / sizeof(value_type)));
                size_type second = 1ULL << (sizeof(difference_type) << 3ULL);
                if (first < second)
                    return first;
                return second;
            }
            /**
             * This functions clears the vector, i.e., 
             * destroys all the elements and sets the
             * size to 0.
            */
            void clear()
            {
                destroy(_internalBuffer, _internalBuffer + _numberOfElements);
                allocator_type::deallocate(_internalBuffer, _capacity);
                _numberOfElements = 0ULL;
                _capacity = 0ULL;
            }
            /**
             * This function pushes an element onto the end of 
             * the vector, i.e., adds an element at the end of it.
             * @param elem The element to add to the end of the vector.
            */
            void push_back(const_reference elem)
            {
                if (_numberOfElements ==  _capacity)
                {
                    _capacity = _get_new_capacity();
                    _realloc(_capacity, _capacity >> 1ULL, _numberOfElements);
                }
                construct_at(_internalBuffer + _numberOfElements, elem);
                _numberOfElements++;
            }
            /**
             * This function has the same functionality as push_back(const T&), 
             * except it pushes rvalue references.
             * @param elem The rvalue reference to push back.
            */
            void push_back(T&& elem)
            {
                this->emplace_back(move(elem));
            }
            /**
             * This function adds an element at the beginning of the vector. 
             * This function is new.
             * @param elem The element to add to the front of the vector.
            */
            void push_front(const_reference elem)
            {
                this->insert(this->cbegin(), elem);
            }
            /**
             * This function removes the last element in the vector.
            */
            void pop_back()
            {
                (_internalBuffer + _numberOfElements - 1)->~value_type();
                _numberOfElements--;
            }
            /**
             * This function removes the element at the beginning of the vector.
            */
            void pop_front()
            {
                move(_internalBuffer + 1, _internalBuffer + _numberOfElements, _internalBuffer);
                this->pop_back();
            }
            /**
             * This function constructs an element at pos in place.
             * @param pos The position to construct the element.
             * @param args The arguments to forward to the element's constructor.
            */
            template <class ...Args>
            iterator emplace(const_iterator pos, Args&& ...args)
            {
                const difference_type addToGetPos = pos - this->cbegin();
                if (_numberOfElements ==  _capacity)
                    _realloc_create_insert_space(addToGetPos, addToGetPos + 1, _numberOfElements, _get_new_capacity());
                else
                    uninitialized_move_backward(_internalBuffer + addToGetPos, _internalBuffer + _numberOfElements, _internalBuffer + _numberOfElements + 1);

                _numberOfElements++;
            
                construct_at(_internalBuffer + addToGetPos, forward<Args>(args)...);

                return iterator(_internalBuffer + addToGetPos);
            }
            /**
             * This function constructs elements in place.
             * @param args The elements to construct in place.
            */
            template <class ...Args>
            reference emplace_back(Args&&... args)
            {
                this->emplace(this->cend(), forward<Args>(args)...);
                return this->back();
            }
            /**
             * This function returns a reference to 
             * the element at a specified index in 
             * the vector.
             * @param index The index of the element to retrieve.
            */
            reference at(size_type index) const
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
            reference operator[](size_type index) const
            {
                return *(_internalBuffer + index);
            }
            /**
             * This function assigns the vector newSize 
             * elements with value val. It discards all 
             * elements previously in the vector.
             * @param newSize The new size of the vector.
             * @param val The value which is assigned to each element in the vector.
            */
            void assign(size_type newSize, const_reference val)
            {
                allocator_type::deallocate(_internalBuffer, _capacity);
                _numberOfElements = newSize;
                _capacity = newSize;
                _internalBuffer = allocator_type::allocate(newSize);
                fill(_internalBuffer, _internalBuffer + newSize, val);
            }
            /**
             * Copies the elements from the range [first, last) into the vector.
             * @param first An iterator to the start of the range.
             * @param last An iterator to the end of the range.
            */
            template <class InputIterator>
            void assign(InputIterator first, InputIterator last)
        #if __cplusplus > 201703L
            requires input_iterator<InputIterator>
        #endif
            {
                allocator_type::deallocate(_internalBuffer, _capacity);
                _numberOfElements = std_copy::distance(first, last);
                _capacity = _numberOfElements;
                _internalBuffer = allocator_type::allocate(_numberOfElements);
                uninitialized_move(first, last, _internalBuffer);
            }
            /**
             * Copies the elements from the vector s into the vector.
             * @param s The vector to copy from.
            */
            void assign(const _vector_type& s)
            {
                this->assign(s._internalBuffer, s._internalBuffer + s._numberOfElements);
            }
            /**
             * Copies the elements from the rvalue-reference'd vector s into the vector.
             * @param s The vector to copy from.
            */
            void assign(_vector_type&& s)
            {
                this->assign(move(s._internalBuffer), move(s._internalBuffer + s._numberOfElements));
            }
            /**
             * Copies all the arguments in args into the vector.
             * @param args The arguments that are copied into the vector.
            */
            template <class ...Args>
            void assign(Args ...args)
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
            void reserve(size_type size)
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
            void resize(size_type n, const_reference val)
            {
                _resize(n, val);
            }
            /**
             * This function resizes the vector to contain 
             * n elements of type T. The elements in the vector 
             * are default-initialized.
             * @param n The new size to resize the vector with.
            */
            void resize(size_type n)
            {
                _resize(n, value_type());
            }
            /**
             * This function returns a reference to the
             * first element in the array.
            */
            reference front() const noexcept { return *_internalBuffer; }
            /**
             * This function returns a reference to the
             * last element in the array.
            */
            reference back() const noexcept { return *(_internalBuffer + _numberOfElements - 1); }
            /**
             * This function shrinks the vector's capacity
             * to fit its size.
            */
            void shrink_to_fit()
            {
                pointer temp = _internalBuffer;
                _internalBuffer = allocator_type::allocate(_numberOfElements);
                uninitialized_move(temp, temp + _numberOfElements, _internalBuffer);
                allocator_type::deallocate(temp, _capacity);
                _capacity = _numberOfElements;
            }
            /**
             * This function returns a copy of the _allocator
             * object associated with the vector.
            */
            allocator_type get_allocator() const noexcept { return allocator_type(); }
            /**
             * This function returns an iterator to the front of the vector.
            */
            iterator begin() const noexcept { return iterator(_internalBuffer); }
            /**
             * This function returns an iterator to the theoretical element after the last element in the vector.
            */
            iterator end() const noexcept { return iterator(_internalBuffer + _numberOfElements); }
            /**
             * Returns a reverse iterator to the reverse beginning of the vector.
            */
            reverse_iterator rbegin() const noexcept { return reverse_iterator(_internalBuffer + _numberOfElements); }
            /**
             * Returns a reverse iterator to the reverse end of the vector.
            */
            reverse_iterator rend() const noexcept { return reverse_iterator(_internalBuffer); }
            /**
             * Returns a const reverse iterator to the reverse beginning of the vector.
            */
            const_reverse_iterator crbegin() const noexcept { return reverse_iterator(_internalBuffer + _numberOfElements); }
            /**
             * Returns a const reverse iterator to the reverse end of the vector.
            */
            const_reverse_iterator crend() const noexcept { return reverse_iterator(_internalBuffer); }
            /**
             * This function returns a const iterator to the 
             * first element in the vector.
            */
            const_iterator cbegin() const noexcept { return const_iterator(_internalBuffer); }
            /**
             * This function returns a const iterator to 
             * the theoretical element after the last element 
             * in the vector.
            */
            const_iterator cend() const noexcept { return const_iterator(_internalBuffer + _numberOfElements); }
            /**
             * Overloaded assignment operator.
            */
            void operator=(const _vector_type& t)
            {
                if (std_copy::addressof(*this) == std_copy::addressof(t))
                    return;

                allocator_type::deallocate(_internalBuffer, _numberOfElements);
                _numberOfElements = t._numberOfElements;
                _capacity = t._capacity;
                _internalBuffer = allocator_type::allocate(_numberOfElements);
                uninitialized_move(t._internalBuffer, t._internalBuffer + _numberOfElements, _internalBuffer);
            }
            /**
             * This function inserts an element at the position pointed to by pos.
             * @param pos The position to insert the element at.
             * @param val The value to insert.
            */
            iterator insert(const_iterator pos, const_reference val)
            {
                difference_type t = pos - this->cbegin();
                if (_numberOfElements == _capacity)
                    _realloc_create_insert_space(t, t + 1, _numberOfElements, _get_new_capacity());
                else
                    move_backward(_internalBuffer + t, _internalBuffer + _numberOfElements, _internalBuffer + _numberOfElements + 1);

                _numberOfElements++;
                
                *(_internalBuffer + t) = val;
                return iterator(_internalBuffer + t);
            }
            /**
             * This function inserts the elements in the range [start, end) to the position pointed 
             * to by pos.
             * @param pos The position to insert the elements at.
             * @param start The start of the sequence of elements to insert.
             * @param end The end of the sequence of elements to insert.
            */
            template <class InputIterator>
            iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        #if __cplusplus > 201703L
            requires input_iterator<InputIterator>
        #endif
            {
                const difference_type dist = std_copy::distance(first, last);
                if (dist == 0)
                    return pos;
                _numberOfElements += dist;
                difference_type addToGetPos = pos - this->cbegin();
                
                if (_numberOfElements > _capacity)
                    _realloc_create_insert_space(addToGetPos, addToGetPos + dist, _numberOfElements - dist, 1ULL << _power_of_smallest_power_of_two_greater_than(_numberOfElements));
                else
                    move_backward(_internalBuffer + addToGetPos, _internalBuffer + _numberOfElements - dist, _internalBuffer + _numberOfElements);

                while (first != last)
                    _internalBuffer[addToGetPos++] = *first++;

                return iterator(_internalBuffer + addToGetPos);
            }
            /**
             * This function erases the elements in the range [index1, index2). Note that index1 and 
             * index2 are integers. 
             * This function is new.
             * @param index1 The start of the block to erase.
             * @param index2 The end of the block to erase.
            */
            _vector_type& erase(size_type index1, size_type index2)
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

                move(_internalBuffer + index2, _internalBuffer + _numberOfElements, _internalBuffer + index1);
                destroy(_internalBuffer + _numberOfElements - (index2 - index1), _internalBuffer + _numberOfElements);
                _numberOfElements -= index2 - index1;
                return *this;
            }
            /**
             * This function erases the elements in the range [start, end). Note that start and 
             * end are iterators.
             * @param first The start of the block to erase.
             * @param last The end of the block to erase.
            */
            _vector_type& erase(const_iterator first, const_iterator last)
            {
                auto distF = first - cbegin();
                auto distL = last - cbegin();
                move(_internalBuffer + distL, _internalBuffer + _numberOfElements, _internalBuffer + distF);
                destroy(_internalBuffer + _numberOfElements - (distL - distF), _internalBuffer + _numberOfElements);
                _numberOfElements -= (distL - distF);
                return *this;
            }
            /**
             * This function erases the element pointed to by pos.
             * @param pos The iterator pointing to the element to be erased.
            */
            _vector_type& erase(const_iterator pos)
            {
                auto dist = pos - cbegin();
                move(_internalBuffer + dist + 1, _internalBuffer + _numberOfElements, _internalBuffer + dist);
                this->pop_back();
                return *this;
            }
            /**
             * This function checks for whether the vector contains an 
             * element. This function is new.
             * @param elem The element to check for.
            */
            bool contains(const_reference elem) const noexcept
            {
                return this->count(elem) != 0;
            }
            /**
             * This function returns an iterator to the first occurrence 
             * of an element. If the element doesn't exist, the function 
             * returns end().
             * @param elem The element to find.
            */
            iterator find(const_reference elem) const noexcept
            {
                return find(_internalBuffer, _internalBuffer + _numberOfElements, elem);
            }
            /**
             * This function finds how many occurrences of an element exist 
             * inside the vector.
             * @param elem The element of which to count the number of occurrences.
            */
            size_type count(const_reference elem) const noexcept
            {
                return count(_internalBuffer, _internalBuffer + _numberOfElements, elem);
            }
            /**
             * This function swaps the contents of *this and s.
             * @param s The vector to swap the contents with.
            */
            void swap(_vector_type& s)
            {
                _vector_type temp(*this);
                this->assign(move(s));
                s.assign(move(temp));

                std_copy::swap(_numberOfElements, s._numberOfElements);
                std_copy::swap(_capacity, s._capacity);
            }
    };
    //Overloaded == operator
    template <class T, class Alloc = allocator<T>>
    bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
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
    template <class T, class Alloc = allocator<T>>
    void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
    {
        lhs.swap(rhs);
    }
    /**
     * Erases all the values that compares equal to val.
     * @param vec The vector from which the values are erased.
     * @param val The value to erase.
    */
    template <class T, class Alloc = allocator<T>>
    std::size_t erase(vector<T, Alloc>& vec, const T& val)
    {
        auto it = remove(vec.begin(), vec.end(), val);
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
    template <class T, class Alloc = allocator<T>, class Function>
    std::size_t erase_if(vector<T, Alloc>& vec, Function func)
    {
        auto it = remove_if(vec.begin(), vec.end(), func);
        auto dist = std_copy::distance(it, vec.end());
        vec.erase(it, vec.end());
        return dist;
    }
    /**
     * Gets the Nth element from vec. N is a template parameter.
     * @param vec The vector from which to get the element.
    */
    template <std::size_t N, class T, class Alloc>
    T&& get(vector<T, Alloc>& vec)
    {
        return move(vec[N]);
    }
    /**
     * Gets the Nth element from vec. N is a template parameter.
     * @param vec The vector from which to get the element.
    */
    template <std::size_t N, class T, class Alloc>
    T& get(vector<T, Alloc>& vec)
    {
        return vec[N];
    }
    /**
     * Returns an iterator to the beginning of a std_copy::vector. Equivalent 
     * to vec.begin().
     * @param vec The vector.
    */
    template <class T, class Alloc>
    auto begin(const vector<T, Alloc>& vec) -> decltype(vec.begin())
    {
        return vec.begin();
    }
    /**
     * Returns an iterator to the end of a std_copy::vector. Equivalent 
     * to vec.end().
     * @param vec The vector.
    */
    template <class T, class Alloc>
    auto end(const vector<T, Alloc>& vec) -> decltype(vec.end())
    {
        return vec.end();
    }
}

#endif /* _STD_COPY_VECTOR */