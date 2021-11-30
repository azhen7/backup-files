#ifndef _STD_COPY_CHARCONV
#define _STD_COPY_CHARCONV

#include "system_error.hpp"
#include "limits.hpp"
#include "type_traits.hpp"

namespace _std_copy_hidden
{
    namespace _std_copy_charconv
    {
        int _from_alpha_to_num(char c)
        {
            if (c >= 'a' && c <= 'z')
                return c - 'a' + 10;
            if (c >= 'A' && c <= 'Z')
                return c - 'A' + 10;
            if (c >= '0' && c <= '9')
                return c - '0';
            return -1;
        }

        namespace _detail
        {
            template <class T, bool B, class ...Args>
            struct _select;

            template <class T, class IntT, class ...Args>
            struct _select<T, true, IntT, Args...>
            {
                typedef IntT    type;
            };
            template <class T, class IntT, class NextIntT, class ...Args>
            struct _select<T, false, IntT, NextIntT, Args...> 
                : _select<T, sizeof(T) <= sizeof(NextIntT), NextIntT, Args...>
            {
            };
            template <class T, class IntT>
            struct _select<T, false, IntT>
            {
                typedef T   type;
            };
        }

        template <class T>
        struct _find_uleast
        {
            using type = _detail::_select<T, sizeof(T) <= sizeof(unsigned short),
                        unsigned short,
                        unsigned int,
                        unsigned long,
                        unsigned long long,
                        unsigned __int128>::type;
        };

        bool _is_alpha_char(char c)
        {
            return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        }

        bool _is_num_char(char c)
        {
            return (c >= '0' && c <= '9');
        }
    }
}

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
     * Contains a pointer and an error code to indicate additional information on 
     * potential errors.
    */
    struct from_chars_result
    {
        const char* ptr;
        errc ec;
    };
    /**
     * Converts the range [first, last) to an integral type.
     * @param first A pointer to the start of the range to convert.
     * @param last A pointer to the end of the range to convert.
     * @param value An integral type to store the result in.
     * @param base The base to interpret the range in.
    */
    template <class IntType>
    from_chars_result from_chars(char* first, char* last, IntType& val, int base = 10)
        requires is_integral_v<IntType>
    {
        using uleast_type = _std_copy_hidden::_std_copy_charconv::_find_uleast<IntType>::type;
        uleast_type value = static_cast<uleast_type>(val);

        bool hasVal = false;
        int sign = 1;

        auto failure =
        [&](bool condition)
        {
            from_chars_result ret;
            ret.ptr = first;
            value /= base;
            if (value > numeric_limits<IntType>::max())
            {
                ret.ptr = last;
                ret.ec = errc::result_out_of_range;
                return ret;
            }

            val = value;

            if (condition)
                ret.ec = static_cast<errc>(0);
            else
                ret.ec = errc::invalid_argument;

            return ret;
        };

        while (first != last)
        {
            if (_std_copy_hidden::_std_copy_charconv::_is_num_char(*first))
            {
                int temp = _std_copy_hidden::_std_copy_charconv::_from_alpha_to_num(*first);
                if (temp >= base)
                    return failure(hasVal);

                value += temp;
            }
            else if (_std_copy_hidden::_std_copy_charconv::_is_alpha_char(*first))
            {
                if (base < 11)
                    return failure(hasVal);
                    
                int temp = _std_copy_hidden::_std_copy_charconv::_from_alpha_to_num(*first);
                if (temp >= base)
                    return failure(hasVal);
                    
                value += temp;
            }
            else
            {
                if (!hasVal && *first == '-')
                {
                    if constexpr(is_signed_v<IntType>)
                    {
                        sign = -1;
                        continue;
                    }
                }
                
                return failure(hasVal);
            }
            if (first + 1 != last)
                value *= base;

            hasVal = true;
            first++;
        }
        from_chars_result ret;
        ret.ptr = last;

        if (value > numeric_limits<IntType>::max())
        {
            ret.ec = errc::result_out_of_range;
            return ret;
        }

        ret.ec = static_cast<errc>(0);

        val = value;
        val *= sign;
        return ret;
    }
}

#endif /* _STD_COPY_CHARCONV */