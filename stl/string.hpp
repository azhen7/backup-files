#ifndef _STD_COPY_STRING
#define _STD_COPY_STRING

#include <stdexcept>

#include "allocator.hpp"
#include "allocator_traits.hpp"
#include "iterator_funcs.hpp"
#include "iterator_adaptors.hpp"
#include "char_traits.hpp"
#include "algorithm.hpp"
#include "uninitialized_algo.hpp"

#if __cplusplus > 201703L
namespace _std_copy_hidden
{
    namespace _std_copy_string
    {
        template <class CharT>
        concept _is_valid_char_type = 
        requires(CharT c1, CharT c2)
        {
            {c1 == c2} -> std_copy::same_as<bool>;
            {c1 != c2} -> std_copy::same_as<bool>;
            {c1 = c2};
            {c1 < c2} -> std_copy::same_as<bool>;
            {CharT()};
        };
    }
}
#endif

namespace std_copy
{
    /**
     * An implementation of std::basic_string from <string> and the typedefs present: 
     * std::string. std::wstring, std::u8string, std::u16string, and std::u32string;
     * @param CharacterType The character of which its pointer type is used as the underlying buffer.
     * @param Traits The traits of CharacterType, which manipulates sequences of CharacterType.
     * @param Alloc The allocator object used in allocating the underlying character sequence.
    */
    template <class CharacterType, class Traits = char_traits<CharacterType>, class Alloc = allocator<CharacterType>>
#if __cplusplus > 201703L
    requires _std_copy_hidden::_std_copy_string::_is_valid_char_type<CharacterType>
             && _std_copy_hidden::_std_copy_allocator::_is_valid_allocator<Alloc>
#endif
    class basic_string
    {
        protected:
            typedef basic_string<CharacterType, Traits, Alloc> _basic_string_type;
            typedef std_copy::allocator_traits<Alloc>          _alloc_traits;

        public:
            typedef CharacterType                           value_type;
            typedef Traits                                  traits_type;
            typedef Alloc                                   allocator_type;
            typedef _alloc_traits::size_type                size_type;
            typedef _alloc_traits::difference_type          difference_type;
            typedef CharacterType&                          reference;
            typedef const CharacterType&                    const_reference;
            typedef _alloc_traits::pointer                  pointer;
            typedef const _alloc_traits::pointer            const_pointer;
            typedef _std_copy_hidden::_std_copy_stl_containers::_iterator<_basic_string_type> iterator;
            typedef const iterator                          const_iterator;
            typedef reverse_iterator<pointer>               reverse_iterator;
            typedef const reverse_iterator                  const_reverse_iterator;

        protected:
            pointer _internalString;
            size_type _length;
            size_type _capacity;

            template <class _AllocateFunc>
            constexpr void _allocate_and_move_str(size_type i, _AllocateFunc mem_alloc, pointer src, size_type count)
            {
                _capacity = (i + 1 > 15) ? i + 1 : 15;
                _internalString = mem_alloc(_capacity);
                traits_type::move(_internalString, src, count);
                _internalString[i] = value_type();
            }

            template <class _AllocateFunc>
            constexpr void _allocate_and_assign_str(size_type i, _AllocateFunc mem_alloc, size_type count, const_reference ch)
            {
                _capacity = (i + 1 > 15) ? i + 1 : 15;
                _internalString = mem_alloc(_capacity);
                traits_type::assign(_internalString, count, ch);
                _internalString[i] = value_type();
            }

            template <class _AllocateFunc, class InputIterator>
            constexpr void _allocate_and_move_range(size_type i, _AllocateFunc mem_alloc, InputIterator first, InputIterator last)
            {
                _capacity = (i + 1 > 15) ? i + 1 : 15;
                _internalString = mem_alloc(_capacity);
                std_copy::move(first, last, _internalString);
                _internalString[i] = value_type();
            }

            constexpr size_type _calculate_smallest_power_of_two_greater_than(size_type x)
            {
                if (x == 0)
                    return 1;
                return __builtin_pow(2, (size_type) (__builtin_log(x) / __builtin_log(2)) + 1);
            }

            //Reallocates the internal buffer.
            constexpr void _realloc(size_type n, size_type copyUpTo)
            {
                pointer temp = _internalString;
                size_type newSize = _capacity * _calculate_smallest_power_of_two_greater_than(n);
                _allocate_and_move_str(newSize - 1, allocator_type::allocate, temp, copyUpTo);
                allocator_type::deallocate(temp, _capacity);
                _capacity = newSize;
            }

            //Null terminates the internal buffer and updates _length
            constexpr void _terminate_and_update_length(size_type newLen = npos, size_type whereToTerminate = npos)
            {
                if (newLen == npos)
                    newLen = _length;
                _length = move(newLen);

                if (whereToTerminate == npos)
                    whereToTerminate = _length;
                _internalString[whereToTerminate] = value_type();
            }

            template <class ExceptionType = std::out_of_range>
            constexpr void _check_exception(size_type a, difference_type checkAgainst, const char* str)
            {
                if (a >= checkAgainst)
                    throw ExceptionType(str);
            }

            constexpr void _move_string(pointer dest, pointer src, size_type n)
            {
                if (n == 1)
                    traits_type::assign(*dest, *src);
                else
                    traits_type::move(dest, src, n);
                
                _terminate_and_update_length(_length - n);
            }

            //Contains other helper one-use functions
            struct _helper
            {
                static void _to_upper(reference c)
                {
                    c -= 32 * (c >= 'a' && c <= 'z');
                }
                static void _to_lower(reference c)
                {
                    c += 32 * (c >= 'A' && c <= 'Z');
                }
            };

        public:
            const static size_type npos = -1;

            basic_string()
                : _length(0),
                _capacity(15)
            {
                _internalString = allocator_type::allocate(15);
            }

            basic_string(const_pointer str)
            {
                _length = traits_type::length(str);
                _allocate_and_move_str(_length, allocator_type::allocate,
                    str, _length);
            }

            basic_string(size_type count, const_reference ch)
                : _length(count)
            {
                _allocate_and_assign_str(_length, allocator_type::allocate,
                    count, ch);
            }

            basic_string(const_pointer str, size_type count)
                : _length(count)
            {
                _allocate_and_move_str(_length - 1, allocator_type::allocate,
                    str, count);
            }

            basic_string(const _basic_string_type& s, size_type count)
            {
                _length = (count > s._length) ? s._length : count;
                _allocate_and_move_str(_length, allocator_type::allocate,
                    s._internalString, _length);
            }

            basic_string(const _basic_string_type& s, size_type pos, size_type count)
            {
                size_type copyUpTo = (pos + count > s._length || count == npos) ? s._length : pos + count;
                _length = copyUpTo - pos;
                _allocate_and_move_str(_length, allocator_type::allocate,
                    s._internalString + pos, _length);
            }

            basic_string(const _basic_string_type& s)
                : _length(s._length)
            {
                _allocate_and_move_str(_length, allocator_type::allocate,
                    s._internalString, _length);
            }

            basic_string(_basic_string_type&& s)
                : _length(move(s._length)),
                _internalString(move(s._internalString))
            {
            }

            template <class InputIterator>
            basic_string(InputIterator start, InputIterator last)
            {
                _length = std_copy::distance(start, last);
                _allocate_and_move_range(_length, allocator_type::allocate,
                    start, last);
            }

            basic_string(decltype(nullptr)) = delete;

            ~basic_string()
            {
                allocator_type::deallocate(_internalString, _capacity);
            }

            /**
             * Returns the length of the string.
            */
            constexpr size_type length() const noexcept { return _length; }
            /**
             * Returns the size of the string (i.e. the number of characters).
            */
            constexpr size_type size() const noexcept { return _length; }
            /**
             * Returns the capacity of the string, i.e. the number of elements the 
             * string has storage for.
            */
            constexpr size_type capacity() const noexcept { return _capacity; }
            /**
             * Returns the allocator object associated with the string.
            */
            constexpr allocator_type get_allocator() const noexcept { return allocator_type(); }
            /**
             * Returns the underlying buffer serving as storage.
            */
            constexpr const_pointer data() const noexcept
            {
                _internalString[_length] = value_type();
                return _internalString;
            }
            /**
             * Returns a non-modifiable C style array version of the string. 
            */
            constexpr const_pointer c_str() const noexcept
            {
                _internalString[_length] = value_type();
                return _internalString;
            }
            /**
             * Returns the element at index i.
             * @param i The index to retrieve the element from.
            */
            constexpr reference at(size_type i) const noexcept
            {
                _check_exception(i, _length, "basic_string::at: i out of bounds");
                return *(_internalString + i);
            }
            /**
             * Returns the element at index i. Provides C-style array indexing.
             * @param i The index to retrieve the element from.
            */
            constexpr reference operator[](size_type i) const noexcept { return *(_internalString + i); }
            /**
             * Returns a reference to the first character in the string. Equivalent to 
             * (*this)[0].
            */
            constexpr reference front() const noexcept { return *_internalString; }
            /**
             * Returns a reference to the last character in the string. Equivalent to 
             * (*this)[_length - 1].
            */
            constexpr reference back() const noexcept { return *(_internalString + _length - 1); }
            /**
             * Returns an iterator to the start of the string.
            */
            constexpr iterator begin() const noexcept { return iterator(_internalString); }
            /**
             * Returns an iterator to the theoretical element after the last element.
            */
            constexpr iterator end() const noexcept { return iterator(_internalString + _length); }
            /**
             * Returns a const iterator to the start of the string.
            */
            constexpr const_iterator cbegin() const noexcept { return iterator(_internalString); }
            /**
             * Returns a const iterator to the theoretical element after the last element.
            */
            constexpr const_iterator cend() const noexcept { return iterator(_internalString + _length); }
            /**
             * Returns a reverse iterator to the reverse beginning of the string.
            */
            constexpr reverse_iterator rbegin() const noexcept { return reverse_iterator(_internalString + _length); }
            /**
             * Returns a reverse iterator to the reverse end of the string.
            */
            constexpr reverse_iterator rend() const noexcept { return reverse_iterator(_internalString); }
            /**
             * Returns a const reverse iterator to the reverse beginning of the string.
            */
            constexpr const_reverse_iterator crbegin() const noexcept { return reverse_iterator(_internalString + _length); }
            /**
             * Returns a const reverse iterator to the reverse end of the string.
            */
            constexpr const_reverse_iterator crend() const noexcept { return reverse_iterator(_internalString); }
            /**
             * Returns a boolean indicating whether the string is empty.
            */
            constexpr bool empty() const noexcept { return _length == 0; }
            /**
             * Reserves additional memory in the string.
            */
            constexpr void reserve(size_type newCap)
            {
                if (newCap <= _capacity)
                    return;

                pointer temp = _internalString;
                _internalString = allocator_type::allocate(newCap);
                traits_type::move(_internalString, temp, _length);
                allocator_type::deallocate(temp, _capacity);
                _capacity = newCap;
                _terminate_and_update_length();
            }
            /**
             * Shrinks the amount of storage in the string to the number of elements 
             * in the string.
            */
            constexpr void shrink_to_fit()
            {
                pointer temp = _internalString;
                _internalString = allocator_type::allocate(_length);
                traits_type::move(_internalString, temp, _length);
                allocator_type::deallocate(temp, _capacity);
                _terminate_and_update_length();
            }
            /**
             * Appends the first count elements from the sequence of characters pointed to by p onto the end of 
             * the string.
             * @param p The pointer to the start of the sequence of characters.
             * @param count The number of elements to append.
            */
            constexpr _basic_string_type& append(const_pointer str, size_type count)
            {
                if (_length + count > _capacity)
                    _realloc((_length + count) / _capacity, _length);

                traits_type::move(_internalString + _length, str, count);
                _terminate_and_update_length(_length + count);
                return *this;
            }
            /**
             * Appends the entire sequence of characters pointed to by p onto the end of the string.
             * @param p The pointer to the start of the sequence of characters.
            */
            constexpr _basic_string_type& append(const_pointer str)
            {
                return this->append(str, traits_type::length(str));
            }
            /**
             * Appends count characters with value ch.
             * @param count The number of characters to append.
             * @param ch The character to append.
            */
            constexpr _basic_string_type& append(size_type count, const_reference ch)
            {
                if (_length + count > _capacity)
                    _realloc((_length + count) / _capacity, _length);

                traits_type::assign(_internalString + _length, count, ch);
                _terminate_and_update_length(_length + count);
                return *this;
            }
            /**
             * Appends another basic_string string onto this string. It appends the 
             * first count characters starting from pos.
             * @param s The string object that gets appended.
             * @param pos The starting position from where to append.
             * @param count The number of characters after pos to append.
            */
            constexpr _basic_string_type& append(const _basic_string_type& s, size_type pos = 0, size_type count = npos)
            {
                _check_exception(pos, s._length, "basic_string::append: pos is greater than the length of s");
                if (pos + count > s._length || count == npos)
                    count = s._length - pos;
                
                return this->append(s._internalString + pos, count);
            }
            /**
             * Appends a rvalue reference'd basic_string object onto *this.
             * @param s The object that gets appended.
             * @param pos The starting position in obj from where to append.
             * @param count The number of characters after pos to append.
            */
            constexpr _basic_string_type& append(_basic_string_type&& s, size_type pos = 0, size_type count = npos)
            {
                _check_exception(pos, s._length, "basic_string::append: pos is greater than the length of s");
                if (pos + count > s._length || count == npos)
                    count = s._length - pos;
                
                return this->append(move(s._internalString + pos), count);
            }
            /**
             * Copies the contents of str to *this.
             * @param str The basic_string object to copy from.
            */
            constexpr _basic_string_type& assign(const _basic_string_type& str)
            {
                this->assign(str, str._length);
            }
            /**
             * Copies the first n characters of str to *this.
             * @param str The basic_string object to copy from.
             * @param count The number of characters to copy.
            */
            constexpr _basic_string_type& assign(const _basic_string_type& str, size_type count)
            {
                if (_length > count)
                {
                    traits_type::move(_internalString, str._internalString, count);
                    _terminate_and_update_length(count);
                    return *this;
                }
                else
                {
                    _length = count;
                    _allocate_and_move_str(_length, allocator_type::allocate,
                        str._internalString, _length);
                }
                return *this;
            }
            /**
             * Copies the first n characters of str after pos.
             * @param str The basic_string object to copy from.
             * @param pos The number of characters to copy.
             * @param count The number of characters after pos to copy.
            */
            constexpr _basic_string_type& assign(const _basic_string_type& str, size_type pos, size_type count)
            {
                return this->assign(str, 0, count);
            }
            /**
             * Copies the first n characters of s.
             * @param s The character sequence to copy from.
             * @param count The number of characters to copy.
            */
            constexpr _basic_string_type assign(const_pointer s, size_type count)
            {
                if (_length > count)
                {
                    traits_type::move(_internalString, s, count);
                    _terminate_and_update_length(count);
                }
                else
                {
                    _length = count;
                    _allocate_and_move_str(_length, allocator_type::allocate,
                        s, _length);
                }
                return *this;
            }
            /**
             * Copies the character sequence s.
             * @param s The character sequence to copy from.
            */
            constexpr _basic_string_type assign(const_pointer s)
            {
                return this->assign(s, traits_type::length(s));
            }
            /**
             * Assigns *this count occurences of ch.
            */
            constexpr _basic_string_type assign(size_type count, const_reference ch)
            {
                _length = count;
                _allocate_and_assign_str(_length, allocator_type::allocate,
                    count, ch);
            }
            /**
             * Appends all the characters in the range [first, last) onto the end of the string.
             * @param first An iterator to the start of the sequence.
             * @param last An iterator to the end of the sequence.
            */
            template <class InputIterator>
            constexpr _basic_string_type& append(InputIterator first, InputIterator last)
        #if __cplusplus > 201703L
            requires input_iterator<InputIterator>
        #endif
            {
                const difference_type dist = std_copy::distance(first, last);
                if (_length + dist > _capacity)
                    _realloc((_length + dist) / _capacity, _length);

                std_copy::move(first, last, _internalString + _length);
                _terminate_and_update_length(_length + dist);

                return *this;
            }
            /**
             * Overloaded operator+=. This operator appends a character sequence pointed to by 
             * p onto the end of the current basic_string object.
             * @param p A pointer to the character sequence to append.
            */
            constexpr _basic_string_type& operator+=(const_pointer p)
            {
                return this->append(p);
            }
            /**
             * Overloaded operator+=. This operator appends another basic_string type onto the end 
             * of the current basic_string object.
             * @param s The basic_string object to append.
            */
            constexpr _basic_string_type& operator+=(const _basic_string_type& s)
            {
                return this->append(s._internalString);
            }
            /**
             * Overloaded operator+=. This operator appends a character onto the end of the current basic_string object.
             * @param ch The character to append.
            */
            constexpr _basic_string_type& operator+=(const_reference ch)
            {
                return this->append(1, ch);
            }
            /**
             * Pushes a character onto the back of the current basic_string object.
             * @param ch The character to push.
            */
            constexpr void push_back(const_reference ch)
            {
                return this->append(1, ch);
            }
            /**
             * Erases the last element off the string.
            */
            constexpr void pop_back()
            {
                _terminate_and_update_length(_length - 1);
            }
            /**
             * Erases the character pointed to by pos.
             * @param pos An iterator pointing to the element to be erased.
            */
            constexpr iterator erase(iterator pos)
            {
                const difference_type dist = pos - this->begin();

                _check_exception(0, dist, "basic_string::erase: pos is out of bounds");
                _check_exception(dist, _length, "basic_string::erase: pos is out of bounds");
                
                if (pos == this->end() - 1)
                    _terminate_and_update_length(_length - 1);
                else
                    _move_string(pos.base(), pos.base() + 1, _length - dist - 1);

                return iterator(_internalString + dist);
            }
            /**
             * Erases the characters in the range [first, last).
             * @param first An iterator to the start of the sequence to erase.
             * @param last An iterator to the end of the sequence to erase.
            */
            constexpr iterator erase(iterator first, iterator last)
            {
                const difference_type len = last - first;
                const difference_type dist_from_last_to_begin = last - this->begin();
                const difference_type dist_from_first_to_begin = first - this->begin();

                _check_exception(0, dist_from_first_to_begin, "basic_string::erase: first is out of bounds");
                _check_exception(0, dist_from_last_to_begin, "basic_string::erase: last is out of bounds");
                _check_exception(size_type(dist_from_first_to_begin), _length, "basic_string::erase: first is out of bounds");
                _check_exception(size_type(dist_from_last_to_begin), _length + 1, "basic_string::erase: last is out of bounds");

                if (len)
                {
                    if (last == this->end())
                        _terminate_and_update_length(size_type(dist_from_first_to_begin));
                    else
                        _move_string(first.base(), last.base(), _length - dist_from_first_to_begin - len);
                }
                return iterator(_internalString + dist_from_first_to_begin);
            }
            /**
             * Erases the first count characters starting from index pos.
             * @param pos The index from where to start erasing.
             * @param count The number of characters to erase.
            */
            constexpr _basic_string_type& erase(size_type pos = 0, size_type count = npos)
            {
                _check_exception(pos, _length, "basic_string::erase: pos is out of bounds");

                if (count)
                {
                    if (pos + count >= _length || count == npos)
                        _terminate_and_update_length(pos);
                    else
                        _move_string(_internalString + pos, _internalString + pos + count, _length - pos - count);
                }
                return *this;
            }
            /**
             * Compares this basic_string with the character sequence pointed to by p.
             * @param p A pointer to the character sequence to compare against.
            */
            constexpr int compare(const_pointer p) const noexcept
            {
                return this->compare(0, _length, p);
            }
            /**
             * Compares the substring [pos, pos + count) of the current basic_string object with the 
             * character sequence pointed to by p.
             * @param pos The starting index of the substring of the current basic_string object.
             * @param count The number of characters after pos to compare.
             * @param p A pointer to the character sequence to compare against.
            */
            constexpr int compare(size_type pos, size_type count, const_pointer p) const noexcept
            {
                return this->compare(pos, count, p, traits_type::length(p));
            }
            /**
             * Compares the substring [pos, pos + count1) of the current basic_string object with the 
             * first count2 elements in the character sequence pointed to by p.
             * @param pos The starting index of the substring of the current basic_string object.
             * @param count1 The number of characters after pos to compare.
             * @param p A pointer to the character sequence to compare against.
             * @param count2 The number of characters in p to compare.
            */
            constexpr int compare(size_type pos, size_type count1, const_pointer p, size_type count2) const noexcept
            {
                if (count1 > _length - pos)
                    count1 = _length - pos;
                
                int result = traits_type::compare(_internalString + pos, p, std_copy::min(count1, count2));
                if (result != 0 || count1 == count2)
                    return result;
                if (count1 < count2)
                    return -1;
                return 1;
            }
            /**
             * Compares two basic_string types.
             * @param s The basic_string object getting compared to *this.
            */
            constexpr int compare(const _basic_string_type& s) const noexcept
            {
                return this->compare(0, _length, s);
            }
            /**
             * Compares the substring [pos, pos + count) of the current basic_string object with 
             * another basic_string object.
             * @param pos The starting index of the substring of the current basic_string object.
             * @param count The number of characters after pos to compare.
             * @param s The basic_string object to compare against.
            */
            constexpr int compare(size_type pos, size_type count, const _basic_string_type& s)
            {
                return this->compare(pos, count, s, 0, s._length);
            }
            /**
             * Compares the substring [pos1, pos1 + count1) of the current basic_string object with 
             * the substring [pos2, count2) of another basic_string object.
             * @param pos1 The starting index of the substring of the current basic_string object.
             * @param count1 The number of characters after pos1 to compare.
             * @param s The basic_string object to compare against.
             * @param pos2 The starting index of the substring of s.
             * @param count2 The number of characters after pos2 in s to compare.
            */
            constexpr int compare(size_type pos1, size_type count1, const _basic_string_type& s, size_type pos2, size_type count2)
            {
                if (count1 > _length - pos1)
                    count1 = _length - pos1;
                if (count2 > s._length - pos2)
                    count2 = s._length - pos2;
                
                int result = traits_type::compare(_internalString + pos1, s._internalString + pos2, std_copy::min(count1, count2));
                if (result != 0 || count1 == count2)
                    return result;
                if (count1 < count2)
                    return -1;
                return 1;
            }
            /**
             * Checks if *this starts with a character ch. The behavior is undefined 
             * if *this is empty.
             * @param ch The character to check for at the beginning of the current basic_string object.
            */
            constexpr bool starts_with(value_type ch) const noexcept
            {
                return traits_type::eq(_internalString[0], ch);
            }
            /**
             * Checks if *this starts with the null-terminated character sequence p.
             * @param p The character sequence to check for at the beginning of the current basic_string object.
            */
            constexpr bool starts_with(const_pointer p) const noexcept
            {
                const size_type len = traits_type::length(p);
                if (len > _length)
                    return false;
                
                for (size_type i = 0; i < len; i++)
                    if (!traits_type::eq(_internalString[i], p[i]))
                        return false;
                return true;
            }
            /**
             * Checks if *this starts with the basic_string object s.
             * @param s The basic_string object to check for at the beginning of the current basic_string object.
            */
            constexpr bool starts_with(const _basic_string_type& s) const noexcept
            {
                if (s._length > _length)
                    return false;
                
                for (size_type i = 0; i < s._length; i++)
                    if (!traits_type::eq(_internalString[i], s._internalString[i]))
                        return false;
                return true;
            }
            /**
             * Checks if *this starts with the elements in the range 
             * [first, last).
             * @param first An iterator to the start of the sequence.
             * @param last An iterator to the end of the sequence.
            */
            template <class InputIterator>
            constexpr bool starts_with(InputIterator first, InputIterator last) const noexcept
            {
                const difference_type dist = std_copy::distance(first, last);
                if (dist > _length)
                    return false;
                
                size_type i = 0;
                while (first != last)
                {
                    if (!traits_type::eq(*first, _internalString[i]))
                        return false;
                    i++;
                    first++;
                }
                return true;
            }
            /**
             * Check if *this ends with ch.
             * @param ch The character to check for at the end of the current basic_string object.
            */
            constexpr bool ends_with(const_reference ch) const noexcept
            {
                return traits_type::eq(this->back(), ch);
            }
            /**
             * Check if *this ends with p.
             * @param p A null-terminated character sequence to check for at the end of the current basic_string object.
            */
            constexpr bool ends_with(pointer p) const noexcept
            {
                const size_type len = traits_type::length(p);
                return (_length > len) && (this->compare(_length - len, len, p) == 0);
            }
            /**
             * Checks if *this ends with s.
             * @param s A basic_string object to check for at the end of the current basic_string object.
            */
            constexpr bool ends_with(const _basic_string_type& s) const noexcept
            {
                if (s._length > _length)
                    return false;
                
                for (size_type i = 1; i <= s._length; i++)
                    if (!traits_type::eq(_internalString[_length - i], s._internalString[s._length - i]))
                        return false;
                return true;
            }
            /**
             * Checks if *this ends with the elements in the range [first, last).
             * @param first An iterator to the start of the range.
             * @param second An iterator to the end of the range.
            */
            template <class InputIterator>
            constexpr bool ends_with(InputIterator first, InputIterator last) const noexcept
            {
                const difference_type dist = std_copy::distance(first, last);
                if (dist > _length)
                    return false;
                
                size_type i = 1;
                while ((--last) != first)
                {
                    if (!traits_type::eq(*last, _internalString[_length - i]))
                        return false;
                    i++;
                }
                return true;
            }
            /**
             * Checks if *this contains another basic_string object.
             * @param s The basic_string object to find.
            */
            constexpr bool contains(const _basic_string_type& s) const noexcept
            {
                return this->find(s) != npos;
            }
            /**
             * Checks if *this contains a character sequence p.
             * @param p The character sequence to look for.
            */
            constexpr bool contains(const_pointer p) const noexcept
            {
                return this->find(p) != npos;
            }
            /**
             * Checks if *this contains a character ch.
             * @param ch The character to search for.
            */
            constexpr bool contains(const_reference ch, size_type pos = 0) const noexcept
            {
                return this->find(ch, pos) != npos;
            }
            /**
             * Resizes a string to contain count elements. Any additional elements 
             * (if any) are initialized to ch.
             * @param count The number of elements to resize *this to.
             * @param ch The character assigned to any additional elements.
            */
            constexpr void resize(size_type count, const_reference ch)
            {
                if (count < _length)
                    _realloc(0, count);
                else
                {
                    _realloc(count / _capacity, _length);
                    traits_type::assign(_internalString + _length, count - _length, ch);
                }
                _terminate_and_update_length(count);
            }
            /**
             * Resizes a string to contain count elements.
             * @param count The number of elements to resize *this to.
            */
            constexpr void resize(size_type count)
            {
                return this->resize(count, value_type());
            }
            /**
             * Replaces the range [first, last) of the current basic_string object with str.
             * @param first An iterator pointing to the start of the range to erase.
             * @param last An iterator pointing to the end of the range to erase.
             * @param str The basic_string object to replace the range.
            */
            constexpr _basic_string_type& replace(iterator first, iterator last, const _basic_string_type& str)
            {
                return this->replace(first - this->begin(), last - first, str);
            }
            /**
             * Replaces the substring [pos, pos + count) of the current basic_string object with str.
             * @param pos The index from which to start replacing.
             * @param count The number of characters after pos to replace.
             * @param str The basic_string object to replace the substring with.
            */
            constexpr _basic_string_type& replace(size_type pos, size_type count, const _basic_string_type& str)
            {
                _check_exception(pos, _length, "basic_string::replace: pos is out of range");

                if (count > _length - pos)
                    count = _length - pos;

                if (count == 0)
                    return this->erase(pos, count);
                
                if (count == str._length)
                    traits_type::move(_internalString + pos, str._internalString, count);
                else if (str._length < count)
                {
                    traits_type::move(_internalString + pos, str._internalString, str._length);
                    traits_type::move(_internalString + pos + str._length, _internalString + pos + count, _length - pos - count);
                    _terminate_and_update_length(_length - count + str._length);
                }
                else
                {
                    if (_length - count + str._length > _capacity)
                    {
                        _capacity *= _calculate_smallest_power_of_two_greater_than((_length - count + str._length) / _capacity);
                        pointer temp = _internalString;
                        _internalString = allocator_type::allocate(_capacity);
                        traits_type::move(_internalString, temp, pos);
                        traits_type::move(_internalString + pos, str._internalString, str._length);
                        traits_type::move(_internalString + pos + str._length, temp + pos + count, _length - pos - count);
                    }
                    else
                    {
                        std_copy::move_backward(_internalString + pos + count, _internalString + _length, _internalString + _length - count + str._length);
                        traits_type::move(_internalString + pos, str._internalString, str._length);
                    }
                    _terminate_and_update_length(_length - count + str._length);
                }
                return *this;
            }
            /**
             * Replaces the substring [pos1, pos1 + count1) of the current basic_string object with the substring [pos2, pos2 + count2) 
             * of str.
             * @param pos1 The index from which to start replacing.
             * @param count1 The number of characters after pos to replace.
             * @param str The basic_string object to replace the substring with.
             * @param pos2 The index of str to start replacing the substring [pos, pos + count) in *this.
             * @param count2 The number of characters after pos2 to start replacing the substring [pos, pos + count) in *this.
            */
            constexpr _basic_string_type& replace(size_type pos1, size_type count1, const _basic_string_type& str, size_type pos2, size_type count2)
            {
                _check_exception(pos1, str._length, "basic_string::replace: pos1 > str.size()");
                _check_exception(pos2, str._length, "basic_string::replace: pos2 > str.size()");

                count1 = (count1 > _length - pos1) ? _length - pos1 : count1;
                count2 = (count2 > str._length - pos2) ? str._length - pos2 : count2;

                return this->replace(pos1, count1, str._internalString + pos2, str._internalString + pos2 + count2);
            }
            /**
             * Replaces the range [first, last) of the current basic_string object with s.
             * @param first An iterator pointing to the start of the range to erase.
             * @param last An iterator pointing to the end of the range to erase.
             * @param s The character sequence to replace the range.
            */
            constexpr _basic_string_type& replace(iterator first, iterator last, pointer s)
            {
                return this->replace(first - this->begin(), last - first, s);
            }
            /**
             * Replaces the substring [pos, pos + count) of the current basic_string object with s.
             * @param pos The index from which to start replacing.
             * @param count The number of characters after pos to replace.
             * @param s The character sequence to replace the range.
            */
            constexpr _basic_string_type& replace(size_type pos, size_type count, pointer s)
            {
                _check_exception(pos, _length, "basic_string::replace: pos > size()");
                
                const size_type len = traits_type::length(s);
                if (count > _length - pos)
                    count = _length - pos;

                if (count == 0)
                    return this->erase(pos, count);
                
                if (count == len)
                    traits_type::move(_internalString + pos, s, count);
                else if (len < count)
                {
                    traits_type::move(_internalString + pos, s, len);
                    traits_type::move(_internalString + pos + len, _internalString + pos + count, _length - pos - count);
                    _terminate_and_update_length(_length - count + len);
                }
                else
                {
                    if (_length - count + len > _capacity)
                    {
                        _capacity *= _calculate_smallest_power_of_two_greater_than((_length - count + len) / _capacity);
                        pointer temp = _internalString;
                        _internalString = allocator_type::allocate(_capacity);
                        traits_type::move(_internalString, temp, pos);
                        traits_type::move(_internalString + pos, s, len);
                        traits_type::move(_internalString + pos + len, temp + pos + count, _length - pos - count);
                    }
                    else
                    {
                        std_copy::move_backward(_internalString + pos + count, _internalString + _length, _internalString + _length - count + len);
                        traits_type::move(_internalString + pos, s, len);
                    }
                    _terminate_and_update_length(_length - count + len);
                }
                return *this;
            }
            /**
             * Replaces the substring [pos, pos + count1) of the current basic_string object with the first count2 
             * characters of s.
             * @param pos The index from which to start replacing.
             * @param count1 The number of characters after pos to replace.
             * @param s The character sequence to replace the range.
             * @param count2 The number of characters in s to replace with.
            */
            constexpr _basic_string_type& replace(size_type pos, size_type count1, pointer s, size_type count2)
            {
                _check_exception(pos, _length, "basic_string::replace: pos > size()");

                const size_type len = traits_type::length(s);
                if (count1 > _length - pos)
                    count1 = _length - pos;
                count2 = (count2 > len) ? len : count2;

                return this->replace(this->begin() + pos, this->begin() + pos + count1, s, s + count2);
            }
            /**
             * Replaces the range [first, last) of the current basic_string object with the first count2 
             * characters of s.
             * @param first An iterator to the start of the range to replace.
             * @param last An iterator to the end of the range to replace.
             * @param s The character sequence to replace the range.
             * @param count2 The number of characters in s to replace with.
            */
            constexpr _basic_string_type& replace(iterator first, iterator last, pointer s, size_type count2)
            {
                return this->replace(first, last, s, s + count2);
            }
            /**
             * Replaces the range [first, last) of the current basic_string object with the range [first2, last2).
             * @param first An iterator pointing to the start of the range to erase.
             * @param last An iterator pointing to the end of the range to erase.
             * @param first2 An iterator to the start of the range to replace [first, last).
             * @param last2 An iterator to the end of the range to replace [first, last).
            */
            template <class InputIterator>
            constexpr _basic_string_type& replace(iterator first, iterator last, InputIterator first2, InputIterator last2)
        #if __cplusplus > 201703L
            requires input_iterator<InputIterator>
        #endif
            {
                return this->replace(first - this->begin(), last - first, first2, last2);
            }
            /**
             * Replaces the substring [pos, pos + count) of the current basic_string object with the range [first2, last2).
             * @param pos The index from which to start replacing.
             * @param count The number of characters after pos to replace.
             * @param first An iterator to the start of the range to replace [first, last).
             * @param last An iterator to the end of the range to replace [first, last).
            */
            template <class InputIterator>
            constexpr _basic_string_type& replace(size_type pos, size_type count, InputIterator first, InputIterator last)
        #if __cplusplus > 201703L
            requires input_iterator<InputIterator>
        #endif
            {
                _check_exception(pos, _length, "basic_string::replace: pos > size()");

                const size_type len = std_copy::distance(first, last);
                if (count > _length - pos)
                    count = _length - pos;

                if (count == 0)
                    return this->erase(pos, count);
                
                if (count == len)
                    traits_type::move(_internalString + pos, first, count);
                else if (len < count)
                {
                    traits_type::move(_internalString + pos, first, len);
                    traits_type::move(_internalString + pos + len, _internalString + pos + count, _length - pos - count);
                    _terminate_and_update_length(_length - count + len);
                }
                else
                {
                    if (_length - count + len > _capacity)
                    {
                        _capacity *= _calculate_smallest_power_of_two_greater_than((_length - count + len) / _capacity);
                        pointer temp = _internalString;
                        _internalString = allocator_type::allocate(_capacity);
                        traits_type::move(_internalString, temp, pos);
                        traits_type::move(_internalString + pos, first, len);
                        traits_type::move(_internalString + pos + len, temp + pos + count, _length - pos - count);
                    }
                    else
                    {
                        std_copy::move_backward(_internalString + pos + count, _internalString + _length, _internalString + _length - count + len);
                        traits_type::move(_internalString + pos, first, len);
                    }
                    _terminate_and_update_length(_length - count + len);
                }
                return *this;
            }
            /**
             * Replaces the substring [pos, pos + count) with count2 elements of value ch.
             * @param pos The index to start replacing from.
             * @param count The number of characters after pos to replace.
             * @param count2 The number of elements to replace the range with.
             * @param ch The value of each element.
            */
            constexpr _basic_string_type& replace(size_type pos, size_type count, size_type count2, const_reference ch)
            {
                _check_exception(pos, _length, "basic_string::replace: pos > size()");
                if (count > _length - pos)
                    count = _length - pos;
    
                if (count == count2)
                    traits_type::assign(_internalString + pos, count2, ch);
                else if (count2 < count)
                {
                    traits_type::assign(_internalString + pos, count2, ch);
                    traits_type::move(_internalString + pos + count2, _internalString + pos + count, _length - pos - count);
                    _terminate_and_update_length(_length - count + count2);
                }
                else
                {
                    _capacity *= _calculate_smallest_power_of_two_greater_than((_length - count + count2) / _capacity);
                    pointer temp = _internalString;
                    _internalString = allocator_type::allocate(_capacity);
                    traits_type::move(_internalString, temp, pos);
                    traits_type::assign(_internalString + pos, count2, ch);
                    traits_type::move(_internalString + pos + count2, temp + pos + count, _length - pos - count);
                    _terminate_and_update_length(_length - count + count2);
                }
                return *this;
            }
            /**
             * Replaces the range [first, last) with count elements of value ch.
             * @param first An iterator pointing to the start of the range to erase.
             * @param last An iterator pointing to the end of the range to erase.
             * @param count The number of elements to replace the range with.
             * @param ch The value of each element.
            */
            constexpr _basic_string_type& replace(iterator first, iterator last, size_type count, const_reference ch)
            {
                return this->replace(first - this->begin(), last - first, count, ch);
            }
            /**
             * Returns the substring [pos, pos + count) of the current basic_string object.
             * @param pos The index to start getting the characters from.
             * @param count The number of characters after pos to put into the substring.
            */
            _basic_string_type substr(size_type pos, size_type count = npos) const
            {
                _check_exception(pos, _length, "basic_string::substr: pos > size()");

                if (pos + count > _length)
                    count = _length - pos;

                return _basic_string_type(*this, pos, count);
            }
            /**
             * Copies the substring [pos, pos + count) of the current basic_string object to dest;
             * @param dest The character sequence to copy to.
             * @param pos The position from which to start copying.
             * @param count The number of characters to copy.
            */
            size_type copy(pointer dest, size_type pos = 0, size_type count = npos)
            {
                _check_exception(pos, _length, "basic_string::copy: pos > size()");

                if (count == npos || pos + count > _length)
                    count = _length - pos;

                traits_type::copy(dest, _internalString + pos, count);
                return count;
            }
            /**
             * Swaps the contents of two basic_string objects.
             * @param other The basic_string object to swap contents with.
            */
            constexpr void swap(_basic_string_type& other)
            {
                _basic_string_type temp(*this);
                

                std_copy::swap(_length, other._length);
                std_copy::swap(_capacity, other._capacity);
            }

            /**
             * Returns a std::size_t value indicating the index at which the character 
             * ch first occurrs in *this.
             * @param ch The character to search for.
             * @param pos The index from where to start searching. Default value is 0.
             * @param count The number of characters after pos to search in.
            */
            constexpr size_type find(const_reference ch, size_type pos, size_type count) const
            {
                return (traits_type::find(_internalString + pos, count, ch) - _internalString);
            }
            /**
             * Returns a std::size_t value indicating the index at which the character 
             * ch first occurrs in *this.
             * @param ch The character to search for.
             * @param pos The index from where to start searching. Default value is 0.
            */
            constexpr size_type find(const_reference ch, size_type pos = 0) const
            {
                return this->find(ch, pos, _length);
            }
            /**
             * Returns a std::size_t value indicating the index at which the substring 
             * p first occurs in *this.
             * @param p The substring to search for.
             * @param pos The index from which to start searching for the substring.
            */
            constexpr size_type find(const_pointer p, size_type pos = 0) const
            {
                return this->find(p, pos, traits_type::length(p));
            }
            /**
             * Returns a std::size_t value indicating the index at which the first count 
             * characters in the character sequence p first occurs in the substring [pos, size()) 
             * of the current basic_string object.
             * @param p The character sequence to find.
             * @param pos The index from which to start searching for p in *this.
             * @param count The number of characters in p to look for.
            */
            constexpr size_type find(const_pointer p, size_type pos, size_type count) const
            {
                pointer where = search(_internalString + pos, _internalString + _length, p, p + count);
                if (where == _internalString + _length)
                    return npos;
                return (where - _internalString);
            }
            /**
             * Returns a std::size_t value indicating the value at which the first count 
             * characters in the basic_string object s first occurs in the substring 
             * [pos, size()) of the current basic_string object.
             * @param s The basic_string object to search for.
             * @param pos The position from where to start searching.
             * @param count The number of characters in s to search for.
            */
            constexpr size_type find(const _basic_string_type& s, size_type pos, size_type count) const
            {
                return this->find(s._internalString, pos, count);
            }
            /**
             * Returns a std::size_t value indicating the value at which the basic_string 
             * object s first occurs in the substring [pos, size()) of the current basic_string object.
             * @param s The basic_string object to search for.
             * @param pos The position from where to start searching.
            */
            constexpr size_type find(const _basic_string_type& s, size_type pos = 0) const noexcept
            {
                return this->find(s._internalString, pos, s._length);
            }
            /**
             * Returns a std::size_t value indicating the value at which the range [first, last) 
             * first occurs in the substring [pos, size()) of the current basic_string object.
             * @param first An iterator to the start of the range.
             * @param last An iterator to the end of the range.
             * @param pos The position in *this from where to start searching.
            */
            template <class InputIterator>
            constexpr size_type find(InputIterator first, InputIterator last, size_type pos = 0) const noexcept
        #if __cplusplus > 201703L
            requires input_iterator<InputIterator>
        #endif
            {
                pointer where = std_copy::search(_internalString + pos, _internalString + _length, first, last);
                if (where == _internalString + _length)
                    return npos;
                return (where - _internalString);
            }
            /**
             * Searches for the first n characters of str from the back of the current basic_string object.
             * @param str The basic_string object to search for in *this.
             * @param n The number of characters in str to search for.
             * @param pos The position in *this to start searching backwards from.
            */
            constexpr size_type rfind(const _basic_string_type& str, size_type n, size_type pos) const noexcept
            {
                if (pos >= _length)
                    pos = _length - 1;
                
                size_type indexSubstrEnd = npos;
                size_type indexInSubstr = str._length - 1;
                for (size_type i = pos, increment = 0; ; i--)
                {
                    if (!traits_type::eq(_internalString[i], str._internalString[indexInSubstr]))
                    {
                        indexInSubstr = str._length - 1;
                        indexSubstrEnd = npos;
                        increment = 0;
                    }
                    if (traits_type::eq(_internalString[i], str._internalString[indexInSubstr]))
                    {
                        indexInSubstr--;
                        indexSubstrEnd = (indexSubstrEnd == npos) ? i : indexSubstrEnd;
                        increment++;
                        if (increment == n)
                        {
                            indexSubstrEnd -= str._length - 1;
                            break;
                        }
                    }
                    if (i == 0)
                        break;
                }
                return indexSubstrEnd;
            }
            /**
             * Searches for str from the back of the current basic_string object.
             * @param str The basic_string object to search for in *this.
             * @param pos The position in *this to start searching backwards from.
            */
            constexpr size_type rfind(const _basic_string_type& str, size_type pos = npos) const noexcept
            {
                return this->rfind(str, str._length, pos);
            }
            /**
             * Searches for the first n characters of str from the back of the current basic_string object.
             * @param str The character sequence to search for in *this.
             * @param n The number of characters in str to search for.
             * @param pos The position in *this to start searching backwards from.
            */
            constexpr size_type rfind(pointer str, size_type n, size_type pos) const noexcept
            {
                return this->rfind(_basic_string_type(str), n, pos);
            }
            /**
             * Searches for p from the back of the current basic_string object.
             * @param p A character sequence to search for in *this.
             * @param pos The position in *this to start searching backwards from.
            */
            constexpr size_type rfind(pointer p, size_type pos = npos) const noexcept
            {
                return this->rfind(p, traits_type::length(p), pos);
            }
            /**
             * Searches for ch from the back of the current basic_string object.
             * @param ch The character to search for.
             * @param pos The position to start searching backwards from.
            */
            constexpr size_type rfind(const_reference ch, size_type pos = npos) const noexcept
            {
                if (pos > _length)
                    pos = _length - 1;

                while (pos-- > 0)
                {
                    if (traits_type::eq(_internalString[pos], ch))
                        return pos;
                }
                return npos;
            }
            /**
             * Searches for the first occurrence of any of the characters in the character 
             * sequence p in *this.
             * @param p The character sequence.
             * @param pos The position from which to start searching.
            */
            constexpr size_type find_first_of(const_pointer p, size_type pos = 0)
            {
                return this->find_first_of(p, pos, traits_type::length(p));
            }
            /**
             * Searches for the first occurrence of any of the characters in the first count  
             * characters from the character sequence p in *this.
             * @param p The character sequence.
             * @param pos The position from which to start searching.
             * @param count The number of charcters in p that count as "valid".
            */
            constexpr size_type find_first_of(const_pointer p, size_type pos, size_type count)
            {
                _check_exception(pos, _length, "basic_string::find_first_of: pos > size()");
                
                pointer where = std_copy::find_first_of(_internalString + pos, _internalString + _length, p, p + count);
                if (where == _internalString + _length)
                    return npos;
                return where - _internalString;
            }
            /**
             * Searches for the first occurrence of any of the characters in the 
             * basic_string object p in *this.
             * @param p The basic_string object.
             * @param pos The position from which to start searching.
            */
            constexpr size_type find_first_of(const _basic_string_type& p, size_type pos = 0)
            {
                return this->find_first_of(p._internalString, pos, p._length);
            }
            /**
             * Searches for the first occurrence of ch in *this.
             * @param ch The character to search for.
             * @param pos The position to start searching from.
            */
            constexpr size_type find_first_of(const_reference ch, size_type pos = 0)
            {
                _check_exception(pos, _length, "basic_string::find_first_of: pos > size()");
                
                pointer where = std_copy::find(_internalString + pos, this->end().base(), ch);
                if (where == _internalString + _length)
                    return npos;
                return where - _internalString;
            }
            /**
             * Searches for the first occurrence of any character not in the 
             * character sequence p in *this.
             * @param p The character sequence.
             * @param pos The position from which to start searching.
            */
            constexpr size_type find_first_not_of(const_pointer p, size_type pos = 0)
            {
                return this->find_first_not_of(p, pos, traits_type::length(p));
            }
            /**
             * Searches for the first occurrence of any character not in the first count characters 
             * from character sequence p in *this.
             * @param p The character sequence.
             * @param pos The position from which to start searching.
             * @param count The number of characters from p considered "invalid".
            */
            constexpr size_type find_first_not_of(const_pointer p, size_type pos, size_type count)
            {
                _check_exception(pos, _length, "basic_string::find_first_not_of: pos > size()");
                
                for (size_type i = pos; i < _length; i++)
                {
                    pointer where = std_copy::find(p, p + count, _internalString[i]);
                    if (where == p + count)
                        return i;
                }
                return npos;
            }
            /**
             * Searches for the first occurrence of any character not in the 
             * basic_string object p in *this.
             * @param p The basic_string object.
             * @param pos The position from which to start searching.
            */
            constexpr size_type find_first_not_of(const _basic_string_type& p, size_type pos = 0)
            {
                return this->find_first_not_of(p._internalString, pos, p._length);
            }
            /**
             * Searches for first occurrence of any character that is not ch in 
             * *this.
             * @param ch The character.
             * @param pos The position to start searching from.
            */
            constexpr size_type find_first_not_of(const_reference ch, size_type pos = 0)
            {
                _check_exception(pos, _length, "basic_string::find_first_not_of: pos > size()");
                
                for (size_type i = pos; i < _length; i++)
                {
                    if (!traits_type::eq(_internalString[i], ch))
                        return i;
                }
                return npos;
            }
            /**
             * Searches for the last occurrence of any of the characters from the first count 
             * characters from the character sequence p.
             * @param p The character sequence.
             * @param pos The position to start searching backwards from.
             * @param count The number of characters from count considered "valid".
            */
            constexpr size_type find_last_of(const_pointer p, size_type pos, size_type count)
            {
                _check_exception(pos, _length, "basic_string::find_last_of: pos > size()");

                for (size_type i = pos; i < _length; i++)
                {
                    if (std_copy::find(p, p + count, _internalString[i]) != p + count)
                        return i;
                }
                return npos;
            }
            /**
             * Searches for the last occurrence of any of the characters from the character 
             * sequence p.
             * @param p The character sequence.
             * @param pos The position to start searching backwards from.
            */
            constexpr size_type find_last_of(const_pointer p, size_type pos = npos)
            {
                if (pos >= _length)
                    pos = _length - 1;

                return this->find_last_of(p, pos, traits_type::length(p));
            }
            /**
             * Searches for the last occurrence of any of the characters from the 
             * basic_string object p.
             * @param p The character sequence.
             * @param pos The position to start searching backwards from.
            */
            constexpr size_type find_last_of(const _basic_string_type& p, size_type pos = npos)
            {
                if (pos >= _length)
                    pos = _length - 1;

                return this->find_last_of(p._internalString, pos, p._length);
            }
            /**
             * Searches for the last occurrence of ch in *this.
             * @param ch The character to search for.
             * @param pos The position to start searching from.
            */
            constexpr size_type find_last_of(const_reference ch, size_type pos = npos)
            {
                if (pos >= _length)
                    pos = _length - 1;
                
                while (pos-- > 0)
                {
                    if (traits_type::eq(_internalString[pos], ch))
                        return pos;
                }
                return npos;
            }
            /**
             * Searches for the last occurrence of any character not from the first count 
             * characters from the character sequence p.
             * @param p The character sequence.
             * @param pos The position to start searching backwards from.
             * @param count The number of characters from count considered "valid".
            */
            constexpr size_type find_last_not_of(const_pointer p, size_type pos, size_type count)
            {
                _check_exception(pos, _length, "basic_string::find_last_not_of: pos > size()");

                for (size_type i = pos; i < _length; i++)
                {
                    if (std_copy::find(p, p + count, _internalString[i]) == p + count)
                        return i;
                }
                return npos;
            }
            /**
             * Searches for the last occurrence of any character not from the character 
             * sequence p.
             * @param p The character sequence.
             * @param pos The position to start searching backwards from.
            */
            constexpr size_type find_last_not_of(const_pointer p, size_type pos = npos)
            {
                if (pos >= _length)
                    pos = _length - 1;

                return this->find_last_not_of(p, pos, traits_type::length(p));
            }
            /**
             * Searches for the last occurrence of any character not from the 
             * basic_string object p.
             * @param p The character sequence.
             * @param pos The position to start searching backwards from.
            */
            constexpr size_type find_last_not_of(const _basic_string_type& p, size_type pos = npos)
            {
                if (pos >= _length)
                    pos = _length - 1;

                return this->find_last_not_of(p._internalString, pos, p._length);
            }
            /**
             * Searches for the last occurrence of ch in *this.
             * @param ch The character to search for.
             * @param pos The position to start searching from.
             * @returns The index of the last occurrence of ch.
            */
            constexpr size_type find_last_not_of(const_reference ch, size_type pos = npos)
            {
                if (pos >= _length)
                    pos = _length - 1;
                
                while (pos-- > 0)
                {
                    if (!traits_type::eq(_internalString[pos], ch))
                        return pos;
                }
                return npos;
            }
            /**
             * Converts all the alphabetic characters to uppercase if they are lowercase.
            */
            constexpr _basic_string_type& to_upper()
            {
                std_copy::for_each(_internalString, _internalString + _length, _helper::_to_upper);
                return *this;
            }
            /**
             * Converts all the alphabetic characters to lowercase if they are uppercase.
            */
            constexpr _basic_string_type& to_lower()
            {
                std_copy::for_each(_internalString, _internalString + _length, _helper::_to_lower);
                return *this;
            }
            /**
             * Removes all the occurrences of a character ch.
             * @param ch The character to remove.
            */
            constexpr size_type remove(const_reference ch)
            {
                size_type numberOfOccurrences = 0;
                #if __cplusplus >= 201103L

                    pointer upTo = std_copy::remove(_internalString, _internalString + _length, ch);
                    numberOfOccurrences = this->end() - upTo;
                    _terminate_and_update_length(_length - numberOfOccurrences);

                #else

                    for (size_type i = 0, where = 0; i < _length; i++)
                    {
                        if (!traits_type::eq(_internalString[i], ch))
                        {
                            traits_type::assign(_internalString[where], _internalString[i]);
                            where++;
                        }
                        else
                            numberOfOccurrences++;
                    }
                    _terminate_and_update_length(_length - numberOfOccurrences);

                #endif

                return numberOfOccurrences;
            }
            /**
             * Removes all the occurrences of characters for which fn returns true.
             * @param fn The character to remove.
            */
            template <class Function>
            constexpr size_type remove_if(Function fn)
            {
                size_type numberOfOccurrences = 0;
                #if __cplusplus >= 201103L

                    pointer upTo = std_copy::remove_if(_internalString, _internalString + _length, fn);
                    numberOfOccurrences = size_type(this->end() - upTo);
                    _terminate_and_update_length(_length - numberOfOccurrences);

                #else

                    for (size_type i = 0, where = 0; i < _length; i++)
                    {
                        if (!fn(_internalString[i]))
                        {
                            traits_type::assign(_internalString[where], _internalString[i]);
                            where++;
                        }
                        else
                            numberOfOccurrences++;
                    }
                    _terminate_and_update_length(_length - numberOfOccurrences);

                #endif

                return numberOfOccurrences;
            }
    };
    /**
     * Appends two basic_string objects.
     * @param first The first basic_string object.
     * @param second The second basic_string object.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(const basic_string<CharT, Traits, Alloc>& first,
                                                 const basic_string<CharT, Traits, Alloc>& second)
    {
        basic_string<CharT, Traits, Alloc> ret(first);
        ret += second;
        return ret;
    }
    /**
     * Appends a character sequence onto a basic_string object.
     * @param first The basic_string object.
     * @param second The character sequence to append.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(const basic_string<CharT, Traits, Alloc>& first,
                                                 const CharT* second)
    {
        basic_string<CharT, Traits, Alloc> ret(first);
        ret += second;
        return ret;
    }
    /**
     * Appends a character onto a basic_string object.
     * @param first The basic_string object.
     * @param ch The character to append.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(const basic_string<CharT, Traits, Alloc>& first,
                                                           CharT ch)
    {
        basic_string<CharT, Traits, Alloc> ret(first);
        ret += ch;
        return ret;
    }
    /**
     * Appends a basic_string object onto a character sequence.
     * @param first The character sequence.
     * @param second The basic_string object to append.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(const CharT* first,
                                                           const basic_string<CharT, Traits, Alloc>& second)
    {
        basic_string<CharT, Traits, Alloc> ret(first);
        ret += second;
        return ret;
    }
    /**
     * Appends a basic_string object onto a basic_string object.
     * @param first The character.
     * @param second The basic_string object.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(CharT first,
                                                           const basic_string<CharT, Traits, Alloc>& second)
    {
        basic_string<CharT, Traits, Alloc> ret(1, first);
        ret += second;
        return ret;
    }
    /**
     * Appends a rvalue reference'd basic_string object onto another rvalue-reference'd 
     * basic_string object.
     * @param first The first rvalue reference'd basic_string object.
     * @param second The second rvalue reference'd basic_string object.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(basic_string<CharT, Traits, Alloc>&& first,
                                                           basic_string<CharT, Traits, Alloc>&& second)
    {
        return first.append(second);
    }
    /**
     * Appends a character sequence onto a rvalue-reference'd basic_string object.
     * @param first The rvalue-reference'd basic_string object.
     * @param second The character sequence to append.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(basic_string<CharT, Traits, Alloc>&& first,
                                                           const CharT* second)
    {
        return first.append(second);
    }
    /**
     * Appends a character onto a rvalue-reference'd basic_string object.
     * @param first The rvalue-reference'd basic_string object.
     * @param ch The character to append.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(basic_string<CharT, Traits, Alloc>&& first,
                                                           CharT ch)
    {
        return first.append(1, ch);
    }
    /**
     * Appends a rvalue reference'd basic_string object onto a basic_string object.
     * @param first The basic_string object.
     * @param second The rvalue reference'd basic_string object.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(const basic_string<CharT, Traits, Alloc>& first,
                                                           basic_string<CharT, Traits, Alloc>&& second)
    {
        basic_string<CharT, Traits, Alloc> ret(first);
        ret.append(move(second));
        return ret;
    }
    /**
     * Appends a basic_string object onto a rvalue reference'd basic_string object.
     * @param first The rvalue reference'd basic_string object.
     * @param second The basic_string object.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(basic_string<CharT, Traits, Alloc>&& first,
                                                           const basic_string<CharT, Traits, Alloc>& second)
    {
        return first.append(second);
    }
    /**
     * Appends a rvalue-reference'd basic_string object onto a character sequence.
     * @param first The character sequence.
     * @param second The rvalue-reference'd basic_string object;
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(const CharT* first,
                                                           basic_string<CharT, Traits, Alloc>&& second)
    {
        basic_string<CharT, Traits, Alloc> ret(first);
        ret.append(move(second));
        return ret;
    }
    /**
     * Appends a rvalue-reference'd basic_string object onto a character.
     * @param first The character.
     * @param second The rvalue-reference'd basic_string object.
    */
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    constexpr basic_string<CharT, Traits, Alloc> operator+(CharT first,
                                                           basic_string<CharT, Traits, Alloc>&& second)
    {
        basic_string<CharT, Traits, Alloc> ret(1, first);
        ret.append(move(second));
        return ret;
    }

    /**
     * Gets the Nth element from str. N is a template parameter.
     * @param str The basic_string object from which to get the element.
    */
    template <std::size_t N, class CharT, class CharTraits = char_traits<CharT>, class Alloc = allocator<CharT>>
    CharT&& get(basic_string<CharT, CharTraits, Alloc>& str)
    {
        return move(str[N]);
    }
    /**
     * Gets the Nth element from str. N is a template parameter.
     * @param str The basic_string object from which to get the element.
    */
    template <std::size_t N, class CharT, class CharTraits = char_traits<CharT>, class Alloc = allocator<CharT>>
    CharT& get(basic_string<CharT, CharTraits, Alloc>& str)
    {
        return str[N];
    }
    /**
     * Returns an iterator to the beginning of a basic_string object. Equivalent to 
     * str.begin().
     * @param str The string.
    */
    template <class CharT, class CharTraits, class Alloc>
    auto begin(const basic_string<CharT, CharTraits, Alloc>& str) -> decltype(str.begin())
    {
        return str.begin();
    }
    /**
     * Returns an iterator to the end of a basic_string object. Equivalent to 
     * str.end().
     * @param str The string.
    */
    template <class CharT, class CharTraits, class Alloc>
    auto end(const basic_string<CharT, CharTraits, Alloc>& str) -> decltype(str.end())
    {
        return str.end();
    }
    /**
     * Swaps two basic_string objects.
     * @param s1 The first basic_string object.
     * @param s2 The second basic_string object.
    */
    template <class CharT, class CharTraits, class Alloc>
    constexpr void swap(basic_string<CharT, CharTraits, Alloc>& s1, basic_string<CharT, CharTraits, Alloc>& s2)
    {
        s1.swap(s2);
    }
    /**
     * Removes all characters equal to ch in str.
     * @param str The basic_string object.
     * @param ch The element of which all occurrences in str will be erased.
    */
    template <class CharT, class CharTraits, class Alloc, class U>
    constexpr std::size_t erase(basic_string<CharT, CharTraits, Alloc>& str, const U& ch)
    {
        auto it = std_copy::remove(str.begin(), str.end(), ch);
        std::size_t numberErased = std::distance(it, str.end());
        str.erase(it, str.end());
        return numberErased;
    }
    /**
     * Removes all characters for which fn equals true in str.
     * @param str The basic_string object.
     * @param fn The function used to determine which elements to erase.
    */
    template <class CharT, class CharTraits, class Alloc, class Function>
    constexpr std::size_t erase_if(basic_string<CharT, CharTraits, Alloc>& str, Function fn)
    {
        auto it = std_copy::remove_if(str.begin(), str.end(), fn);
        std::size_t numberErased = std::distance(it, str.end());
        str.erase(it, str.end());
        return numberErased;
    }

    typedef basic_string<char>      string;
    typedef basic_string<wchar_t>   wstring;
    typedef basic_string<char8_t>   u8string;
    typedef basic_string<char16_t>  u16string;
    typedef basic_string<char32_t>  u32string;
}

#endif /* _STD_COPY_STRING */