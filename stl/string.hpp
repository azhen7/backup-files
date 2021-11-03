#ifndef _STD_COPY_STRING
#define _STD_COPY_STRING

#include "allocator.hpp"
#include "allocator_traits.hpp"
#include "iterator.hpp"
#include "char_traits.hpp"

namespace std_copy
{
    template <class CharT, class Traits = std_copy::char_traits<CharT>, class Alloc = std_copy::allocator<CharT>>
    class basic_string
    {
        private:
            typedef basic_string<CharT, Traits, Alloc>      _basic_string_type;
            typedef iterator<_basic_string_type>            _iterator_type;
            typedef std_copy::allocator_traits<Alloc>       _alloc_traits;

        public:
            typedef CharT                                   value_type;
            typedef Traits                                  traits_type;
            typedef Alloc                                   allocator_type;
            typedef _alloc_traits::size_type                size_type;
            typedef _alloc_traits::difference_type          difference_type;
            typedef CharT&                                  reference;
            typedef const CharT&                            const_reference;
            typedef _alloc_traits::pointer                  pointer;
            typedef const pointer                           const_pointer;
            typedef _iterator_type                          iterator;
            typedef const iterator                          const_iterator;

        private:
            pointer _internalString;
            size_type _length;
            size_type _capacity;
        
        public:
            const size_type npos = -1;

            basic_string()
                : _length(0),
                _capacity(0),
                _internalString(nullptr)
            {
            }

            basic_string(pointer str)
            {
                _length = traits_type::length(str);
                _capacity = _length;
                _internalString = allocator_type::allocate(_capacity);
                traits_type::move(_internalString, str, _length);
            }
            basic_string(pointer str, const allocator_type& a)
            {
                _length = traits_type::length(str);
                _capacity = _length;
                _internalString = a.allocate(_capacity);
                traits_type::move(_internalString, str, _length);
            }

            basic_string(size_type count, value_type ch)
                : _length(count),
                _capacity(count)
            {
                _internalString = allocator_type::allocate(_capacity);
                traits_type::assign(_internalString, count, ch);
            }
            basic_string(size_type count, value_type ch, const allocator_type& a)
                : _length(count),
                _capacity(count)
            {
                _internalString = a.allocate(_capacity);
                traits_type::assign(_internalString, count, ch);
            }

            basic_string(pointer str, size_type count)
                : _length(count),
                _capacity(count)
            {
                _internalString = allocator_type::allocate(_capacity);
                traits_type::move(_internalString, str, count);
            }
            basic_string(pointer str, size_type count, const allocator_type& a)
                : _length(count),
                _capacity(count)
            {
                _internalString = a.allocate(_capacity);
                traits_type::move(_internalString, str, count);
            }

            basic_string(const _basic_string_type& s, size_type count)
            {
                size_type copyUpTo = (count > s._length) ? s._length : count;
                _length = copyUpTo;
                _capacity = copyUpTo;
                _internalString = allocator_type::allocate(_capacity);
                traits_type::move(_internalString, s._internalString, copyUpTo);
            }
            basic_string(const _basic_string_type& s, size_type count, const allocator_type& a)
            {
                _length = s._length;
                _capacity = s._capacity;
                size_type copyUpTo = (count > _length) ? _length + 1 : count;
                _internalString = a.allocate(_capacity);
                traits_type::move(_internalString, s._internalString, copyUpTo);
            }

            basic_string(const _basic_string_type& s, size_type pos, size_type count)
            {
                size_type copyUpTo = (pos + count > s._length || count == npos) ? s._length + 1 : pos + count;
                _length = copyUpTo - pos;
                _capacity = copyUpTo - pos;
                _internalString = allocator_type::allocate(_capacity);
                traits_type::move(_internalString, s._internalString + pos, count);
            }
            basic_string(const _basic_string_type& s, size_type pos, size_type count, const allocator_type& a)
            {
                size_type copyUpTo = (pos + count > s._length || count == npos) ? s._length : pos + count;
                _length = copyUpTo - pos;
                _capacity = copyUpTo - pos;
                _internalString = a.allocate(_capacity);
                traits_type::move(_internalString, s._internalString + pos, s._internalString + pos + count);
            }

            basic_string(const _basic_string_type& s)
                : _length(s._length),
                _capacity(s._capacity)
            {
                _internalString = allocator_type::allocate(_capacity);
                traits_type::move(_internalString, s._internalString, _length);
            }
            basic_string(const _basic_string_type& s, const allocator_type& a)
                : _length(s._length),
                _capacity(s._capacity)
            {
                _internalString = a.allocate(_capacity);
                traits_type::move(_internalString, s._internalString, _length);
            }

            basic_string(_basic_string_type&& s)
                : _length(s._length),
                _capacity(s._capacity)
            {
                _internalString = allocator_type::allocate(_capacity);
                traits_type::move(_internalString, s._internalString, _length);
            }
            basic_string(_basic_string_type&& s, const allocator_type& a)
                : _length(s._length),
                _capacity(s._capacity)
            {
                _internalString = a.allocate(_capacity);
                traits_type::move(_internalString, s._internalString, _length);
            }

            template <class InputIt>
            basic_string(InputIt start, InputIt last)
            {
                _length = std_copy::distance(start, last);
                _capacity = _length;
                _internalString = allocator_type::allocate(_capacity);
                size_type i = 0;
                while (start != last)
                    _internalString[i++] = *start++;
            }
            template <class InputIt>
            basic_string(InputIt start, InputIt last, const allocator_type& a)
            {
                _length = std_copy::distance(start, last);
                _capacity = _length;
                _internalString = a.allocate(_capacity);
                size_type i = 0;
                while (start != last)
                    _internalString[i++] = *start++;
            }

            /**
             * Returns the length of the string.
            */
            size_type length() const noexcept
            {
                return _length;
            }
            /**
             * Returns the size of the string (i.e. the number of characters).
            */
            size_type size() const noexcept
            {
                return _length;
            }

            reference operator[](size_type i)
            {
                return _internalString[i];
            }
    };

    typedef basic_string<char>      string;
    typedef basic_string<wchar_t>   wstring;
    typedef basic_string<char8_t>   u8string;
    typedef basic_string<char16_t>  u16string;
    typedef basic_string<char32_t>  u32string;
}

#endif