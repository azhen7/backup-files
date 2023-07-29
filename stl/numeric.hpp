#ifndef _STD_COPY_NUMERIC
#define _STD_COPY_NUMERIC

#include "move.hpp"
#include "iterator.hpp"

namespace std_copy
{
    /**
     * Fills the range [first, last) with sequentially increasing values, starting
     * with value and repeatedly incrementing value.
     * @param first The start of the range to fill.
     * @param last The end of the range to fill.
     * @param value The starting value.
    */
    template <class ForwardIt, class T>
    constexpr void iota(ForwardIt first, ForwardIt last, T value)
#if __cplusplus > 201703L
    requires input_iterator<ForwardIt>
#endif
    {
        while (first != last)
        {
            *first++ = value;
            value++;
        }
    }
    /**
     * Computes the sum of the values in the range [first, last) and a given value init.
     * Invokes operator+.
     * @param first The start of the range to sum.
     * @param last The end of the range to sum.
     * @param init A given value added to each element in the range.
    */
    template <class ForwardIt, class T>
    constexpr T accumulate(ForwardIt first, ForwardIt last, T init)
#if __cplusplus > 201703L
    requires input_iterator<ForwardIt>
#endif
    {
        while (first != last)
        {
            init = move(init) + *first;
            first++;
        }
        return init;
    }
    /**
     * Computes the sum of the values in the range [first, last) and a given value init.
     * Invokes a custom adding object adder.
     * @param first The start of the range to sum.
     * @param last The end of the range to sum.
     * @param init A given value added to each element in the range.
     * @param adder A custom adding object used to calculate the sum.
    */
    template <class ForwardIt, class T, class Adder>
    constexpr T accumulate(ForwardIt first, ForwardIt last, T init, Adder adder)
#if __cplusplus > 201703L
    requires input_iterator<ForwardIt>
#endif
    {
        while (first != last)
        {
            init = adder(move(init), *first);
            first++;
        }
        return init;
    }
    /**
     * Computes the inner product of the range [first, last) and the range
     * starting at first2, with a value init added onto the final product.
     * Invokes operator* and operator+.
     * @param first1 The start of the first range.
     * @param last1 The end of the first range.
     * @param first2 The start of the second range.
     * @param init The value added onto the final product.
    */
    template <class ForwardIt1, class ForwardIt2, class T>
    constexpr T inner_product(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, T init)
#if __cplusplus > 201703L
    requires input_iterator<ForwardIt1>
    && input_iterator<ForwardIt2>
#endif
    {
        while (first1 != last1)
        {
            init = move(init) + (*first1) * (*first2);
            first1++;
            first2++;
        }
        return init;
    }
    /**
     * Computes the inner product of the range [first, last) and the range
     * starting at first2, with a value init added onto the final product.
     * Invokes two custom objects to compute multiplication and addition.
     * @param first1 The start of the first range.
     * @param last1 The end of the first range.
     * @param first2 The start of the second range.
     * @param init The value added onto the final product.
     * @param adder The custom object used to add.
     * @param multiplier The custom object used to multiply.
    */
    template <class ForwardIt1, class ForwardIt2, class T, class Adder, class Multiplier>
    constexpr T inner_product(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, T init, Adder adder, Multiplier multiplier)
#if __cplusplus > 201703L
    requires input_iterator<ForwardIt1>
    && input_iterator<ForwardIt2>
#endif
    {
        while (first1 != last1)
        {
            init = adder(move(init), multiplier(*first1, *first2));
            first1++;
            first2++;
        }
        return init;
    }
    /**
     * Computes the differences of adjacent elements in [first, last) and stores
     * the values in the range starting at dest. Invokes operator- to compute the
     * differences.
     * @param first The start of the input range.
     * @param last The end of the input range.
     * @param dest The start of the storage range.
    */
    template <class ForwardIt, class OutputIt>
    constexpr OutputIt adjacent_difference(ForwardIt first, ForwardIt last, OutputIt dest)
#if __cplusplus > 201703L
    requires input_iterator<ForwardIt>
    && output_iterator<OutputIt>
#endif
    {
        if (first == last) return dest;

        ForwardIt temp = first;
        *dest++ = *first++;
        while (first != last)
        {
            *dest++ = *first - *temp;
            first++;
            temp++;
        }
        return ++dest;
    }
    /**
     * Computes the differences of adjacent elements in [first, last) and stores
     * the values in the range starting at dest. Invokes a custom object to compute the
     * differences.
     * @param first The start of the input range.
     * @param last The end of the input range.
     * @param dest The start of the storage range.
     * @param subtractor The custom object used to compute the differences.
    */
    template <class ForwardIt, class OutputIt, class Subtractor>
    constexpr OutputIt adjacent_difference(ForwardIt first, ForwardIt last, OutputIt dest, Subtractor subtractor)
#if __cplusplus > 201703L
    requires input_iterator<ForwardIt>
    && output_iterator<OutputIt>
#endif
    {
        if (first == last) return dest;

        ForwardIt temp = first;
        *dest++ = *first++;
        while (first != last)
        {
            *dest++ = subtracter(*first, *temp);
            first++;
            temp++;
        }
        return ++dest;
    }
    /**
     * Computes the sum of the subranges of the range [first, last) and stores
     * the values in the range starting at dest. Invokes operator+ to add the elements.
     * @param first The start of the range to add.
     * @param last The end of the range to add.
     * @param dest The start of the storage range.
    */
    template <class ForwardIt, class OutputIt>
    constexpr OutputIt partial_sum(ForwardIt first, ForwardIt last, OutputIt dest)
#if __cplusplus > 201703L
    requires input_iterator<ForwardIt>
    && output_iterator<OutputIt>
#endif
    {
        if (first == last) return dest;

        auto sum = *first++;
        *dest++ = sum;

        while (first != last)
        {
            sum = move(sum) + *first;
            *dest++ = sum;
            first++;
        }
        return ++dest;
    }
    /**
     * Computes the sum of the subranges of the range [first, last) and stores
     * the values in the range starting at dest. Invokes a custom object to add the elements.
     * @param first The start of the range to add.
     * @param last The end of the range to add.
     * @param dest The start of the storage range.
     * @param adder The custom object used to add elements.
    */
    template <class ForwardIt, class OutputIt, class Adder>
    constexpr OutputIt partial_sum(ForwardIt first, ForwardIt last, OutputIt dest, Adder adder)
#if __cplusplus > 201703L
    requires input_iterator<ForwardIt>
    && output_iterator<OutputIt>
#endif
    {
        if (first == last) return dest;

        auto sum = *first++;
        *dest++ = sum;

        while (first != last)
        {
            sum = adder(move(sum), *first);
            *dest++ = sum;
            first++;
        }
        return ++dest;
    }
};

#endif /* _STD_COPY_NUMERIC */