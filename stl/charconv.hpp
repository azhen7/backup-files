#ifndef _STD_COPY_CHARCONV
#define _STD_COPY_CHARCONV

#include "system_error.hpp"
#include "limits.hpp"
#include "type_traits.hpp"
#include "char_traits.hpp"

#define _CHARCONV_START_HIDDEN_SCOPE \
    namespace _std_copy_hidden       \
    {                                \
        namespace _std_copy_charconv \
        {

#define _CHARCONV_END_HIDDEN_SCOPE \
        }                          \
    }

_CHARCONV_START_HIDDEN_SCOPE
    int _from_alpha_to_num(char c, int base = 10)
    {
        if (c >= 'a' && c <= 'z' && base > 10)
            return c - 'a' + 10;
        if (c >= 'A' && c <= 'Z' && base > 10)
            return c - 'A' + 10;
        if (c >= '0' && c <= '9' && (c - '0') < base)
            return c - '0';
        return -1;
    }

    char _from_num_to_alpha(int c, int base)
    {
        if (c < 10)
        {
            char ret;
            if (c >= base)
                return -1;
            ret = c + '0';
            return ret;
        }
        if (c >= 10 && base > 10)
        {
            char ret = c + 'A' - 10;
            if (ret > 'Z')
                return -1;
            return ret;
        }
        return '\0';
    }

    bool _is_alpha_char(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool _is_num_char(char c)
    {
        return (c >= '0' && c <= '9');
    }
_CHARCONV_END_HIDDEN_SCOPE

namespace std_copy
{
    enum class chars_format
    {
        scientific = 1,
        fixed = 2,
        hex = 4,
        general = fixed | scientific
    };
    /**
     * The return type from the from_chars functions.
     * Contains a constant character pointer and an error code to 
     * indicate additional information on potential errors.
    */
    struct from_chars_result
    {
        const char *ptr;
        std_copy::errc ec;

        friend bool operator==(const from_chars_result &, const from_chars_result &) = default;
    };
    /**
     * The return type from the to_chars functions.
     * Contains a character pointer and an error code to 
     * indicate additional information on potential errors.
    */
    struct to_chars_result
    {
        char *ptr;
        std_copy::errc ec;

        friend bool operator==(const to_chars_result &, const to_chars_result &) = default;
    };
}

//std_copy::from_chars
_CHARCONV_START_HIDDEN_SCOPE
    template <class IntType>
    struct _from_chars_integral_helper
    {
        static std_copy::from_chars_result _from_chars(char *first, char *last, IntType &val, int base = 10)
    #if __cplusplus > 201703L
            requires std_copy::is_integral_v<IntType>
    #endif
        {
            using uleast_type = typename _std_copy_type_traits::_find_uleast<IntType>::type;
            uleast_type value = static_cast<uleast_type>(val);
            val = 0;

            std_copy::from_chars_result ret;

            bool has_val = false;
            short sign = 1;

            auto failure =
                [&](bool condition)
            {
                ret.ptr = first;
                value /= base;
                if (value > std_copy::numeric_limits<IntType>::max())
                {
                    ret.ptr = last;
                    ret.ec = std_copy::errc::result_out_of_range;
                    return ret;
                }

                val = value * sign;

                if (condition)
                    ret.ec = static_cast<std_copy::errc>(0);
                else
                    ret.ec = std_copy::errc::invalid_argument;

                return ret;
            };

            while (first != last)
            {
                if (_is_num_char(*first))
                {
                    int temp = _from_alpha_to_num(*first, base);
                    if (temp < 0)
                        return failure(has_val);

                    value += temp;
                }
                else if (_is_alpha_char(*first))
                {
                    int temp = _from_alpha_to_num(*first, base);
                    if (temp < 0)
                        return failure(has_val);

                    value += temp;
                }
                else
                {
                    if (!has_val && *first == '-')
                    {
                        if constexpr(std_copy::is_signed_v<IntType>)
                        {
                            sign = -1;
                            continue;
                        }
                    }

                    return failure(has_val);
                }
                value *= base;

                has_val = true;
                first++;
            }
            value /= base;
            ret.ptr = last;

            if (value > std_copy::numeric_limits<IntType>::max())
            {
                ret.ec = std_copy::errc::result_out_of_range;
                return ret;
            }

            ret.ec = static_cast<std_copy::errc>(0);

            val = value * sign;
            return ret;
        }
    };

    template <class FloatingPointType>
    struct _from_chars_float_helper
    {
        static std_copy::from_chars_result _from_chars(char *start, char *end, FloatingPointType &val, std_copy::chars_format fmt = std_copy::chars_format::general)
    #if __cplusplus > 201703L
            requires std_copy::is_floating_point_v<FloatingPointType>
    #endif
        {
            using floating_point_least_greater = typename _std_copy_type_traits::_find_least_floating_point<FloatingPointType>::type;
            floating_point_least_greater value = 0.0;

            std_copy::from_chars_result ret;

            bool is_decimal_mode = false;
            bool has_val = false;
            short sign = 1;
            short number_of_decimal_places_division_value = 10;
            val = 0;

            auto exit =
                [&](bool check_too_large, std_copy::errc if_value_not_too_large = std_copy::errc::result_out_of_range)
            {
                ret.ptr = start;
                ret.ec = if_value_not_too_large;

                if (check_too_large)
                {
                    ret.ec = std_copy::errc::result_out_of_range;
                    return ret;
                }
                if (!is_decimal_mode)
                    value /= 10;
                val = value * sign;

                return ret;
            };

            while (start != end)
            {
                if (*start == '-')
                    sign = -1;
                else if (*start == '.')
                {
                    is_decimal_mode = true;
                }
                else if (_is_num_char(*start))
                {
                    short current_digit = _from_alpha_to_num(*start);
                    if (is_decimal_mode)
                    {
                        if (number_of_decimal_places_division_value == 100000 && start + 1 != end)
                        {
                            if (!_is_num_char(*(start + 1)))
                                return exit(value > std_copy::numeric_limits<FloatingPointType>::max(), std_copy::errc::invalid_argument);

                            // Only accounts up to 5 decimal places; any more decimal places after that get rounded
                            if (_from_alpha_to_num(*(start + 1)) >= 5)
                                value += 0.00001;

                            while (start + 1 != end && _is_num_char(*(start + 1)))
                                start++;

                            break;
                        }
                        else
                        {
                            FloatingPointType valToAdd = static_cast<FloatingPointType>(current_digit) / number_of_decimal_places_division_value;
                            value += valToAdd;
                            number_of_decimal_places_division_value *= 10;
                        }
                    }
                    else
                    {
                        value = has_val ? value * 10 : value;
                        value += current_digit;
                    }
                    if (value > std_copy::numeric_limits<FloatingPointType>::max())
                        return exit(true);
                }
                else if ((*start == 'E' || *start == 'e') && has_val)
                {
                    // Checks for a valid formatting option and if there's a valid exponent after
                    if ((fmt == std_copy::chars_format::fixed && fmt != std_copy::chars_format::general) || start + 1 == end || !_is_num_char(*(start + 1)))
                    {
                        ret.ptr = start;

                        if (value > std_copy::numeric_limits<FloatingPointType>::max())
                        {
                            ret.ec = std_copy::errc::result_out_of_range;
                            return ret;
                        }
                        val = value * sign;

                        if (has_val)
                            ret.ec = static_cast<std_copy::errc>(0);
                        else
                            ret.ec = std_copy::errc::invalid_argument;

                        return ret;
                    }
                    int exp = 0;
                    std_copy::from_chars_result t = _from_chars_integral_helper<int>::_from_chars(start + 1, end, exp);
                    start = const_cast<char *>(t.ptr);

                    int count = 0;
                    auto v = value;
                    while (value > 0)
                    {
                        v = static_cast<int>(v / 10);
                        count++;
                    }
                    if (count + exp > 38)
                        return exit(true);

                    while (exp-- > 0)
                        value *= 10;

                    if (start != end)
                    {
                        ret.ptr = start;

                        if (value > std_copy::numeric_limits<FloatingPointType>::max())
                        {
                            ret.ec = std_copy::errc::result_out_of_range;
                            return ret;
                        }
                        val = value * sign;

                        if (has_val)
                            ret.ec = static_cast<std_copy::errc>(0);
                        else
                            ret.ec = std_copy::errc::invalid_argument;

                        return ret;
                    }
                }
                else
                    return exit(value > std_copy::numeric_limits<FloatingPointType>::max(), std_copy::errc::invalid_argument);

                has_val = true;
                start++;
            }
            return exit(value > std_copy::numeric_limits<FloatingPointType>::max(), static_cast<std_copy::errc>(0));
        }
    };
_CHARCONV_END_HIDDEN_SCOPE

#define _FROM_CHARS_INTEGRAL(type, first, last, val, base) (_std_copy_hidden::_std_copy_charconv::_from_chars_integral_helper<type>::_from_chars(first, last, val, base))
#define _FROM_CHARS_FLOATING_POINT(type, first, last, val, fmt) (_std_copy_hidden::_std_copy_charconv::_from_chars_float_helper<type>::_from_chars(first, last, val, fmt))

namespace std_copy
{
    /**
     * Converts the range [first, last) to an integral type.
     * @param first A pointer to the start of the range to convert.
     * @param last A pointer to the end of the range to convert.
     * @param val An integral type to store the result in.
     * @param base The base to interpret the range in.
    */
    from_chars_result from_chars(char *first, char *last, bool &val, int base = 10) = delete;
    from_chars_result from_chars(char *first, char *last, char &val, int base = 10)
    {
        return _FROM_CHARS_INTEGRAL(char, first, last, val, base);
    }
    from_chars_result from_chars(char *first, char *last, unsigned char &val, int base = 10)
    {
        return _FROM_CHARS_INTEGRAL(unsigned char, first, last, val, base);
    }
    from_chars_result from_chars(char *first, char *last, short &val, int base = 10)
    {
        return _FROM_CHARS_INTEGRAL(short, first, last, val, base);
    }
    from_chars_result from_chars(char *first, char *last, unsigned short &val, int base = 10)
    {
        return _FROM_CHARS_INTEGRAL(unsigned short, first, last, val, base);
    }
    from_chars_result from_chars(char *first, char *last, int &val, int base = 10)
    {
        return _FROM_CHARS_INTEGRAL(int, first, last, val, base);
    }
    from_chars_result from_chars(char *first, char *last, unsigned int &val, int base = 10)
    {
        return _FROM_CHARS_INTEGRAL(unsigned int, first, last, val, base);
    }
    from_chars_result from_chars(char *first, char *last, long &val, int base = 10)
    {
        return _FROM_CHARS_INTEGRAL(long, first, last, val, base);
    }
    from_chars_result from_chars(char *first, char *last, unsigned long &val, int base = 10)
    {
        return _FROM_CHARS_INTEGRAL(unsigned long, first, last, val, base);
    }
    from_chars_result from_chars(char *first, char *last, long long &val, int base = 10)
    {
        return _FROM_CHARS_INTEGRAL(long long, first, last, val, base);
    }
    from_chars_result from_chars(char *first, char *last, unsigned long long &val, int base = 10)
    {
        return _FROM_CHARS_INTEGRAL(unsigned long long, first, last, val, base);
    }

    /**
     * Converts the range [first, last) to an floating-point type.
     * @param start  pointer to the start of the range to convert.
     * @param end A pointer to the end of the range to convert.
     * @param val An integral type to store the result in.
     * @param fmt The formatting mode of the sequence.
    */
    from_chars_result from_chars(char *first, char *last, float &val, chars_format fmt = chars_format::general)
    {
        return _FROM_CHARS_FLOATING_POINT(float, first, last, val, fmt);
    }
    from_chars_result from_chars(char *first, char *last, double &val, chars_format fmt = chars_format::general)
    {
        return _FROM_CHARS_FLOATING_POINT(double, first, last, val, fmt);
    }
    from_chars_result from_chars(char *first, char *last, long double &val, chars_format fmt = chars_format::general)
    {
        return _FROM_CHARS_FLOATING_POINT(long double, first, last, val, fmt);
    }
}

//std_copy::to_chars
_CHARCONV_START_HIDDEN_SCOPE
    template <class IntType>
    struct _to_chars_integral_helper
    {
    private:
        static void _reverse(char *s, char *end)
        {
            unsigned int len = end - s;
            for (unsigned int i = 0; i < (int)(len / 2); i++)
            {
                char temp = s[i];
                s[i] = s[len - i - 1];
                s[len - i - 1] = temp;
            }
        }
        static void _copy(char *s, char *end, char *dest)
        {
            while (s != end)
            {
                *dest = *s;
                s++;
                dest++;
            }
        }

    public:
        static std_copy::to_chars_result _to_chars(char *first, char *last, IntType val, int base = 10)
    #if __cplusplus > 201703L
            requires std_copy::is_integral_v<IntType>
    #endif
        {
            std_copy::to_chars_result ret;
            char str_as_arr[last - first + 1];
            for (decltype(last - first) i = 0; i < last - first + 1; i++)
            {
                if (val < 0 && i == 0)
                {
                    first[0] = '-';
                    continue;
                }
                if (val == 0)
                {
                    first[last - first] = '\0';
                    _reverse(first, first + i);
                    //_copy(first, first + i + 1, first);

                    ret.ptr = last;
                    ret.ec = static_cast<std_copy::errc>(0);
                    return ret;
                }

                // auto q = val / base;
                // IntType digit = val - q * base;
                // val = q;
                IntType digit = val % base;
                val /= base;

                first[i] = _from_num_to_alpha(digit, base); //something about char* being read-only

                if (first[i] == '\0')
                {
                    ret.ptr = first + i;
                    ret.ec = std_copy::errc::invalid_argument;
                    return ret;
                }
            }
            ret.ptr = last;
            ret.ec = std_copy::errc::result_out_of_range;
            return ret;
        }
    };
_CHARCONV_END_HIDDEN_SCOPE

#define _TO_CHARS_INTEGRAL(type, first, last, val, base) (_std_copy_hidden::_std_copy_charconv::_to_chars_integral_helper<type>::_to_chars(first, last, val, base))

namespace std_copy
{
    /**
     * Convert a floating-point value to a string.
     * @param first The start of the range to store the decimal value in.
     * @param last The end of the range to store the decimal value in.
     * @param val The decimal value to convert.
    */
    to_chars_result to_chars(char *first, char *last, int val, int base = 10)
    {
        return _TO_CHARS_INTEGRAL(int, first, last, val, base);
    }
    to_chars_result to_chars(char *first, char *last, unsigned int val, int base = 10)
    {
        return _TO_CHARS_INTEGRAL(unsigned int, first, last, val, base);
    }
    to_chars_result to_chars(char *first, char *last, short val, int base = 10)
    {
        return _TO_CHARS_INTEGRAL(short, first, last, val, base);
    }
    to_chars_result to_chars(char *first, char *last, unsigned short val, int base = 10)
    {
        return _TO_CHARS_INTEGRAL(unsigned short, first, last, val, base);
    }
    to_chars_result to_chars(char *first, char *last, char val, int base = 10)
    {
        return _TO_CHARS_INTEGRAL(char, first, last, val, base);
    }
    to_chars_result to_chars(char *first, char *last, long val, int base = 10)
    {
        return _TO_CHARS_INTEGRAL(long, first, last, val, base);
    }
    to_chars_result to_chars(char *first, char *last, unsigned long val, int base = 10)
    {
        return _TO_CHARS_INTEGRAL(unsigned long, first, last, val, base);
    }
    to_chars_result to_chars(char *first, char *last, long long val, int base = 10)
    {
        return _TO_CHARS_INTEGRAL(long long, first, last, val, base);
    }
    to_chars_result to_chars(char *first, char *last, unsigned long long val, int base = 10)
    {
        return _TO_CHARS_INTEGRAL(unsigned long long, first, last, val, base);
    }
    to_chars_result to_chars(char *first, char *last, bool val, int base = 10) = delete;
}

#endif /* _STD_COPY_CHARCONV */