#ifndef _STD_COPY_ARRAY
#define _STD_COPY_ARRAY

#include <stdexcept>
#include <string>

#include "iterator_funcs.hpp"
#include "algorithm.hpp"

namespace std_copy
{
    /**
     * An implementation of the STL array container, which
     * is defined in the <array> header.
     * @param T The type of the elements in the array.
     * @param s The size of the array.
     * The array STL container has the same functionality as normal
     * static-sized C arrays, except you can assign one std_copy::array
     * to another, and you can return them from functions. They also
     * come with a lot of helpful functions.
    */
    template <class T, unsigned long long s>
    class array
    {
        private:
            typedef array<T, s>                                     _array_type;
            
        public:
            //typdefs
            typedef T                                                                   value_type;
            typedef T*                                                                  pointer;
            typedef const T*                                                            const_pointer;
            typedef T&                                                                  reference;
            typedef const T&                                                            const_reference;
            typedef unsigned long long                                                  size_type;
            typedef long long                                                           difference_type;
            typedef _std_copy_hidden::_std_copy_stl_containers::_iterator<_array_type>  iterator;
            typedef const iterator                                                      const_iterator;
            
        private:
            T _internalBuffer[s];
            size_type _numberOfElements;
            const size_type _size = s;

        public:
            array() : _numberOfElements(0) {}

            array(const_reference val)
                : _numberOfElements(move(s))
            {
                std_copy::fill_n(_internalBuffer, _size, val);
            }

            array(const _array_type& copy) 
                : _numberOfElements(move(copy._numberOfElements))
            {
                std_copy::move(copy._internalBuffer, copy._internalBuffer + _numberOfElements, _internalBuffer);
            }

            array(_array_type&& copy)
                : _numberOfElements(move(copy._numberOfElements))
            {
                std_copy::move(copy._internalBuffer, copy._internalBuffer + _numberOfElements, _internalBuffer);
            }

            template <size_type Size>
            array(T (&arr)[Size])
                : _numberOfElements(move(Size))
            {
                for (size_type i = 0; i < Size; i++)
                    _internalBuffer[i] = move(arr[i]);
            }

            virtual ~array() = default;

            /**
             * Assigns one array to another.
             * @param assign The array to get assigned.
            */
            void operator=(const _array_type& assign)
            {
                for (int i = 0; i < _size; i++)
                    _internalBuffer[i] = assign._internalBuffer[i];
            }
            /**
             * This function fills the array with the
             * designated value.
             * @param val The value used to fill the array.
            */
            void fill(const_reference val)
            {
                std_copy::fill_n(_internalBuffer, _size, val);
            }
            /**
             * This function returns the number of elements
             * in the array. This function is new.
            */
            size_type quantity() const noexcept
            {
                return _numberOfElements;
            }
            /**
             * This function returns the underlying
             * internal buffer of the array.
            */
            pointer data() const noexcept
            {
                return _internalBuffer;
            }
            /**
             * Returns C-style array used as underlying buffer 
             * of the array.
            */
            pointer c_array() const noexcept
            {
                return _internalBuffer;
            }
            /**
             * This function returns a boolean, depending
             * on whether the array is empty or not, i.e.,
             * whether there are no elements in the array.
             * This function is new.
            */
            bool empty() const noexcept
            {
                return _numberOfElements == 0;
            }
            /**
             * This function returns the size of the
             * array.
            */
            size_type size() const noexcept
            {
                return _size;
            }
            /**
             * This function returns an iterator to the first element 
             * in the array container.
            */
            iterator begin() const noexcept
            {
                return iterator(_internalBuffer);
            }
            /**
             * This function returns an iterator to the theoretical element 
             * after the last element in the array container.
            */
            const_iterator end() const noexcept
            {
                return iterator(_internalBuffer + _numberOfElements);
            }
            /**
             * This function returns an const iterator to the first element 
             * in the array container.
            */
            const_iterator cbegin() const noexcept
            {
                return iterator(_internalBuffer);
            }
            /**
             * This function returns an const iterator to the theoretical element 
             * after the last element in the array container.
            */
            iterator cend() const noexcept
            {
                return iterator(_internalBuffer + _numberOfElements);
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
                    std::string err = "index (which is " + std::to_string(index) + ") >= this->size() (which is " + 
                                    std::to_string(_numberOfElements) + ")";

                    throw std::out_of_range(err);
                }
                return *(_internalBuffer + index);
            }
            /**
             * operator[] is overloaded to provide C-style array
             * indexing.
             * @param index The index of the element to retrieve.
            */
            reference operator[](size_type index) const noexcept
            {
                return _internalBuffer[index];
            }
            /**
             * This function returns a reference to the
             * first element in the array. If the vector
             * is empty, this function throws an exception.
            */
            reference front() const
            {
                if (_numberOfElements == 0)
                    throw std::length_error("Cannot access element in empty array");

                return _internalBuffer[0];
            }
            /**
             * This function returns a reference to the
             * last element in the array. If the vector 
             * is empty, this function throws an exception.
            */
            reference back() const
            {
                if (_numberOfElements == 0)
                    throw std::length_error("Cannot access element in empty array");

                return _internalBuffer[_numberOfElements - 1];
            }
            /**
             * This function swaps the contents of *this and toSwap.
             * @param toSwap The array to swap the contents with.
            */
            void swap(const _array_type& toSwap)
            {
                pointer temp = _internalBuffer;
                _internalBuffer = toSwap._internalBuffer;
                toSwap._internalBuffer = temp;

                size_type tempNumberOfElems = _numberOfElements;
                _numberOfElements = toSwap._numberOfElements;
                toSwap._numberOfElements = tempNumberOfElems;
            }
    };

    /**
     * This function swaps the contents of two arrays.
     * @param lhs The first array.
     * @param rhs The second array.
    */
    template <class T, unsigned long long N>
    void swap(const array<T, N>& lhs, const array<T, N>& rhs)
    {
        lhs.swap(rhs);
    }
    /**
     * This function converts a builtin array to a std::array.
     * @param arr The array to convert.
    */
    template <class T, unsigned long long N>
    constexpr array<T, N> to_array(T (&arr)[N])
    {
        return array<T, N>(arr);
    }
    /**
     * Returns the Nth element of arr. N is a template parameter.
     * @param arr The array from which to get the Nth element.
    */
    template <unsigned long long I, class T, unsigned long long N>
    T&& get(array<T, N>& arr)
    {
        return move(arr[I]);
    }
    /**
     * Returns the Nth element of arr. N is a template parameter.
     * @param arr The array from which to get the Nth element.
    */
    template <unsigned long long I, class T, unsigned long long N>
    T& get(array<T, N>& arr)
    {
        return arr[I];
    }
}

#endif /* _STD_COPY_ARRAY */