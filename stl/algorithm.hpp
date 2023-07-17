#ifndef _STD_COPY_ALGORITHM
#define _STD_COPY_ALGORITHM

#include "utility.hpp"
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "concepts.hpp"

#include <cstdint>

#if __cplusplus > 201703L
namespace _std_copy_hidden
{
    namespace _std_copy_algorithm
    {
        //Checks if operator< can be invoked two objects of type T 
        template <class T>
        concept _is_less_operator_invokable =
        requires(T a, T b)
        {
            {a < b} -> std_copy::same_as<bool>;
        };
    }
}
#endif

namespace std_copy
{
    /**
     * This function counts how many elements with the same value as 
     * val exist between first and last.
     * @param first The initial position of the sequence of elements.
     * @param last The final position of the sequence of elements.
     * @param val The value for which to compare against.
    */
    template <class InputIterator, class T>
    std::size_t count(InputIterator first, InputIterator last, const T& val)
#if __cplusplus > 201703
    requires input_iterator<InputIterator>
#endif
    {
        std::size_t c = 0;
        while (first != last)
        {
            if (*first == val)
                c++;
            
            first++;
        }
        return c;
    }
    /**
     * This function returns the number of elements in the range [first, last) for which 
     * func returns true.
     * exist between first and last.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to "test" the elements.
    */
    template <class InputIterator, class Function>
    std::size_t count_if(InputIterator first, InputIterator last, Function func)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        std::size_t c = 0;
        while (first != last)
        {
            if (func(*first))
                c++;
            
            first++;
        }
        return c;
    }
    /**
     * This function returns an iterator to the first element in the 
     * range [first, last) that is equal to val.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value used to compare against the current element.
    */
    template <class InputIterator, class T>
    InputIterator find(InputIterator first, InputIterator last, const T& val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        while (*first != val && ++first != last);
        return first;
    }
    /**
     * This function returns an iterator to the first element in the range [first, last) for 
     * which func evaluates to true.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to "test" the elements.
    */
    template <class InputIterator, class Function>
    InputIterator find_if(InputIterator first, InputIterator last, Function func)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        while (!func(*first) && ++first != last);
        return first;
    }
    /**
     * This function returns an iterator to the first element in the range [first, last) for 
     * which func evaluates to false.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to "test" the elements.
    */
    template <class InputIterator, class Function>
    InputIterator find_if_not(InputIterator first, InputIterator last, Function func)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        while (func(*first) && ++first != last);
        return first;
    }
    /**
     * This function assigns val to all the element in the range [first, last).
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value that each element gets assigned to in the range [first, last).
    */
    template <class InputIterator, class T>
    void fill(InputIterator first, InputIterator last, const T& val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        while (first != last && *first++ = val);
    }
    /**
     * This function assigns val to all the element at most n after first.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param n The number of elements after first to assign.
     * @param val The value that each element gets assigned to.
    */
    template <class InputIterator, class Size,  class T>
    void fill_n(InputIterator first, Size n, const T& val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && is_integral_v<Size>
#endif
    {
        while (n-- > 0 && *first++ = val);
    }
    /**
     * This function copies the elements in the range [first, last) to result.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the elements 
     * are stored.
    */
    template <class InputIterator, class OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        while (first != last)
            *result++ = *first++;
        return result;
    }
    /**
     * This function copies the first n elements starting from first to result.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param n The number of elements after first to assign.
     * @param result An iterator to the initial position of the range where the elements 
     * are stored.
    */
    template <class InputIterator, class Size, class OutputIterator>
    OutputIterator copy_n(InputIterator first, Size n, OutputIterator result)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator> 
    && output_iterator<OutputIterator>
    && is_integral_v<Size>
#endif
    {
        while (n-- > 0)
            *result++ = *first++;

        return result;
    }
    /**
     * This function copies the elements in the range [first, last) for which func 
     * evaluates to true to result.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the elements 
     * are stored.
     * @param func The function which accepts an element as argument and returns either true 
     * and false. The element is copied if true is returned.
    */
    template <class InputIterator, class OutputIterator, class Function>
    OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator result, Function func)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        while (first != last)
        {
            if (func(*first))
                *result++ = *first;
                
            first++;
        }
        return result;
    }
    /**
     * This function copies the elements in the range [first, second) in backwards 
     * order to the range ending at result.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the elements 
     * are stored.
    */
    template <class InputIterator, class OutputIterator>
    OutputIterator copy_backward(InputIterator first, InputIterator last, OutputIterator result)
#if __cplusplus > 201703L
    requires bidirectional_iterator<InputIterator>
    && bidirectional_iterator<OutputIterator>
#endif
    {
        while (first != last)
            *(--result) = *(--last);

        return result;
    }
    /**
     * This function assigns the elements in the range [first, last) to the results 
     * of a generator function.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param gen The generator function.
    */
    template <class InputIterator, class GeneratorFunc>
    void generate(InputIterator first, InputIterator last, GeneratorFunc gen)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        while (first != last)
            *first++ = gen();
    }
    /**
     * This function assigns the first n elements starting from first to the return values
     * from gen.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param n The number of elements to assign.
     * @param gen The generator function.
    */
    template <class InputIterator, class Size, class Generator>
    void generate_n(InputIterator first, Size n, Generator gen)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && is_integral_v<Size>
#endif
    {
        while (n-- > 0)
            *first++ = gen();
    }
    /**
     * This function returns true if all elements in the range [first, last) 
     * evaluate to true when passed to func.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to test all the elements.
    */
    template <class InputIterator, class Function>
    bool all_of(InputIterator first, InputIterator last, Function func)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        while (first != last)
        {
            if (!func(*first))
                return false;

            first++;
        }
        return true;
    }
    /**
     * This function returns true if any element in the range [first, last) evaluates 
     * to true when passed to func.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to test all the elements.
    */
    template <class InputIterator, class Function>
    bool any_of(InputIterator first, InputIterator last, Function func)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        while (first != last)
        {
            if (func(*first))
                return true;

            first++;
        }
        return false;
    }
    /**
     * This function returns true if all elements in the range [first, last) 
     * evaluate to false when passed to func.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to test all the elements.
    */
    template <class InputIterator, class Function>
    bool none_of(InputIterator first, InputIterator last, Function func)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        return !all_of(first, last, func);
    }
    /**
     * This function compares all the elements in the range [first1, last1) and the 
     * start of first2. This function invokes operator!=.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
    */
    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        while (first1 != last1)
        {
            if (*first1 != *first2)
                return false;
            first1++;
            first2++;
        }
        return true;
    }
    /**
     * This function compares all the elements in the range [first1, last1) and the 
     * start of first2. This function invokes a provided function which is used to 
     * compare the elements.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
    */
    template <class InputIterator1, class InputIterator2, class Compare>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, Compare pred)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        while (first1 != last1)
        {
            if (!pred(*first1++, *first2++))
                return false;
        }
        return true;
    }
    /**
     * This function returns an iterator to the first element in the range [first, second) 
     * that doesn't compare less to val. This function uses operator<.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value that the elements get compared to.
    */
    template <class InputIterator, class T>
    InputIterator lower_bound(InputIterator first, InputIterator last, const T& val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        std::size_t count, half;
        count = std_copy::distance(first, last);
        InputIterator curr_elem;
        while (count > 0)
        {
            half = count / 2;
            curr_elem = next(first, half);
            if (*curr_elem < val)
            {
                first = curr_elem + 1;
                count -= half + 1;
            }
            else
            {
                count = half;
            }
        }
        return first;
    }
    /**
     * This function returns an iterator to the first element in the range [first, second) 
     * that doesn't compare less to val. This function uses a provided function to compare 
     * the values.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value that the elements get compared to.
     * @param comp The function used to compare the values.
    */
    template <class InputIterator, class T, class Compare>
    InputIterator lower_bound(InputIterator first, InputIterator last, const T& val, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        std::size_t count, half;
        count = std_copy::distance(first, last);
        InputIterator curr_elem;
        while (count > 0)
        {
            half = count / 2;
            curr_elem = next(first, half);
            if (comp(*curr_elem, val))
            {
                first = curr_elem + 1;
                count -= half + 1;
            }
            else
            {
                count = half;
            }
        }
        return first;
    }
    /**
     * This function returns an iterator to the first element in the range [first, second) 
     * that compares greater than val. This function uses operator< to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value that the elements get compared to.
    */
    template <class InputIterator, class T>
    InputIterator upper_bound(InputIterator first, InputIterator last, const T& val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        std::size_t count, half;
        count = std_copy::distance(first, last);
        InputIterator curr_elem;
        while (count > 0)
        {
            half = count / 2;
            curr_elem = next(first, half);
            if (!(val < *curr_elem))
            {
                first = curr_elem + 1;
                count -= half + 1;
            }
            else
            {
                count = half;
            }
        }
        return first;
    }
    /**
     * This function returns an iterator to the first element in the range [first, second) 
     * that compares greater than val. This function uses a provided function to compare  
     * the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value that the elements get compared to.
     * @param comp The function that is used to compare the elements.
    */
    template <class InputIterator, class T, class Compare>
    InputIterator upper_bound(InputIterator first, InputIterator last, const T& val, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        std::size_t count, half;
        count = std_copy::distance(first, last);
        InputIterator curr_elem;
        while (count > 0)
        {
            half = count / 2;
            curr_elem = next(first, half);
            if (!comp(val, *curr_elem))
            {
                first = curr_elem + 1;
                count -= half + 1;
            }
            else
            {
                count = half;
            }
        }
        return first;
    }
    /**
     * Returns true if val is in [first, last), and false if not. Invokes operator<
     * to compare the elements.
     * @param first The start of the range to search in.
     * @param last The end of the range to search in.
     * @param val The value to search for.
    */
    template <class InputIterator, class T>
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    bool binary_search(InputIterator first, InputIterator last, const T& val)
    {
        InputIterator lower = lower_bound(first, last, val);
        return (lower != last && !(val < *lower));
    }
    /**
     * This function returns the larger element of two elements. This function invokes 
     * operator<.
     * @param a The first element.
     * @param b The second element.
    */
    template <class T>
#if __cplusplus > 201703
    requires _std_copy_hidden::_std_copy_algorithm::_is_less_operator_invokable<T>
#endif
    const T& max(const T& a, const T& b)
    {
        if (b < a)
            return a;
        return b;
    }
    /**
     * This function returns the larger element of two elements. This function invokes 
     * a provided function.
     * @param a The first element.
     * @param b The second element.
     * @param comp The function that is invoked.
    */
    template <class T, class Compare>
    const T& max(const T& a, const T& b, Compare comp)
    {
        if (comp(b, a))
            return a;
        return b;
    }
    /**
     * This function returns the smaller element of two elements. This function invokes 
     * operator<.
     * @param a The first element.
     * @param b The second element.
    */
    template <class T>
    const T& min(const T& a, const T& b)
#if __cplusplus > 201703L
    requires _std_copy_hidden::_std_copy_algorithm::_is_less_operator_invokable<T>
#endif
    {
        if (a < b)
            return a;
        return b;
    }
    /**
     * This function returns the smaller element of two elements. This function invokes 
     * a provided function.
     * @param a The first element.
     * @param b The second element.
     * @param comp The function that is invoked.
    */
    template <class T, class Compare>
    const T& min(const T& a, const T& b, Compare comp)
    {
        if (comp(a, b))
            return a;
        return b;
    }
    /**
     * This function returns the largest element from the elements in 
     * the range [first, second). This function invokes operator< to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
    */
    template <class InputIterator>
    InputIterator max_element(InputIterator first, InputIterator second)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator largest = first;

        while (first != second)
        {
            if (*largest < *first)
            {
                largest = first;
            }
            first++;
        }

        return largest;
    }
    /**
     * This function returns the largest element from the elements in 
     * the range [first, second). This function invokes a provided function to 
     * compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param comp The function used to compare the element.
    */
    template <class InputIterator, class Compare>
    InputIterator max_element(InputIterator first, InputIterator second, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator largest = first;

        while (first != second)
        {
            if (comp(*largest, *first))
            {
                largest = first;
            }
            first++;
        }

        return largest;
    }
    /**
     * This function returns the smallest element from the elements in 
     * the range [first, second). This function invokes operator< to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
    */
    template <class InputIterator>
    InputIterator min_element(InputIterator first, InputIterator second)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator smallest = first;

        while (first != second)
        {
            if (*first < *smallest)
                smallest = first;

            first++;
        }

        return smallest;
    }
    /**
     * This function returns the smallest element from the elements in 
     * the range [first, second). This function invokes a provided function to compare 
     * the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param comp The function used to compare the elements.
    */
    template <class InputIterator, class Compare>
    InputIterator min_element(InputIterator first, InputIterator second, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator smallest = first;

        while (first != second)
        {
            if (comp(*first, *smallest))
                smallest = first;
            first++;
        }

        return smallest;
    }
    /**
     * This function returns a pair with the smaller element between a and b as first, and 
     * the larger element between a and b as second.
     * @param a The first element.
     * @param b The second element.
    */
    template <class T>
    pair<T, T> minmax(const T& a, const T& b)
#if __cplusplus > 201703L
    requires _std_copy_hidden::_std_copy_algorithm::_is_less_operator_invokable<T>
#endif
    {
        if (a < b)
            return make_pair(a, b);
        return make_pair(b, a);
    }
    /**
     * This function returns a pair with first as an iterator pointing to the smallest element in 
     * the range [first, last), and second as an iterator pointing to the largest element.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
    */
    template <class InputIterator>
    pair<InputIterator, InputIterator> minmax_element(InputIterator first, InputIterator last)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator smallest = first;
        InputIterator largest = first;

        if (first == last || ++first == last)
        {
            return make_pair(smallest, largest);
        }

        while (first != last)
        {
            if (*first < *smallest)
            {
                smallest = first;
            }
            if (*first > *largest)
            {
                largest = first;
            }
            first++;
        }
        return make_pair(smallest, largest);
    }
    /**
     * This function compares the elements in the ranges [first1, last1) and the sequence of elements 
     * starting from first2 and returns a pair of iterators which point to the first elements in each 
     * sequence that aren't equal. This function invokes operator==.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
    */
    template <class InputIterator1, class InputIterator2>
    pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        while (first1 != last1 && *first1 == *first2)
            first1++;

        return make_pair(first1, first2);
    }
    /**
     * This function compares the elements in the ranges [first1, last1) and the sequence of elements 
     * starting from first2 and returns a pair of iterators which point to the first elements in each 
     * sequence that aren't equal. This function invokes a provided function which is used to compare 
     * the elements.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param pred The function used to compare the elements.
    */
    template <class InputIterator1, class InputIterator2, class Compare>
    pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, Compare pred)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        while (first1 != last1 && pred(*first1, *first2))
            first1++;

        return make_pair(first1, first2);
    }
    /**
     * This function returns an iterator to the first element in the range [first1, last1) that matches any of 
     * the elements in the range [first2, last2). This function invokes operator== to compare the elements. 
     * If an element is found, an iterator to it is returned, otherwise, last1 is returned.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param last2 An iterator to the final position of the second sequence of elements.
    */
    template <class InputIterator1, class InputIterator2>
    InputIterator1 find_first_of(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        while (first1 != last1)
        {
            for (InputIterator2 it = first2; it != last2; it++)
            {
                if (*it == *first1)
                    return first1;
            }
        }
        return last1;
    }
     /**
     * This function returns an iterator to the first element in the range [first1, last1) that matches any of 
     * the elements in the range [first2, last2). This function invokes a provided function to compare the 
     * elements. 
     * If an element is found, an iterator to it is returned, otherwise, last1 is returned.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param last2 An iterator to the final position of the second sequence of elements.
     * @param comp The function used to compare the elements.
    */
    template <class InputIterator1, class InputIterator2, class Compare>
    InputIterator1 find_first_of(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        while (first1 != last1)
        {
            for (InputIterator2 it = first2; it != last2; it++)
            {
                if (comp(*it, *first1))
                    return first1;
            }
        }
        return last1;
    }
    /**
     * Finds the sequence [first1, last1) for the last occurence of the subsequence defined by [first2, last2).
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param last2 An iterator to the final position of the second sequence of elements.
    */
    template <class InputIterator1, class InputIterator2>
    InputIterator1 find_end(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        if (first2 == last2)
            return last1;
        last2--;
        while (true)
        {
            last1--;
            InputIterator1 it1 = last1;
            InputIterator2 it2 = last2;

            while (*it1 == *it2)
            {
                it1--;
                it2--;
                if (it2 == first2)
                    return it1;
                if (it1 == first1)
                    return last1;
            }

            if (last1 == first1)
                break;
        }
        return last1;
    }
    /**
     * This function returns an iterator to the last element in the range [first1, last1) that matches any of 
     * the elements in the range [first2, last2). This function invokes a provided function to compare the elements. 
     * If an element is found, an iterator to it is returned, otherwise, last1 is returned.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param last2 An iterator to the final position of the second sequence of elements.
     * @param comp The function used to compare the elements.
    */
    template <class InputIterator1, class InputIterator2, class Compare>
    InputIterator1 find_end(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        if (first2 == last2)
            return last1;
        last2--;
        while (true)
        {
            last1--;
            InputIterator1 it1 = last1;
            InputIterator2 it2 = last2;

            while (comp(*it1,*it2))
            {
                it1--;
                it2--;
                if (it2 == first2)
                    return it1;
                if (it1 == first1)
                    return last1;
            }

            if (last1 == first1)
                break;
        }
        return last1;
    }
    /**
     * This function finds the first occurence of the sequence of elements in the range [first2, last2) 
     * in the sequence of elements in the range [first1, last1) and returns an iterator to the first 
     * element. This function invokes operator==. 
     * If the provided subsequence is not found, last1 is returned.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param last2 An iterator to the final position of the second sequence of elements.
    */
    template <class InputIterator1, class InputIterator2>
    InputIterator1 search(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        while (first1 != last1)
        {
            InputIterator2 it2 = first2;
            InputIterator1 it1 = first1;
            while (*it1 == *it2)
            {
                it1++;
                it2++;
                if (it2 == last2)
                    return first1;
                    
                if (it1 == last1)
                    return last1;
            }
            first1++;
        }
        return last1;
    }
    /**
     * This function finds the first occurence of the sequence of elements in the range [first2, last2) 
     * in the sequence of elements in the range [first1, last1) and returns an iterator to the first 
     * element. This function invokes a provided function to compare the elements. 
     * If the provided subsequence is not found, last1 is returned.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param last2 An iterator to the final position of the second sequence of elements.
     * @param comp The function used to compare the elements.
    */
    template <class InputIterator1, class InputIterator2, class Compare>
    InputIterator1 search(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        while (first1 != last1)
        {
            InputIterator2 it2 = first2;
            InputIterator1 it1 = first1;
            while (comp(*it1, *it2))
            {
                it1++;
                it2++;
                if (it2 == last2)
                    return first1;

                if (it1 == last1)
                    return last1;
            }
            first1++;
        }
        return last1;
    }
    /**
     * This function searches the elements in the range [first, last) for a sequence of count elements that all 
     * are equal to val and returns an iterator to the first of these elements. This function invokes operator== 
     * to compare the elements against val.
     * If count elements (all equal to val) are found consecutively in the provided range, an iterator to the first 
     * element is returned, and otherwise, last is returned.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param count The number of elements that compare equal to val to search for.
     * @param val The value that the elements get compared against.
    */
    template <class InputIterator, class Size, class T>
    InputIterator search_n(InputIterator first, InputIterator last, Size count, const T& val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && is_integral_v<Size>
#endif
    {
        while (first != last)
        {
            Size i = 0;
            InputIterator it = first;
            while (*it == val)
            {
                i++;
                it++;
                if (i == count)
                    return first;
            }
        }
        return last;
    }
    /**
     * This function searches the elements in the range [first, last) for a sequence of count elements that all 
     * are equal to val and returns an iterator to the first of these elements. This function invokes a provided 
     * function to compare the elements against val. 
     * If count elements (all equal to val) are found consecutively in the provided range, an iterator to the first 
     * element is returned, and otherwise, last is returned.
     * @param first An iterator to the initial position of the first sequence of elements.
     * @param last An iterator to the final position of the first sequence of elements.
     * @param count The number of elements that compare equal to val to search for.
     * @param val The value that the elements get compared against.
     * @param comp The function used to compare the elements against val.
    */
    template <class InputIterator, class Size, class T, class Compare>
    InputIterator search_n(InputIterator first, InputIterator last, Size count, const T& val, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && is_integral_v<Size>
#endif
    {
        while (first != last)
        {
            Size i = 0;
            InputIterator it = first;
            while (comp(*it, val))
            {
                i++;
                it++;
                if (i == count)
                    return first;
            }
        }
        return last;
    }
    /**
     * This function returns the bounds of the subrange which includes elements with values all equal to val. 
     * This function invokes operator== to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value of the elements in the subrange to search for.
    */
    template <class InputIterator, class T>
    pair<InputIterator, InputIterator> equal_range(InputIterator first, InputIterator last, const T& val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator start = lower_bound(first, last, val);
        InputIterator end = upper_bound(first, last, val);
        return make_pair(start, end);
    }
    /**
     * This function returns the bounds of the subrange which includes elements with values all equal to val. 
     * This function invokes a provided function to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value of the elements in the subrange to search for.
    */
    template <class InputIterator, class T, class Compare>
    pair<InputIterator, InputIterator> equal_range(InputIterator first, InputIterator last, const T& val, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator start = lower_bound(first, last, val, comp);
        InputIterator end = upper_bound(first, last, val, comp);
        return make_pair(start, end);
    }
    /**
     * This function invokes a provided function on each element in the range [first, last).
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param fn The function that is invoked on the elements.
    */
    template <class InputIterator, class Function>
    Function for_each(InputIterator first, InputIterator last, Function fn)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        while (first != last)
            fn(*first++);
        
        return move(fn);
    }
    /**
     * This function invokes a provided function on the first n elements in the range starting 
     * from first.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param n The number of elements to invoke the function on.
     * @param fn The function that is invoked on the elements.
    */
    template <class InputIterator, class Size, class Function>
    InputIterator for_each_n(InputIterator first, Size n, Function fn)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && is_integral_v<Size>
#endif
    {
        while (n-- > 0)
            fn(*first++);

        return first;
    }
    /**
     * This function invokes a function on the elements in the range [first, last) and stores 
     * the result in the range starting from result.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the function results 
     * are stored.
     * @param fn A function which accepts one argument and returns a result.
    */
    template <class InputIterator, class OutputIterator, class Function>
    OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result, Function fn)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif    
    {
        while (first != last)
            *result++ = fn(*first++);

        return result;
    }
    /**
     * This function invokes a function on the elements in the range [first1, last1) and the range 
     * starting from first2 and stores the result in the range starting from result.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param result An iterator to the initial position of the range where the function results 
     * are stored.
     * @param binary_fn A function which accepts two argument and returns a result.
    */
    template <class InputIterator, class OutputIterator, class Function>
    OutputIterator transform(InputIterator first1, InputIterator last1, InputIterator first2, OutputIterator result, Function binary_fn)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        while (first1 != last1)
            *result++ = binary_fn(*first1++, *first2++);

        return result;
    }
    /**
     * This function removes all the elements in the range [first, second) that compares equal to val.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value used to compare against the elements in the range.
    */
    template <class InputIterator, class T>
    InputIterator remove(InputIterator first, InputIterator last, const T& val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        for (InputIterator it = first; it != last; it++)
        {
            if (*it != val)
                *first++ = move(*it);
        }
        return first;
    }
    /**
     * This function removes all the elements in the range [first, second) for which pred returns true.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param pred The function that is invoked on each element in the range.
    */
    template <class InputIterator, class Function>
    InputIterator remove_if(InputIterator first, InputIterator last, Function pred)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        for (InputIterator it = first; it != last; it++)
        {
            if (!pred(*it))
                *first++ = move(*it);
        }
        return first;
    }
    /**
     * This function copies the elements from the range [first, last) to the range beginning at result 
     * that do not compare equal to val.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the elements are stored.
     * @param val The value which the elements are compared against.
    */
    template <class InputIterator, class OutputIterator, class T>
    OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        while (first != last)
        {
            if (*first != val)
                *result++ = *first;

            first++;
        }
        return result;
    }
    /**
     * This function copies the elements from the range [first, last) to the range beginning at result 
     * for which pred returns false.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the elements are stored.
     * @param pred The function that is invoked on each of the elements.
    */
    template <class InputIterator, class OutputIterator, class Function>
    OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, Function pred)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        while (first != last)
        {
            if (!pred(*first))
                *result++ = *first;

            first++;
        }
        return result;
    }
    /**
     * This function searches the elements in the range [first, last) for two adjacent elements which are 
     * equal. This function invokes operator==.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
    */
    template <class InputIterator>
    InputIterator adjacent_find(InputIterator first, InputIterator last)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator temp = next(first, 1);
        while (*++first != *++temp && first != last);
        return first;
    }
    /**
     * This function searches the elements in the range [first, last) for two adjacent elements which are 
     * equal. This function invokes a provided function to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to compare the elements.
    */
    template <class InputIterator, class Function>
    InputIterator adjacent_find(InputIterator first, InputIterator last, Function func)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator temp = next(first, 1);
        while (!func(*++first, *++temp) && first != last);
        return first;
    }
    /**
     * This function replaces all the elements in the range [first, last) that compare equal to old_val 
     * with new_val. This function invokes operator==.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param old_val The value that gets replaced with new_val.
     * @param new_val The value that replaces old_val. 
    */
    template <class InputIterator, class T>
    void replace(InputIterator first, InputIterator last, const T& old_val, const T& new_val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        while (first != last)
            *first++ = (*first == old_val) ? new_val : *first;
    }
    /**
     * Replaces all the elements in the range [first, last) that compare equal to old_val 
     * with new_val. This function invokes a provided function to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function that determines which elements get replaced with new_val.
     * @param new_val The value that replaces all the elements for which func returns true.
    */
    template <class InputIterator, class Function, class T>
    void replace_if(InputIterator first, InputIterator last, Function func, const T& new_val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        while (first != last)
            *first++ = (func(*first)) ? new_val : *first;
    }
    /**
     * Copies the elements in the range [first, last) to the range starting at result, 
     * replacing all the elements that are equal to old_val with new_val. This function invokes 
     * operator==.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the elements are stored.
     * @param old_val The value that gets replaced with new_val.
     * @param new_val The value that replaces old_val. 
    */
    template <class InputIterator, class OutputIterator, class T>
    OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T& old_val, 
                            const T& new_val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
    && requires(T x, T y) { {x == y} -> same_as<bool>; }
#endif
    {
        while (first != last)
        {
            *result++ = (*first == old_val) ? new_val : *first;
            first++;
        }
        return result;
    }
    /**
     * This function copies the elements in the range [first, last) to the range starting at result, 
     * replacing all the elements for which func returns true with new_val. This function invokes 
     * a provided function to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the elements are stored.
     * @param func The function that determines which elements get replaced with new_val.
     * @param new_val The value that replaces all the elements for which func returns true.
    */
    template <class InputIterator, class OutputIterator, class Function, class T>
    OutputIterator replace_copy_if(InputIterator first, InputIterator last, OutputIterator result, Function func, 
                            const T& new_val)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        while (first != last)
        {
            *result++ = func(*first) ? new_val : *first;
            first++;
        }
        return result;
    }
    /**
     * This function moves the elements from the range [first, last) to the range 
     * starting at result.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the function results 
     * are stored.
    */
    template <class InputIterator, class OutputIterator>
    OutputIterator move(InputIterator first, InputIterator last, OutputIterator result)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        while (first != last)
            *result++ = move(*first++);
        
        return result;
    }
    /**
     * This function moves the first n elements in the range starting at  
     * first to the range starting at result.
     * @param first The start of the sequence to move from.
     * @param n The number of elements to move.
     * @param result The start of the range to move to.
    */
    template <class InputIterator, class Size, class OutputIterator>
    OutputIterator move_n(InputIterator first, Size n, OutputIterator result)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
    && is_integral_v<Size>
#endif
    {
        while (n-- > 0)
            *result++ = move(*first++);

        return result;
    }
    /**
     * This function moves the elements from the range [first, last) to the range 
     * starting at result from the final position to the initial position.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the final position of the range where the function results 
     * are stored.
    */
    template <class InputIterator, class OutputIterator>
    OutputIterator move_backward(InputIterator first, InputIterator last, OutputIterator result)
#if __cplusplus > 201703L
    requires bidirectional_iterator<InputIterator>
    && bidirectional_iterator<OutputIterator>
#endif
    {
        while (first != last)
            *(--result) = move(*(--last));

        return result;
    }
    /**
     * This function shifts the elements in the range [first, last) left by n places.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param n The number of places to shift left by.
    */
    template <class InputIterator>
    InputIterator shift_left(InputIterator first, InputIterator last, std::size_t n = 1)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        if (n == 0 || n > distance(first, last))
            return first;

        InputIterator mid = next(first, n);
        if (mid == last)
            return first;
        return move(move(mid), move(last), move(first));
    }
    /**
     * This function shifts the elements in the range [first, last) right by n places.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param n The number of places to shift right by.
    */
    template <class InputIterator>
    InputIterator shift_right(InputIterator first, InputIterator last, std::size_t n = 1)
#if __cplusplus > 201703L
    requires bidirectional_iterator<InputIterator>
#endif
    {
        if (n == 0 || n > distance(first, last))
            return last;

        InputIterator mid = next(first, n);
        if (mid == first)
            return last;
        return move_backward(move(first), move(mid), move(last));
    }
    /**
     * This function removes consecutive duplicate elements. operator== is invoked
     * to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
    */
    template <class InputIterator>
    InputIterator unique(InputIterator first, InputIterator last)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator result = first;
        while (first != last)
        {
            if (!(*result == *first))
                *(++result) = move(*first);

            first++;
        }
        result++;
        return result;
    }
    /**
     * This function removes consecutive duplicate elements. A user-provided comparator
     * function @p comp is invoked to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param comp The function used to compare the elements.
    */
    template <class InputIterator, class Compare>
    InputIterator unique(InputIterator first, InputIterator last, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
#endif
    {
        InputIterator result = first;
        while (first != last)
        {
            if (!comp(*result, *first))
                *(++result) = move(*first);

            first++;
        }
        result++;
        return result;
    }
    /**
     * This function copies the elements from [first, last) to the range starting at 
     * result, and doesn't copy adjacent duplicate elements. This function invokes
     * operator== to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the function results 
     * are stored.
    */
    template <class InputIterator, class OutputIterator>
    OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        if (first == last) 
            return result;
            
        InputIterator temp = first;
        while (first != last)
        {
            temp++;
            if (!(*temp == *first) || temp == last)
                *result++ = *first;

            first++;
        }
        result++;
        return result;
    }
    /**
     * This function copies the elements from [first, last) to the range starting at 
     * result, and doesn't copy adjacent duplicate elements. This function invokes
     * a provided function to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the function results 
     * are stored.
     * @param comp The function used to compare the elements.
    */
    template <class InputIterator, class OutputIterator, class Compare>
    OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result, Compare comp)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        if (first == last) 
            return result;

        InputIterator temp = first;
        while (first != last)
        {
            temp++;
            if (!comp(*temp, *first) || temp == last)
                *result++ = *first;

            first++;
        }
        result++;
        return result;
    }
    /**
     * This function swaps the values of two iterators.
     * @param a The first iterator.
     * @param b The second iterator.
    */
    template <class InputIterator1, class InputIterator2>
    constexpr void iter_swap(InputIterator1 a, InputIterator2 b)
#if __cplusplus > 201703L
    requires input_iterator<InputIterator1>
    && input_iterator<InputIterator2>
#endif
    {
        std_copy::swap(*a, *b);
    }
    /**
     * This function reverses the order of the values in the range 
     * [first, last).
     * @param first An iterator to the start of the sequence.
     * @param last An iterator to the end of the sequence.
    */
    template <class InputIterator>
    constexpr void reverse(InputIterator first, InputIterator last)
#if __cplusplus > 201703L
    requires bidirectional_iterator<InputIterator>
#endif
    {
        if (first == last) return;
        while (first != last && first != --last)
        {
            iter_swap(first++, last);
        }
    }
    /**
     * This function copies the elements from [first, last) to the 
     * range starting at result in backwards order.
     * @param first An iterator to the start of the sequence.
     * @param last An iterator to the end of the sequence.
     * @param result An iterator to the start of the new sequence.
    */
    template <class InputIterator, class OutputIterator>
    constexpr void reverse_copy(InputIterator first, InputIterator last, OutputIterator result)
#if __cplusplus > 201703L
    requires bidirectional_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        while (last != first)
            *result++ = *(--last);
    }
    /**
     * This function copies the elements from [first, last) to the 
     * range starting at result such that fn returns true for them 
     * in backwards order.
     * @param first An iterator to the start of the sequence.
     * @param last An iterator to the end of the sequence.
     * @param result An iterator to the start of the new sequence.
     * @param fn The function used to determine which elements to copy over.
    */
    template <class InputIterator, class OutputIterator, class Function>
    constexpr void reverse_copy_if(InputIterator first, InputIterator last, OutputIterator result, Function fn)
#if __cplusplus > 201703L
    requires bidirectional_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        last--;
        while (last != first)
        {
            if (fn(*last))
                *result++ = *last;
            last--;
        }
    }
    /**
     * This function moves the elements from [first, last) to the 
     * range starting at result.
     * @param first An iterator to the start of the sequence.
     * @param last An iterator to the end of the sequence.
     * @param result An iterator to the start of the new sequence.
    */
    template <class InputIterator, class OutputIterator>
    constexpr void reverse_move(InputIterator first, InputIterator last, OutputIterator result)
#if __cplusplus > 201703L
    requires bidirectional_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        while (last != first)
            *result++ = move(*(--last));
    }
    /**
     * This function moves the elements from [first, last) to the 
     * range starting at result such that fn returns true for them 
     * in backwards order.
     * @param first An iterator to the start of the sequence.
     * @param last An iterator to the end of the sequence.
     * @param result An iterator to the start of the new sequence.
     * @param fn The function used to determine which elements to copy over.
    */
    template <class InputIterator, class OutputIterator, class Function>
    constexpr void reverse_move_if(InputIterator first, InputIterator last, OutputIterator result, Function fn)
#if __cplusplus > 201703L
    requires bidirectional_iterator<InputIterator>
    && output_iterator<OutputIterator>
#endif
    {
        last--;
        while (last != first)
        {
            if (fn(*last))
                *result++ = move(*last);
            last--;
        }
    }
    /**
     * Rotates the elements in [first, last) left until new_first becomes 
     * the new first element in the range and the last element becomes 
     * new_first - 1.
     * @param first The initial iterator to the beginning of the range.
     * @param new_first The to-be-iterator to the beginning of the range.
     * @param last The initial iterator to the end of the range.
    */
    template <class ForwardIterator>
    constexpr ForwardIterator rotate(ForwardIterator first, ForwardIterator new_first, ForwardIterator last)
    {
        std::ptrdiff_t dist = distance(first, new_first);
        for (std::size_t i = 0; i < dist; i++)
        {
            ForwardIterator temp = last;
            ForwardIterator tempFirst = first;
            typename iterator_traits<ForwardIterator>::value_type firstVal = *first;

            move(++tempFirst, last, first);
            swap(firstVal, *(--temp));
        }
        return next(first, dist);
    }
    /**
     * Swaps two ranges.
     * @param first1 The initial iterator to the beginning of the first range.
     * @param last1 The initial iterator to the end of the first range.
     * @param first2 The initial iterator to the beginning of the second range.
    */
    template <class ForwardIterator1, class ForwardIterator2>
    constexpr ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
    {
        for ( ; first1 != last1; first1++)
            std_copy::iter_swap(first1, first2++);
        return first2;
    }
}

#endif /* _STD_COPY_ALGORITHM */