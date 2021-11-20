#ifndef _STD_COPY_UNINITIALIZED_ALGO
#define _STD_COPY_UNINITIALIZED_ALGO

#include "iterator_traits.hpp"
#include "move.hpp"

namespace std_copy
{
    /**
     * Copies the range [first, last) to the uninitialized range starting at result_first.
     * @param first An iterator to the start of the range to copy.
     * @param last An iterator to the end of the range to copy.
     * @param result_first An iterator to the start of the range to copy to.
    */
    template <class InputIt, class ForwardIt>
    ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt result_first)
    {
        using T = typename iterator_traits<ForwardIt>::value_type;
        ForwardIt temp = result_first;
        try
        {
            while (first != last)
            {
                ::new (const_cast<void*>(static_cast<const volatile void*>(addressof(*result_first)))) T(*first);
                first++;
                result_first++;
            }
        }
        catch(...)
        {
            while (temp != result_first)
            {
                temp->~T();
                temp++;
            }
            throw;
        }
        return result_first;
    }
    /**
     * Copies the first n elements starting from first to the uninitialized range starting at result_first.
     * @param first An iterator to the start of the range to copy.
     * @param n The number of elements after first to copy.
     * @param result_first An iterator to the start of the range to copy to.
    */
    template <class InputIt, class Size, class ForwardIt>
    ForwardIt uninitialized_copy_n(InputIt first, Size n, ForwardIt result_first)
        requires is_integral_v<Size>
    {
        using T = typename iterator_traits<ForwardIt>::value_type;
        ForwardIt temp = result_first;
        try
        {
            while (n > 0)
            {
                ::new (const_cast<void*>(static_cast<const volatile void*>(addressof(*result_first)))) T(*first);
                first++;
                result_first++;
                n--;
            }
        }
        catch(...)
        {
            while (temp != result_first)
            {
                temp->~T();
                temp++;
            }
            throw;
        }
    }
    /**
     * Fills the uninitialized range [first, last) with val.
     * @param first An iterator to the start of the uninitialized range.
     * @param last An iterator to the end of the uninitialized range.
     * @param val The value used to fill the uninitialized range.
    */
    template <class InputIt, class T>
    void uninitialized_fill(InputIt first, InputIt last, const T& val)
    {
        using T = typename iterator_traits<InputIt>::value_type;
        InputIt temp = first;
        try
        {
            while (first != last)
            {
                ::new (const_cast<void*>(static_cast<const volatile void*>(addressof(*first)))) T(val);
                first++;
            }
        }
        catch(...)
        {
            while (temp != first)
            {
                temp->~T();
                temp++;
            }
            throw;
        }
    }
    /**
     * Fills the first n elements of the uninitialized range starting at first with val.
     * @param first An iterator to the start of the uninitialized range.
     * @param n The number of elements to assign.
     * @param val The value used to fill the uninitialized range.
    */
    template <class InputIt, class Size, class T>
    void uninitiialized_fill_n(InputIt first, Size n, const T& val)
        requires is_integral_v<Size>
    {
        using T = typename iterator_traits<InputIT>::value_type;
        InputIt temp = first;
        try
        {
            while (n > 0)
            {
                ::new(const_cast<void*>(static_cast<const volatile void*>(addressof(*first)))) T(val);
                first++;
                n--;
            }
        }
        catch(...)
        {
            while (temp != first)
            {
                temp->~T();
                temp++;
            }
            throw;
        }
    }
}

#endif /* _STD_COPY_UNINITIALIZED_ALGO */