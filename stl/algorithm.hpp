#ifndef _STD_COPY_ALGORITHM
#define _STD_COPY_ALGORITHM

#include "utility.hpp"

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
     * This function returns an iterator to the first element in the range [first, last) for 
     * which func evaluates to true.
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
     * This function returns an iterator to the first element in the range [first, last) for 
     * which func evaluates to false.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to "test" the elements.
    */
    template <class InputIt, class Function>
    InputIt find_if_not(InputIt first, InputIt last, Function func) {
        while (first != last) {
            if (!func(*first))
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
     * @param result An iterator to the initial position of the range where the elements 
     * are stored.
    */
    template <class InputIt, class OutputIt>
    OutputIt copy(InputIt first, InputIt last, OutputIt result) {
        while (first != last) {
            *result++ = *first++;
        }
        return result;
    }
    /**
     * This function copies the first n elements starting from first to result.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param n The number of elements after first to assign.
     * @param result An iterator to the initial position of the range where the elements 
     * are stored.
    */
    template <class InputIt, class Size, class OutputIt>
    OutputIt copy_n(InputIt first, Size n, OutputIt result) {
        for (int i = 0; i < n; i++) {
            *result++ = *first++;
        }
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
    template <class InputIt, class OutputIt, class Function>
    OutputIt copy_if(InputIt first, InputIt last, OutputIt result, Function func) {
        while (first != last) {
            if (func(*first)) {
                *result++ = *first;
            }
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
    template <class InputIt, class OutputIt>
    OutputIt copy_backward(InputIt first, InputIt last, OutputIt result) {
        while (first != last) {
            *(--result) = *(--last);
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
     * This function returns true if all elements in the range [first, last) 
     * evaluate to false when passed to func.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to test all the elements.
    */
    template <class InputIt, class Function>
    bool none_of(InputIt first, InputIt last, Function func) {
        return !all_of(first, last, func);
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
     * element. This function invokes operator==. 
     * If the provided subsequence is not found, last1 is returned.
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
    template <class InputIt1, class InputIt2, class Compare>
    InputIt1 search(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
        while (first1 != last1) {
            InputIt2 it2 = first2;
            InputIt1 it1 = first1;
            while (comp(*it1, *it2)) {
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
     * the elements in the range [first2, last2). This function invokes operator== to compare the elements. 
     * If an element is found, an iterator to it is returned, otherwise, last1 is returned.
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
    template <class InputIt1, class InputIt2, class Compare>
    InputIt1 find_first_of(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
        while (first1 != last1) {
            for (InputIt2 it = first2; it != last2; it++) {
                if (comp(*it, *first1)) {
                    return first1;
                }
            }
        }
        return last1;
    }
    /**
     * This function returns an iterator to the last element in the range [first1, last1) that matches any of 
     * the elements in the range [first2, last2). This function invokes operator== to compare the elements. 
     * If an element is found, an iterator to it is returned, otherwise, last1 is returned.
     * @param first1 An iterator to the initial position of the first sequence of elements.
     * @param last1 An iterator to the final position of the first sequence of elements.
     * @param first2 An iterator to the initial position of the second sequence of elements.
     * @param last2 An iterator to the final position of the second sequence of elements.
    */
    template <class InputIt1, class InputIt2>
    InputIt1 find_end(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
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
    template <class InputIt1, class InputIt2, class Compare>
    InputIt1 find_end(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
        if (first1 == last1)
            return last1;

        InputIt1 curr_elem_reverse = last1;
        while (curr_elem_reverse != first1) {
            for (InputIt2 it = first2; it != last2; it++) {
                if (comp(*curr_elem_reverse, *it)) {
                    return curr_elem_reverse;
                }
            }
        }
        for (InputIt2 it = first2; it != last2; it++) {
            if (comp(*first1, *it)) {
                return first1;
            }
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
    template <class InputIt, class Size, class T>
    InputIt search_n(InputIt first, InputIt last, Size count, const T& val) {
        while (first != last) {
            Size i = 0;
            InputIt it = first;
            while (*it == val) {
                i++;
                it++;
                if (i == count) {
                    return first;
                }
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
    template <class InputIt, class Size, class T, class Compare>
    InputIt search_n(InputIt first, InputIt last, Size count, const T& val, Compare comp) {
        while (first != last) {
            Size i = 0;
            InputIt it = first;
            while (comp(*it, val)) {
                i++;
                it++;
                if (i == count) {
                    return first;
                }
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
    template <class InputIt, class T>
    pair<InputIt, InputIt> equal_range(InputIt first, InputIt last, const T& val) {
        InputIt start = lower_bound(first, last, val);
        InputIt end = upper_bound(first, last, val);
        return make_pair<start, end>;
    }
    /**
     * This function returns the bounds of the subrange which includes elements with values all equal to val. 
     * This function invokes a provided function to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value of the elements in the subrange to search for.
    */
    template <class InputIt, class T, class Compare>
    pair<InputIt, InputIt> equal_range(InputIt first, InputIt last, const T& val, Compare comp) {
        InputIt start = lower_bound(first, last, val, comp);
        InputIt end = upper_bound(first, last, val, comp);
        return make_pair<start, end>;
    }
    /**
     * This function invokes a provided function on each element in the range [first, last).
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param fn The function that is invoked on the elements.
    */
    template <class InputIt, class Function>
    Function for_each(InputIt first, InputIt last, Function fn) {
        while (first != last) {
            fn(*first);
            first++;
        }
        return move(fn);
    }
    /**
     * This function invokes a provided function on the first n elements in the range starting 
     * from first.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param n The number of elements to invoke the function on.
     * @param fn The function that is invoked on the elements.
    */
    template <class InputIt, class Size, class Function>
    InputIt for_each_n(InputIt first, Size n, Function fn) {
        for (int i = 0; i < n; i++) {
            fn(*first);
            first++;
        }
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
    template <class InputIt, class OutputIt, class Function>
    OutputIt transform(InputIt first, InputIt last, OutputIt result, Function fn) {
        while (first != last) {
            *result = fn(*first);
            first++;
            result++;
        }
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
    template <class InputIt, class OutputIt, class Function>
    OutputIt transform(InputIt first1, InputIt last1, InputIt first2, OutputIt result, Function binary_fn) {
        while (first1 != last1) {
            *result++ = binary_fn(*first1, *first2);
            first1++;
            first2++;
        }
        return result;
    }
    /**
     * This function removes all the elements in the range [first, second) that compares equal to val.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param val The value used to compare against the elements in the range.
    */
    template <class InputIt, class T>
    InputIt remove(InputIt first, InputIt last, const T& val) {
        for (InputIt it = first; it != last; it++) {
            if (*it != val) {
                *first++ = move(*it);
            }
        }
        return first;
    }
    /**
     * This function removes all the elements in the range [first, second) for which pred returns true.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param pred The function that is invoked on each element in the range.
    */
    template <class InputIt, class Function>
    InputIt remove_if(InputIt first, InputIt last, Function pred) {
        for (InputIt it = first; it != last; it++) {
            if (!pred(*it)) {
                *first++ = move(*it);
            }
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
    template <class InputIt, class OutputIt, class T>
    OutputIt remove_copy(InputIt first, InputIt last, OutputIt result, const T& val) {
        while (first != last) {
            if (*first != val) {
                *result++ = *first;
            }
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
    template <class InputIt, class OutputIt, class Function>
    OutputIt remove_copy_if(InputIt first, InputIt last, OutputIt result, Function pred) {
        while (first != last) {
            if (!pred(*first)) {
                *result++ = *first;
            }
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
    template <class InputIt>
    InputIt adjacent_find(InputIt first, InputIt last) {
        while (first != last) {
            if (*first == *(first + 1)) {
                return first;
            }
            first++;
        }
        return last;
    }
    /**
     * This function searches the elements in the range [first, last) for two adjacent elements which are 
     * equal. This function invokes a provided function to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function used to compare the elements.
    */
    template <class InputIt, class Function>
    InputIt adjacent_find(InputIt first, InputIt last, Function func) {
        while (first != last) {
            if (func(*first, *(first + 1))) {
                return first;
            }
            first++;
        }
        return last;
    }
    /**
     * This function replaces all the elements in the range [first, last) that compare equal to old_val 
     * with new_val. This function invokes operator==.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param old_val The value that gets replaced with new_val.
     * @param new_val The value that replaces old_val. 
    */
    template <class InputIt, class T>
    void replace(InputIt first, InputIt last, const T& old_val, const T& new_val) {
        while (first != last) {
            if (*first == old_val) {
                *first = new_val;
            }
            first++;
        }
    }
    /**
     * This function replaces all the elements in the range [first, last) that compare equal to old_val 
     * with new_val. This function invokes a provided function to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param func The function that determines which elements get replaced with new_val.
     * @param new_val The value that replaces all the elements for which func returns true.
    */
    template <class InputIt, class Function, class T>
    void replace_if(InputIt first, InputIt last, Function func, const T& new_val) {
        while (first != last) {
            if (func(*first)) {
                *first = new_val;
            }
            first++;
        }
    }
    /**
     * This function copies the elements in the range [first, last) to the range starting at result, 
     * replacing all the elements that are equal to old_val with new_val. This function invokes 
     * operator==.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the elements are stored.
     * @param old_val The value that gets replaced with new_val.
     * @param new_val The value that replaces old_val.
    */
    template <class InputIt, class OutputIt, class T>
    OutputIt replace_copy(InputIt first, InputIt last, OutputIt result, const T& old_val, 
                            const T& new_val) 
    {
        while (first != last) {
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
    template <class InputIt, class OutputIt, class Function, class T>
    OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt result, Function func, 
                            const T& new_val) 
    {
        while (first != last) {
            *result++ = func(*first) ? new_val : *first;
            first++;
        }
        return result;
    }
    /**
     * This function shifts the elements in the range [first, last) left by n places.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param n The number of places to shift left by.
    */
    template <class InputIt>
    InputIt shift_left(InputIt first, InputIt last, long long n) {
        if (n == 0 || n > last - first) {
            return first;
        }
        for (int i = 0; i < n; i++) {
            *(first + i + n) = move(*(first + i));
        }
        return first + (last - first - n);
    }
    /**
     * This function shifts the elements in the range [first, last) right by n places.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param n The number of places to shift right by.
    */
    template <class InputIt>
    InputIt shift_right(InputIt first, InputIt last, long long n) {
        if (n == 0 || n > last - first) {
            return first;
        }
        for (int i = n; i >= 0; i--) {
            *(first + n) = move(*(first + (n << 1)));
        }
        return first + n;
    }
    /**
     * This function moves the elements from the range [first, last) to the range 
     * starting at result.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the function results 
     * are stored.
    */
    template <class InputIt, class OutputIt>
    OutputIt move(InputIt first, InputIt last, OutputIt result) {
        while (first != last) {
            *result++ = move(*first++);
        }
        return result;
    }
    /**
     * This function moves the elements from the range [first, last) to the range 
     * starting at result in backwards order.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the function results 
     * are stored.
    */
    template <class InputIt, class OutputIt>
    OutputIt move_backward(InputIt first, InputIt last, OutputIt result) {
        while (first != last) {
            *(--result) = move(*(--last));
        }
        return result;
    }
    /**
     * This function copies the elements from [first, last) to a new range, for which a 
     * past-the-end iterator gets returned. This function invokes operator== to compare the 
     * elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
    */
    template <class InputIt>
    InputIt unique(InputIt first, InputIt last) {
        InputIt result = first;
        while (first != last) {
            if (!(*result == *first) && result != first) {
                *result = move(*first);
                result++;
            }
            first++;
        }
        return ++result;
    }
    /**
     * This function copies the elements from [first, last) to a new range, for which a 
     * past-the-end iterator gets returned. This function invokes a provided function to 
     * compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param comp The function used to compare the elements.
    */
    template <class InputIt, class Compare>
    InputIt unique(InputIt first, InputIt last, Compare comp) {
        InputIt result = first;
        while (first != last) {
            if (!comp(*result, *first) && result != first) {
                *result = move(*first);
                result++;
            }
            first++;
        }
        return ++result;
    }
    /**
     * This function copies the elements from [first, last) to the range starting at 
     * result. This function invokes operator== to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the function results 
     * are stored.
    */
    template <class InputIt, class OutputIt>
    OutputIt unique_copy(InputIt first, InputIt last, OutputIt result) {
        if (first == last) 
            return result;
            
        while (first != last) {
            if (!(*(first + 1) == *first) || first + 1 == last) {
                *result++ = *first;
            }
            first++;
        }
        return ++result;
    }
    /**
     * This function copies the elements from [first, last) to the range starting at 
     * result. This function invokes a provided function to compare the elements.
     * @param first An iterator to the initial position of the sequence of elements.
     * @param last An iterator to the final position of the sequence of elements.
     * @param result An iterator to the initial position of the range where the function results 
     * are stored.
     * @param comp The function used to compare the elements.
    */
    template <class InputIt, class OutputIt, class Compare>
    OutputIt unique_copy(InputIt first, InputIt last, OutputIt result, Compare comp) {
        if (first == last) 
            return result;

        while (first != last) {
            if (!comp(*(first + 1), *first) || first + 1 == last) {
                *result++ = *first;
            }
            first++;
        }
        return ++result;
    }
    /**
     * This function swaps the values of two iterators.
     * @param a The first iterator.
     * @param b The second iterator.
    */
    template <class InputIt1, class InputIt2>
    void iter_swap(InputIt1 a, InputIt2 b) {
        swap(*a, *b);
    }
}

#endif /* _STD_COPY_ALGORITHM */