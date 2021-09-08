#include "iterator.hpp"

#ifndef _STD_COPY_ALGORITHM
#define _STD_COPY_ALGORITHM

namespace std_copy {
    /**
     * This function counts how many elements with the same value as 
     * val exist between first and last.
     * @param first The initial position of the sequence of elements.
     * @param last The final position of the sequence of elements.
     * @param val The value for which to compare against.
    */
    template <class InputIt, class T>
    long long int count(InputIt first, InputIt last, const T& val) {
        long long int c = 0;
        while (first != last) {
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
    template <class InputIt, class Function>
    long long int count_if(InputIt first, InputIt last, Function func) {
        long long int c = 0;
        while (first != last) {
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
    template <class InputIt, class T>
    InputIt find(InputIt first, InputIt last, const T& val) {
        while (first != last) {
            if (*first == val)
                return first;

            first++;
        }
        return last;
    }
    /**
     * This function returns an iterator to the first element in the range 
     * [first, last) for which func evaluates to true.
     * exist between first and last.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to "test" the elements.
    */
    template <class InputIt, class Function>
    InputIt find_if(InputIt first, InputIt last, Function func) {
        while (first != last) {
            if (func(*first))
                return first;
            
            first++;
        }
        return last;
    }
    /**
     * This function assigns val to all the element in the range [first, last).
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value that each element gets assigned to in the range [first, last).
    */
    template <class InputIt, class T>
    void fill(InputIt first, InputIt last, const T& val) {
        while (first != last) {
            *first = val;
            first++;
        }
    }
    /**
     * This function assigns val to all the element at most n after first.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param n The number of elements after first to assign.
     * @param val The value that each element gets assigned to.
    */
    template <class InputIt, class Size,  class T>
    void fill_n(InputIt first, Size n, const T& val) {
        for (int i = 0; i < n; i++) {
            *first = val;
            first++;
        }
    }
    /**
     * This function copies the elements in the range [first, last) to result.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result The start of where to copy the elements to.
    */
    template <class InputIt, class OutputIt>
    OutputIt copy(InputIt first, InputIt last, OutputIt result) {
        while (first != last) {
            *result = *first;
            first++;
            result++;
        }
        return result;
    }
    /**
     * This function copies the first n elements starting from first to result.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param n The number of elements after first to assign.
     * @param result The start of where to copy the elements to.
    */
    template <class InputIt, class Size, class OutputIt>
    OutputIt copy_n(InputIt first, Size n, OutputIt result) {
        for (int i = 0; i < n; i++) {
            *result = *first;
            first++;
            result++;
        }
        return result;
    }
    /**
     * This function copies the elements in the range [first, last) for which func 
     * evaluates to true.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result The start of where to copy the elements to.
     * @param func The function which accepts an element as argument and returns either true 
     * and false. The element is copied if true is returned.
    */
    template <class InputIt, class OutputIt, class Function>
    OutputIt copy_if(InputIt first, InputIt last, OutputIt result, Function func) {
        while (first != last) {
            if (func(*first)) {
                *result = *first;
                result++;
            }
            first++;
        }
        return result;
    }
    /**
     * This function assigns the elements in the range [first, last) to the results 
     * of a generator function.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param gen The generator function.
    */
    template <class InputIt, class Generator>
    void generate(InputIt first, InputIt last, Generator gen) {
        while (first != last) {
            *first = gen();
            first++;
        }
    }
    /**
     * This function returns true if all elements in the range [first, last) 
     * evaluate to true when passed to func.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to test all the elements.
    */
    template <class InputIt, class Function>
    bool all_of(InputIt first, InputIt last, Function func) {
        while (first != last) {
            if (!func(*first)) {
                return false;
            }
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
    template <class InputIt, class Function>
    bool any_of(InputIt first, InputIt last, Function func) {
        while (first != last) {
            if (func(*first)) {
                return true;
            }
            first++;
        }
        return false;
    }
    /**
     * This function compares all the elements in the range [first1, last1) and the 
     * start of first2.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 The start of the second sequence of elements.
    */
    template <class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
        while (first1 != last1) {
            if (*first1 != *first2) {
                return false;
            }
            first1++;
            first2++;
        }
        return true;
    }
    /**
     * This function returns an iterator to the first element in the range [first, second) 
     * that doesn't compare less to val.
     * @param first An iterator to the initial position of the first sequence of elements.
     * @param last An iterator to the final position of the first sequence of elements.
     * @param val The value that the elements get compared to.
    */
    template <class InputIt, class T>
    InputIt lower_bound(InputIt first, InputIt last, const T& val) {
        unsigned long long count, half;
        count = distance(first, last);
        InputIt curr_elem;
        while (count > 0) {
            half = count / 2;
            curr_elem = first + half;
            if (*curr_elem < val) {
                first = curr_elem + 1;
                count -= half + 1;
            }
            else {
                count = half;
            }
        }
        return first;
    }
}

#endif /* _STD_COPY_ALGORITHM */