#ifndef _STD_COPY_CHAR_TRAITS
#define _STD_COPY_CHAR_TRAITS

#include "algorithm.hpp"
#include "iterator.hpp"

namespace _std_copy_hidden
{
    template <class CharT, class IntT>
    class _char_traits
    {
        public:
            typedef CharT       char_type;
            typedef IntT        int_type;

            /**
             * Assigns a to c.
             * @param c The character that gets assigned to.
             * @param a The character assigned.
            */
            static constexpr void assign(char_type& c, const char_type& a)
            {
                c = a;
            }
            /**
             * Assigns a to the first count characters starting from p.
             * @param p The start of the range to assign to.
             * @param count The number of characters to assign to.
             * @param a The character assigned.
            */
            static constexpr char_type* assign(char_type* p, unsigned long long count, const char_type& a) noexcept
            {
                std_copy::fill_n(p, count, a);
                return p;
            }
            /**
             * Checks if two characters are equal.
             * @param a The first character.
             * @param b The second character.
            */
            static constexpr bool eq(const char_type& a, const char_type& b) noexcept
            {
                return a == b;
            }
            /**
             * Checks if two int_type values are equal.
             * @param a The first value.
             * @param b The second value.
            */
            static constexpr bool eq_int_type(const int_type& a, const int_type b)
            {
                return a == b;
            }
            /**
             * Checks if a is less than b.
             * @param a The first character.
             * @param b The second character.
            */
            static constexpr bool lt(const char_type& a, const char_type& b) noexcept
            {
                return a < b;
            }
            /**
             * Moves count characters from src to dest.
             * @param dest The location to move the characters to.
             * @param src The location from where to get the characters to move to dest.
             * @param count The number of characters to move.
            */
            static constexpr char_type* move(char_type* dest, char_type* src, unsigned long long count) noexcept
            {
                char_type* ptrToStart = src;
                std_copy::advance(src, count);
                std_copy::move(ptrToStart, src, dest);
                return dest;
            }
            /**
             * Copies count characters from src to dest.
             * @param dest The location to copy the characters to.
             * @param src The location from where to get the characters to move to dest.
             * @param count The number of characters to copy.
            */
            static constexpr char_type* copy(char_type* dest, char_type* src, unsigned long long count) noexcept
            {
                for (unsigned int i = 0; i < count; i++)
                    assign(dest[i], src[i]);
                return dest;
            }
            /**
             * Returns a pointer to the first occurence of ch within the first count characters of the 
             * sequence pointing at p.
             * @param p A pointer to the start of the sequence.
             * @param count The number of characters to search in.
             * @param ch The character to search for.
            */
            static constexpr char_type* find(char_type* p, unsigned long long count, const char_type& ch) noexcept
            {
                for (unsigned long long i = 0; i < count; i++)
                {
                    if (eq(p[i], ch))
                        return &p[i];
                }
                return nullptr;
            }
            /**
             * Returns an EOF value based on the character.
            */
            static constexpr int_type eof()
            {
                return -1;
            }
            /**
             * Returns a value that is not equal to EOF.
             * @param a The value.
            */
            static constexpr int_type not_eof(const int_type& a)
            {
                return (a == eof()) ? 0 : a;
            }
            /**
             * Converts a value of type int_type to its corresponding value of type char_type.
             * @param a The value to convert.
            */
            static constexpr char_type to_char_type(const int_type& a)
            {
                return static_cast<char_type>(a);
            }
            /**
             * Converts a value of type char_type to its corresponding value of type int_type.
             * @param c The value to convert.
            */
            static constexpr int_type to_int_type(const char_type& c)
            {
                return static_cast<int_type>(c);
            }
            /**
             * Finds the length of the character sequence pointed to by s.
             * @param s A pointer to the start of the character sequence.
            */
            static constexpr unsigned long long length(char_type* s) noexcept
            {
                unsigned long long len = 0;
                while (!eq(s[len], char_type()))
                    len++;
                return len;
            }
            /**
             * Compares the first count characters of two character sequences lexixographically.
             * @param s1 The first character sequence.
             * @param s2 The second character sequence.
             * @param count The number of characters to compare.
            */
            static constexpr int compare(char_type* s1, char_type* s2, unsigned long long count)
            {
                for (unsigned long long i = 0; i < count; i++)
                {
                    if (lt(s1[i], s2[i]))
                        return -1;
                    else if (lt(s2[i], s1[i]))
                        return 1;
                }
                return 0;
            }
    };
}

namespace std_copy
{
    template <class CharT>
    class char_traits
        : public _std_copy_hidden::_char_traits<CharT, unsigned long long>
    {
    };
    //Partial specialization for char
    template <>
    class char_traits<char>
        : public _std_copy_hidden::_char_traits<char, int>
    {
    };
    //Partial specialization for wchar_t
    template <>
    class char_traits<wchar_t>
        : public _std_copy_hidden::_char_traits<wchar_t, unsigned short>
    {
    };
    //Partial specialization for char16_t
    template <>
    class char_traits<char16_t>
        : public _std_copy_hidden::_char_traits<char16_t, unsigned short>
    {
    };
    //Partial specialization for char32_t
    template <>
    class char_traits<char32_t>
        : public _std_copy_hidden::_char_traits<char32_t, unsigned int>
    {
    };
    //Partial specialization for char8_t (C++20)
    template <>
    class char_traits<char8_t>
        : public _std_copy_hidden::_char_traits<char8_t, unsigned int>
    {
    };
}

#endif