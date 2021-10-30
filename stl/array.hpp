#ifndef _STD_COPY_ARRAY
#define _STD_COPY_ARRAY

#include <stdexcept>
#include <string>

#include "iterator.hpp"
#include "algorithm.hpp"

namespace std_copy
{
    /**
     * My own implementation of the STL array container, which
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
            typedef iterator<array<T, s>>                           iterator_type;
            
        public:
            //typdefs
            typedef T                                               value_type;
            typedef T*                                              pointer;
            typedef const T*                                        const_pointer;
            typedef T&                                              reference;
            typedef const T&                                        const_reference;
            typedef unsigned long long                              size_type;
            typedef long long                                       difference_type;
            typedef iterator_type                                   iterator;
            typedef const iterator_type                             const_iterator;
            
        private:
            typedef array<T, s>         array_type;

            pointer internalBuffer_;
            size_type numberOfElements_;
            const size_type size_ = s;

        public:
            array()
                : numberOfElements_(0)
            {
                internalBuffer_ = new value_type[s];
            }

            array(const_reference val)
                : numberOfElements_(s)
            {
                internalBuffer_ = new value_type[s];
                std_copy::fill_n(internalBuffer_, size_, val);
            }

            array(const array_type& copy) 
                : numberOfElements_(copy.numberOfElements_)
            {
                internalBuffer_ = new value_type[size_];
                std_copy::copy(copy.internalBuffer_, copy.internalBuffer_ + numberOfElements_, internalBuffer_);
            }

            array(array_type&& copy)
                : numberOfElements_(copy.numberOfElements_)
            {
                internalBuffer_ = copy.internalBuffer_;
            }

            virtual ~array() = default;

            /**
             * Assigns one array to another.
             * @param assign The array to get assigned.
            */
            void operator=(const array_type& assign)
            {
                for (int i = 0; i < size_; i++)
                    internalBuffer_[i] = assign.internalBuffer_[i];
            }
            /**
             * This function fills the array with the
             * designated value.
             * @param val The value used to fill the array.
            */
            void fill(const_reference val)
            {
                std_copy::fill_n(internalBuffer_, size_, val);
            }
            /**
             * This function returns the number of elements
             * in the array. This function is new.
            */
            size_type quantity() const noexcept
            {
                return numberOfElements_;
            }
            /**
             * This function returns the underlying
             * internal buffer of the array.
            */
            pointer data() const noexcept
            {
                return internalBuffer_;
            }
            /**
             * This function returns a boolean, depending
             * on whether the array is empty or not, i.e.,
             * whether there are no elements in the array.
             * This function is new.
            */
            constexpr bool empty()
            {
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
             * This function returns an iterator to the first element 
             * in the array container.
            */
            iterator begin()
            {
                return iterator(internalBuffer_);
            }
            /**
             * This function returns an iterator to the theoretical element 
             * after the last element in the array container.
            */
            const_iterator end()
            {
                return iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * This function returns an const iterator to the first element 
             * in the array container.
            */
            const_iterator cbegin()
            {
                return iterator(internalBuffer_);
            }
            /**
             * This function returns an const iterator to the theoretical element 
             * after the last element in the array container.
            */
            iterator cend()
            {
                return iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * This function returns a reference to 
             * the element at a specified index in 
             * the vector.
             * @param index The index of the element to retrieve.
            */
            reference at(size_type index)
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
            reference operator[](size_type index)
            {
                return internalBuffer_[index];
            }
            /**
             * This function returns a reference to the
             * first element in the array. If the vector
             * is empty, this function throws an exception.
            */
            reference front()
            {
                if (numberOfElements_ == 0)
                {
                    throw std::length_error("Cannot access element in empty array");
                }
                return internalBuffer_[0];
            }
            /**
             * This function returns a reference to the
             * last element in the array. If the vector 
             * is empty, this function throws an exception.
            */
            reference back()
            {
                if (numberOfElements_ == 0)
                {
                    throw std::length_error("Cannot access element in empty array");
                }
                return internalBuffer_[numberOfElements_ - 1];
            }
            /**
             * This function swaps the contents of *this and toSwap.
             * @param toSwap The array to swap the contents with.
            */
            void swap(const array_type& toSwap)
            {
                pointer temp = internalBuffer_;
                internalBuffer_ = toSwap.internalBuffer_;
                toSwap.internalBuffer_ = temp;

                size_type tempNumberOfElems = numberOfElements_;
                numberOfElements_ = toSwap.numberOfElements_;
                toSwap.numberOfElements_ = tempNumberOfElems;
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
        array<T, N> converted;
        for (int i = 0; i < N; i++)
            converted[i] = arr[i];
        return converted;
    }
}

#endif /* _STD_COPY_ARRAY */