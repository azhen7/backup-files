#ifndef _STD_COPY_UNINITIALIZED_ALGO
#define _STD_COPY_UNINITIALIZED_ALGO

#include "iterator_traits.hpp"
#include "move.hpp"
#include "concepts.hpp"
#include "construct_destroy.hpp"

#define _uninitialized_algo_construct_obj(type, where, val) \
    (::new (const_cast<void*>(static_cast<const volatile void*>(addressof(where)))) type(val))

namespace std_copy
{
    /**
     * Copies the range [first, last) to the uninitialized range starting at result_first.
     * @param first An iterator to the start of the range to copy.
     * @param last An iterator to the end of the range to copy.
     * @param result_first An iterator to the start of the range to copy to.
    */
    template <class InputIterator, class ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result_first)
#if __cplusplus > 201703L
    requires _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>
    && _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<ForwardIterator>
#endif
    {
        using T = typename iterator_traits<ForwardIterator>::value_type;
        ForwardIterator temp = result_first;
        try
        {
            while (first != last)
            {
                _uninitialized_algo_construct_obj(T, *result_first, move(*first));
                first++;
                result_first++;
            }
        }
        catch(...)
        {
            destroy(temp, result_first);
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
    template <class InputIterator, class Size, class ForwardIterator>
    ForwardIterator uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result_first)
#if __cplusplus > 201703L
    requires integral<Size>
    && _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>
    && _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<ForwardIterator>
#endif
    {
        using T = typename iterator_traits<ForwardIterator>::value_type;
        ForwardIterator temp = result_first;
        try
        {
            while (n > 0)
            {
                _uninitialized_algo_construct_obj(T, *result_first, move(*first));
                first++;
                result_first++;
                n--;
            }
        }
        catch(...)
        {
            destroy(temp, result_first);
            throw;
        }
    }
    /**
     * Fills the uninitialized range [first, last) with val.
     * @param first An iterator to the start of the uninitialized range.
     * @param last An iterator to the end of the uninitialized range.
     * @param val The value used to fill the uninitialized range.
    */
    template <class InputIterator, class T>
    void uninitialized_fill(InputIterator first, InputIterator last, const T& val)
#if __cplusplus > 201703L
    requires _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>
#endif
    {
        using Type = typename iterator_traits<InputIterator>::value_type;
        InputIterator temp = first;
        try
        {
            while (first != last)
            {
                _uninitialized_algo_construct_obj(Type, *first, val);
                first++;
            }
        }
        catch(...)
        {
            destroy(temp, first);
            throw;
        }
    }
    /**
     * Fills the first n elements of the uninitialized range starting at first with val.
     * @param first An iterator to the start of the uninitialized range.
     * @param n The number of elements to assign.
     * @param val The value used to fill the uninitialized range.
    */
    template <class InputIterator, class Size, class T>
    void uninitiialized_fill_n(InputIterator first, Size n, const T& val)
#if __cplusplus > 201703L
    requires integral<Size>
    && _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>
#endif
    {
        using Type = typename iterator_traits<InputIterator>::value_type;
        InputIterator temp = first;
        try
        {
            while (n > 0)
            {
                _uninitialized_algo_construct_obj(Type, *first, val);
                first++;
                n--;
            }
        }
        catch(...)
        {
            destroy(temp, first);
            throw;
        }
    }
    /**
     * Moves the range [first, last) to the uninitialized range starting at result_first.
     * @param first An iterator to the start of the range to move.
     * @param last An iterator to the end of the range to move.
     * @param result_first An iterator to the start of the range to move to.
    */
    template <class InputIterator, class ForwardIterator>
    ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator result_first)
#if __cplusplus > 201703L
    requires _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>
    && _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<ForwardIterator>
#endif
    {
        using T = typename iterator_traits<ForwardIterator>::value_type;
        ForwardIterator temp = result_first;
        try
        {
            while (first != last)
            {
                _uninitialized_algo_construct_obj(T, *result_first, move(*first));
                first++;
                result_first++;
            }
        }
        catch(...)
        {
            destroy(temp, result_first);
            throw;
        }
        return result_first;
    }
    /**
     * Moves the first n elements starting from first to the uninitialized range starting at result_first.
     * @param first An iterator to the start of the range to move.
     * @param n The number of elements after first to move.
     * @param result_first An iterator to the start of the range to move to.
    */
    template <class InputIterator, class Size, class ForwardIterator>
    ForwardIterator uninitialized_move_n(InputIterator first, Size n, ForwardIterator result_first)
#if __cplusplus > 201703L
    requires integral<Size> && _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>
    && _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<ForwardIterator>
#endif
    {
        using T = typename iterator_traits<ForwardIterator>::value_type;
        ForwardIterator temp = result_first;
        try
        {
            while (n > 0)
            {
                _uninitialized_algo_construct_obj(T, *result_first, move(*first));
                first++;
                result_first++;
                n--;
            }
        }
        catch(...)
        {
            destroy(temp, result_first);
            throw;
        }
    }
    /**
     * Fills the uninitialized range [first, last) with constructed elements of T.
     * @param first An iterator to the start of the uninitialized range.
     * @param last An iterator to the end of the uninitialized range.
    */
    template <class InputIterator>
    void uninitialized_default_constructed(InputIterator first, InputIterator last)
#if __cplusplus > 201703L
    requires _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>
#endif
    {
        using T = typename iterator_traits<InputIterator>::value_type;
        InputIterator temp = first;
        try
        {
            while (first != last)
            {
                ::new(const_cast<void*>(static_cast<const volatile void*>(*first))) T;
                first++;
            }
        }
        catch(...)
        {
            destroy(temp, first);
            throw;
        }
    }
    /**
     * Fills the first n elements of the uninitialized range starting at first with constructed elements of T.
     * @param first An iterator to the start of the uninitialized range.
     * @param n The number of elements to assign.
    */
    template <class InputIterator, class Size>
    void uninitialized_default_constructed_n(InputIterator first, Size n)
#if __cplusplus > 201703L
    requires integral<Size> && _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>
#endif
    {
        using T = typename iterator_traits<InputIterator>::value_type;
        InputIterator temp = first;
        try
        {
            while (n > 0)
            {
                ::new(const_cast<void*>(static_cast<const volatile void*>(*first))) T;
                first++;
                n--;
            }
        }
        catch(...)
        {
            destroy(temp, first);
            throw;
        }
    }
    /**
     * Fills the uninitialized range [first, last) with default initialized values.
     * @param first An iterator to the start of the uninitialized range.
     * @param last An iterator to the end of the uninitialized range.
    */
    template <class InputIterator, class T>
    void uninitialized_value_construct(InputIterator first, InputIterator last)
#if __cplusplus > 201703L
    requires _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>
#endif
    {
        using Type = typename iterator_traits<InputIterator>::value_type;
        InputIterator temp = first;
        try
        {
            while (first != last)
            {
                _uninitialized_algo_construct_obj(Type, *first, );
                first++;
            }
        }
        catch(...)
        {
            destroy(temp, first);
            throw;
        }
    }
    /**
     * Fills the first n elements of the uninitialized range starting at first with default initialized values.
     * @param first An iterator to the start of the uninitialized range.
     * @param n The number of elements to assign.
    */
    template <class InputIterator, class Size, class aT>
    void uninitialized_value_construct_n(InputIterator first, Size n)
#if __cplusplus > 201703L
    requires integral<Size>
    && _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIterator>
#endif
    {
        using T = typename iterator_traits<InputIterator>::value_type;
        InputIterator temp = first;
        try
        {
            while (n > 0)
            {
                _uninitialized_algo_construct_obj(T, *first, );
                first++;
                n--;
            }
        }
        catch(...)
        {
            destroy(temp, first);
            throw; 
        }
    }
}

#endif /* _STD_COPY_UNINITIALIZED_ALGO */