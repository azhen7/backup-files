#include "pair.hpp"

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
     * This function assigns the first n elements starting from first to the return values
     * from gen.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param n The number of elements to assign.
     * @param gen The generator function.
    */
    template <class InputIt, class Size, class Generator>
    void generate_n(InputIt first, Size n, Generator gen) {
        for (int i = 0; i < n; i++) {
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
     * start of first2. This function invokes operator!=.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
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
     * This function compares all the elements in the range [first1, last1) and the 
     * start of first2. This function invokes a provided function which is used to 
     * compare the elements.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
    */
    template <class InputIt1, class InputIt2, class Compare>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, Compare pred) {
        while (first1 != last1) {
            if (!pred(*first1, *first2)) {
                return false;
            }
            first1++;
            first2++;
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
    /**
     * This function returns an iterator to the first element in the range [first, second) 
     * that doesn't compare less to val. This function uses a provided function to compare 
     * the values.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value that the elements get compared to.
     * @param comp The function used to compare the values.
    */
    template <class InputIt, class T, class Compare>
    InputIt lower_bound(InputIt first, InputIt last, const T& val, Compare comp) {
        unsigned long long count, half;
        count = distance(first, last);
        InputIt curr_elem;
        while (count > 0) {
            half = count / 2;
            curr_elem = first + half;
            if (comp(*curr_elem, val)) {
                first = curr_elem + 1;
                count -= half + 1;
            }
            else {
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
    template <class InputIt, class T>
    InputIt upper_bound(InputIt first, InputIt last, const T& val) {
        unsigned long long count, half;
        count = distance(first, last);
        InputIt curr_elem;
        while (count > 0) {
            half = count / 2;
            curr_elem = first + half;
            if (!(val < *curr_elem)) {
                first = curr_elem + 1;
                count -= half + 1;
            }
            else {
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
    template <class InputIt, class T, class Compare>
    InputIt upper_bound(InputIt first, InputIt last, const T& val, Compare comp) {
        unsigned long long count, half;
        count = distance(first, last);
        InputIt curr_elem;
        while (count > 0) {
            half = count / 2;
            curr_elem = first + half;
            if (!comp(val, *curr_elem)) {
                first = curr_elem + 1;
                count -= half + 1;
            }
            else {
                count = half;
            }
        }
        return first;
    }
    /**
     * This function returns the larger element of two elements. This function invokes 
     * operator<.
     * @param a The first element.
     * @param b The second element.
    */
    template <class T>
    const T& max(const T& a, const T& b) {
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
    const T& max(const T& a, const T& b, Compare comp) {
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
    const T& min(const T& a, const T& b) {
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
    const T& min(const T& a, const T& b, Compare comp) {
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
    template <class InputIt>
    InputIt max_element(InputIt first, InputIt second) {
        InputIt largest = first;

        while (first != second) {
            if (*largest < *first) {
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
    template <class InputIt, class Compare>
    InputIt max_element(InputIt first, InputIt second, Compare comp) {
        InputIt largest = first;

        while (first != second) {
            if (comp(*largest, *first)) {
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
    template <class InputIt>
    InputIt min_element(InputIt first, InputIt second) {
        InputIt smallest = first;

        while (first != second) {
            if (*first < *smallest) {
                smallest = first;
            }
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
    template <class InputIt, class Compare>
    InputIt min_element(InputIt first, InputIt second, Compare comp) {
        InputIt smallest = first;

        while (first != second) {
            if (comp(*first, *smallest)) {
                smallest = first;
            }
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
    pair<T, T> minmax(const T& a, const T& b) {
        if (a < b)
            return make_pair(a, b);
        return make_pair(b, a);
    }
    /**
     * This function returns a pair with first as an iterator pointing to the smallest element in 
     * the range [first, second), and second as an iterator pointing to the largest element.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
    */
    template <class InputIt>
    pair<InputIt, InputIt> minmax_element(InputIt first, InputIt second) {
        InputIt largest = max_element(first, second);
        InputIt smallest = min_element(first, second);
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
    template <class InputIt1, class InputIt2>
    pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
        while (first1 != last1 && *first1 == *first2) {
            first1++;
        }
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
    template <class InputIt1, class InputIt2, class Compare>
    pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, Compare pred) {
        while (first1 != last1 && pred(*first1, *first2)) {
            first1++;
        }
        return make_pair(first1, first2);
    }
    /**
     * This function finds the first occurence of the sequence of elements in the range [first2, last2) 
     * in the sequence of elements in the range [first1, last1) and returns an iterator to the first 
     * element.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param last2 An iterator to the final position of the second sequence of elements.
    */
    template <class InputIt1, class InputIt2>
    InputIt1 search(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
        while (first1 != last1) {
            InputIt2 it2 = first2;
            InputIt1 it1 = first1;
            while (*it1 == *it2) {
                it1++;
                it2++;
                if (it2 == last2) {
                    return first1;
                }
                if (it1 == last1) {
                    return last1;
                }
            }
            first1++;
        }
        return last1;
    }
    /**
     * This function returns an iterator to the first element in the range [first1, last1) that matches any of 
     * the elements in the range [first2, last2).
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param last2 An iterator to the final position of the second sequence of elements.
    */
    template <class InputIt1, class InputIt2>
    InputIt1 find_first_of(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
        while (first1 != last1) {
            for (InputIt2 it = first2; it != last2; it++) {
                if (*it == *first1) {
                    return first1;
                }
            }
        }
        return last1;
    }
    /**
     * This function returns an iterator to the last element in the range [first1, last1) that matches any of 
     * the elements in the range [first2, last2).
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param last2 An iterator to the final position of the second sequence of elements.
    */
    template <class InputIt1, class InputIt2>
    InputIt1 find_first_of(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
        if (first1 == last1)
            return last1;
            
        InputIt1 curr_elem_reverse = last1;
        while (curr_elem_reverse != first1) {
            for (InputIt2 it = first2; it != last2; it++) {
                if (*curr_elem_reverse == *it) {
                    return curr_elem_reverse;
                }
            }
        }
        for (InputIt2 it = first2; it != last2; it++) {
            if (*first1 == *it) {
                return first1;
            }
        }
        return last1;
    }
}

#endif /* _STD_COPY_ALGORITHM */