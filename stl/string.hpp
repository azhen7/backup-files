#ifndef _STD_COPY_STRING
#define _STD_COPY_STRING

#include <stdexcept>
#include <cmath>

#include "allocator.hpp"
#include "allocator_traits.hpp"
#include "iterator_funcs.hpp"
#include "char_traits.hpp"
#include "algorithm.hpp"

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

namespace std_copy
{
    template <class CharT, class Traits = char_traits<CharT>, class Alloc = allocator<CharT>>
    requires _std_copy_hidden::_std_copy_string::_is_valid_char_type<CharT>
    class basic_string
    {
        private:
            typedef basic_string<CharT, Traits, Alloc>      _basic_string_type;
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
            typedef _std_copy_hidden::_std_copy_stl_containers::_iterator<_basic_string_type> iterator;
            typedef const iterator                          const_iterator;

        private:
            pointer _internalString;
            size_type _length;
            size_type _capacity;

            template <class _AllocateFunc>
            void _allocateAndMoveStr(size_type i, _AllocateFunc mem_alloc, pointer src, size_type count)
            {
                _capacity = (i + 1 > 15) ? i + 1 : 15;
                _internalString = mem_alloc(_capacity);
                traits_type::move(_internalString, src, count);
                _internalString[i] = value_type();
            }

            template <class _AllocateFunc>
            void _allocateAndAssign(size_type i, _AllocateFunc mem_alloc, size_type count, const_reference ch)
            {
                _capacity = (i + 1 > 15) ? i + 1 : 15;
                _internalString = mem_alloc(_capacity);
                traits_type::assign(_internalString, count, ch);
                _internalString[i] = value_type();
            }

            template <class _AllocateFunc, class InputIt>
            void _allocateAndMoveRange(size_type i, _AllocateFunc mem_alloc, InputIt first, InputIt last)
            {
                _capacity = (i + 1 > 15) ? i + 1 : 15;
                _internalString = mem_alloc(_capacity);
                move(first, last, _internalString);
                _internalString[i] = value_type();
            }

            size_type _exponent(size_type x, size_type y)
            {
                size_type result = 1;
                while (y > 0)
                {
                    if (y % 2 == 0)
                    {
                        x *= x;
                        y /= 2;
                    }
                    else
                    {
                        result *= x;
                        y--;
                    }
                }
                return result;
            }
            size_type _calculateSmallestPowerOfTwoGreaterThan(size_type x)
            {
                if (x == 0)
                    return 1;
                return _exponent(2, (size_type) (std::log(x) / std::log(2)) + 1);
            }
            void _realloc(size_type n, size_type copyUpTo)
            {
                pointer temp = _internalString;
                size_type newSize = _capacity * _calculateSmallestPowerOfTwoGreaterThan(n);
                _allocateAndMoveStr(newSize - 1, allocator_type::allocate, temp, copyUpTo);
                allocator_type::deallocate(temp, _capacity);
                _capacity = newSize;
            }

        public:
            const static size_type npos = -1;

            basic_string()
                : _length(0),
                _capacity(15)
            {
                _internalString = allocator_type::allocate(15);
            }

            basic_string(pointer str)
            {
                _length = traits_type::length(str);
               _allocateAndMoveStr(_length, allocator_type::allocate,
                    str, _length);
            }

            basic_string(size_type count, const_reference ch)
                : _length(count)
            {
                _allocateAndAssign(_length, allocator_type::allocate,
                    count, ch);
            }

            basic_string(pointer str, size_type count)
                : _length(count)
            {
               _allocateAndMoveStr(_length, allocator_type::allocate,
                    str, count);
            }

            basic_string(const _basic_string_type& s, size_type count)
            {
                _length = (count > s._length) ? s._length : count;
               _allocateAndMoveStr(_length, allocator_type::allocate,
                    s._internalString, _length);
            }

            basic_string(const _basic_string_type& s, size_type pos, size_type count)
            {
                size_type copyUpTo = (pos + count > s._length || count == npos) ? s._length : pos + count;
                _length = copyUpTo - pos;
               _allocateAndMoveStr(_length, allocator_type::allocate,
                    s._internalString + pos, _length);
            }

            basic_string(const _basic_string_type& s)
                : _length(s._length)
            {
               _allocateAndMoveStr(_length, allocator_type::allocate,
                    s._internalString, _length);
            }

            basic_string(_basic_string_type&& s)
                : _length(s._length)
            {
               _allocateAndMoveStr(_length, allocator_type::allocate,
                    s._internalString, _length);
            }

            template <class InputIt>
            basic_string(InputIt start, InputIt last)
            {
                _length = std_copy::distance(start, last);
                _allocateAndMoveRange(_length, allocator_type::allocate,
                    start, last);
            }

            basic_string(decltype(nullptr)) = delete;

            /**
             * Returns the length of the string.
            */
            constexpr size_type length() const noexcept
            {
                return _length;
            }
            /**
             * Returns the size of the string (i.e. the number of characters).
            */
            constexpr size_type size() const noexcept
            {
                return _length;
            }
            /**
             * Returns the capacity of the string, i.e. the number of elements the 
             * string has storage for.
            */
            constexpr size_type capacity() const noexcept
            {
                return _capacity;
            }
            /**
             * Returns the allocator object associated with the string.
            */
            constexpr allocator_type get_allocator() noexcept
            {
                return allocator_type();
            }
            /**
             * Returns the underlying buffer serving as storage.
            */
            constexpr const_pointer data() noexcept
            {
                return _internalString;
            }
            /**
             * Returns a non-modifiable C style array version of the string. 
            */
            constexpr const_pointer c_str() noexcept
            {
                return _internalString;
            }
            /**
             * Returns the element at index i.
             * @param i The index to retrieve the element from.
            */
            constexpr reference at(size_type i)
            {
                if (i >= _length)
                    throw std::out_of_range("basic_string::at: index is out of bounds");

                return *(_internalString + i);
            }
            /**
             * Returns the element at index i. Provides C-style array indexing.
             * @param i The index to retrieve the element from.
            */
            constexpr reference operator[](size_type i)
            {
                return *(_internalString + i);
            }
            /**
             * Returns a reference to the first character in the string. Equivalent to 
             * operator[](0).
            */
            constexpr reference front()
            {
                return *_internalString;
            }
            /**
             * Returns a reference to the last character in the string. Equivalent to 
             * operator[](_length - 1).
            */
            constexpr reference back()
            {
                return *(_internalString + _length - 1);
            }
            /**
             * Returns an iterator to the start of the string.
            */
            constexpr iterator begin()
            {
                return iterator(_internalString);
            }
            /**
             * Returns an iterator to the theoretical element after the last element.
            */
            constexpr iterator end()
            {
                return iterator(_internalString + _length);
            }
            /**
             * Returns a const iterator to the start of the string.
            */
            constexpr const_iterator cbegin()
            {
                return iterator(_internalString);
            }
            /**
             * Returns a const iterator to the theoretical element after the last element.
            */
            constexpr const_iterator cend()
            {
                return iterator(_internalString + _length);
            }
            /**
             * Returns a boolean indicating whether the string is empty.
            */
            constexpr bool empty()
            {
                return _length == 0;
            }
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
            }
            /**
             * Shrinks the amount of storage in the string to the number of elements 
             * in the string.
            */
            constexpr void shrink_to_fit()
            {
                pointer temp = _internalString;
                _internalString = allocator_type::allocate(_length);
                move(temp, temp + _length, _internalString);
                allocator_type::deallocate(temp, _capacity);
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
                _length += count;
                _internalString[_length] = value_type();
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
                _length += count;
                _internalString[_length] = value_type();
                return *this;
            }
            /**
             * Appends another basic_string string onto this string. It appends the 
             * first count characters starting from pos.
             * @param s The string object that gets appended.
             * @param pos The starting position from where to append.
             * @param count How many places after the start position to end.
            */
            constexpr _basic_string_type& append(const _basic_string_type& s, size_type pos, size_type count = npos)
            {
                if (pos > s._length)
                    throw std::out_of_range("basic_string::append: pos is greater than the length of s");
                if (pos + count > s._length || count == npos)
                    count = s._length - pos;
                
                return this->append(s._internalString + pos, count);
            }
            /**
             * Appends all the characters in the range [first, last) onto the end of the string.
             * @param first An iterator to the start of the sequence.
             * @param last An iterator to the end of the sequence.
            */
            template <class InputIt>
            constexpr _basic_string_type& append(InputIt first, InputIt last)
                requires _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIt>
            {
                const difference_type dist = std_copy::distance(first, last);
                if (_length + dist > _capacity)
                    _realloc((_length + dist) / _capacity, _length);

                size_type i = _length;
                while (first != last)
                    _internalString[i++] = move(*first++);
                
                _internalString[i] = value_type();
                _length += dist;

                return *this;
            }
            /**
             * Overloaded operator+=. This operator appends a character sequence pointed to by 
             * p.
             * @param p A pointer to the character sequence to append.
            */
            constexpr _basic_string_type& operator+=(const_pointer p)
            {
                return this->append(p);
            }
            /**
             * Overloaded operator+=. This operator appends another basic_string type onto the end 
             * of the string.
             * @param s The basic_string object to append.
            */
            constexpr _basic_string_type& operator+=(const _basic_string_type& s)
            {
                return this->append(s._internalString);
            }
            /**
             * Overloaded operator+=. This operator appends a character onto the end of this string.
             * @param ch The character to append.
            */
            constexpr _basic_string_type& operator+=(const_reference ch)
            {
                return this->append(1, ch);
            }
            /**
             * Pushes a character onto the back of the string.
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
                this->erase(this->end() - 1);
            }
            /**
             * Erases the character at pos.
             * @param pos An iterator pointing to the element to be erased.
            */
            constexpr iterator erase(iterator pos)
            {
                const difference_type dist = pos - begin();
                pointer temp = _internalString;
                _internalString = allocator_type::allocate(_capacity);
                move(temp, temp + dist, _internalString);
                move(temp + dist + 1, temp + _length, _internalString + dist);
                _length--;
                _internalString[_length] = value_type();
                allocator_type::deallocate(temp, _capacity);
                return pos;
            }
            /**
             * Erases the characters in the range [first, last).
             * @param first An iterator to the start of the sequence to erase.
             * @param last An iterator to the end of the sequence to erase.
            */
            constexpr iterator erase(iterator first, iterator last)
            {
                const difference_type dist_first = first - begin();
                const difference_type dist_last = last - begin();
                pointer temp = _internalString;
                _internalString = allocator_type::allocate(_capacity);
                move(temp, temp + dist_first, _internalString);
                move(temp + dist_last, temp + _length, _internalString + dist_first);
                _length -= dist_last - dist_first;
                _internalString[_length] = value_type();
                allocator_type::deallocate(temp, _capacity);
                return last;
            }
            /**
             * Erases the first count characters starting from index pos.
             * @param pos The index from where to start erasing.
             * @param count The number of characters to erase.
            */
            constexpr _basic_string_type& erase(size_type pos = 0, size_type count = npos)
            {
                if (pos > _length)
                    throw std::out_of_range("basic_string::erase: pos is greater than _length");
                
                if (pos + count > _length || count == npos)
                    count = _length - pos;

                pointer temp = _internalString;
                _internalString = allocator_type::allocate(_capacity);
                move(temp, temp + pos, _internalString);
                move(temp + pos + count, temp + _length, _internalString + pos);
                _length -= count;
                _internalString[_length] = value_type();
                allocator_type::deallocate(temp, _capacity);
                return *this;
            }
            /**
             * Compares this basic_string with the character sequence pointed to by p.
             * @param p A pointer to the character sequence to compare against.
            */
            constexpr int compare(const_pointer p)
            {
                return this->compare(0, _length, p);
            }
            /**
             * Compares the substring [pos, pos + count) of *this with the 
             * character sequence pointed to by p.
             * @param pos The starting index of the substring of *this.
             * @param count The number of characters after pos to compare.
             * @param p A pointer to the character sequence to compare against.
            */
            constexpr int compare(size_type pos, size_type count, const_pointer p)
            {
                return this->compare(pos, count, p, traits_type::length(p));
            }
            /**
             * Compares the substring [pos, pos + count1) of *this with the 
             * first count2 elements in the character sequence pointed to by p.
             * @param pos The starting index of the substring of *this.
             * @param count1 The number of characters after pos to compare.
             * @param p A pointer to the character sequence to compare against.
             * @param count2 The number of characters in p to compare.
            */
            constexpr int compare(size_type pos, size_type count1, const_pointer p, size_type count2)
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
            constexpr int compare(const _basic_string_type& s)
            {
                return this->compare(0, _length, s);
            }
            /**
             * Compares the substring [pos, pos + count) of *this with 
             * another basic_string object.
             * @param pos The starting index of the substring of *this.
             * @param count The number of characters after pos to compare.
             * @param s The basic_string object to compare against.
            */
            constexpr int compare(size_type pos, size_type count, const _basic_string_type& s)
            {
                if (count > _length - pos)
                    count = _length - pos;

                int result = traits_type::compare(_internalString + pos, s._internalString, std_copy::min(count, s._length));
                if (result != 0 || _length == s._length)
                    return result;
                if (count < s._length)
                    return -1;
                return 1;
            }
            /**
             * Compares the substring [pos1, pos1 + count1) of *this with 
             * the substring [pos2, count2) of another basic_string object.
             * @param pos1 The starting index of the substring of *this.
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
             * @param ch The character to check for at the beginning of *this.
            */
            constexpr bool starts_with(value_type ch)
            {
                return traits_type::eq(this->front(), ch);
            }
            /**
             * Checks if *this starts with the null-terminated character sequence p.
             * @param p The character sequence to check for at the beginning of *this.
            */
            constexpr bool starts_with(const_pointer p)
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
             * @param s The basic_string object to check for at the beginning of *this.
            */
            constexpr bool starts_with(const _basic_string_type& s)
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
            template <class InputIt>
            constexpr bool starts_with(InputIt first, InputIt last)
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
             * @param ch The character to check for at the end of *this.
            */
            constexpr bool ends_with(const_reference ch)
            {
                return traits_type::eq(this->back(), ch);
            }
            /**
             * Check if *this ends with p.
             * @param p A null-terminated character sequence to check for at the end of *this.
            */
            constexpr bool ends_with(const_pointer p)
            {
                const size_type len = traits_type::length(p);
                if (len > _length)
                    return false;
                
                for (size_type i = 1; i <= len; i++)
                    if (!traits_type::eq(_internalString[_length - i], p[len - i]))
                        return false;
                return true;
            }
            /**
             * Checks if *this ends with s.
             * @param s A basic_string object to check for at the end of *this.
            */
            constexpr bool ends_with(const _basic_string_type& s)
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
            template <class InputIt>
            constexpr bool ends_with(InputIt first, InputIt last)
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
             * Returns a std::size_t value indicating the index at which the character 
             * ch first occurrs in *this.
             * @param ch The character to search for.
             * @param pos The index from where to start searching. Default value is 0.
             * @param count The number of characters after pos to search in.
            */
            constexpr size_type find(const_reference ch, size_type pos, size_type count)
            {
                return traits_type::find(_internalString + pos, count, ch) - _internalString;
            }
            /**
             * Returns a std::size_t value indicating the index at which the character 
             * ch first occurrs in *this.
             * @param ch The character to search for.
             * @param pos The index from where to start searching. Default value is 0.
            */
            constexpr size_type find(const_reference ch, size_type pos = 0)
            {
                return this->find(ch, pos, _length);
            }
            /**
             * Returns a std::size_t value indicating the index at which the substring 
             * p first occurs in *this.
             * @param p The substring to search for.
             * @param pos The index from which to start searching for the substring.
            */
            constexpr size_type find(const_pointer p, size_type pos = 0)
            {
                return this->find(p, pos, traits_type::length(p));
            }
            /**
             * Returns a std::size_t value indicating the index at which the first count 
             * characters in the character sequence p first occurs in the substring [pos, size()) 
             * of *this.
             * @param p The character sequence to find.
             * @param pos The index from which to start searching for p in *this.
             * @param count The number of characters in p to look for.
            */
            constexpr size_type find(const_pointer p, size_type pos, size_type count)
            {
                size_type indexInSubstr = 0;
                size_type indexSubstrStart = npos;
                for (size_type i = pos; i < _length && indexInSubstr != count; i++)
                {
                    if (!traits_type::eq(_internalString[i], p[indexInSubstr]))
                    {
                        indexInSubstr = 0;
                        indexSubstrStart = npos;
                    }
                    if (traits_type::eq(_internalString[i], p[indexInSubstr]))
                    {
                        indexInSubstr++;
                        indexSubstrStart = (indexSubstrStart == npos) ? i : indexSubstrStart;
                    }
                }
                return indexSubstrStart;
            }
            /**
             * Returns a std::size_t value indicating the value at which the first count 
             * characters in the basic_string object s first occurs in the substring 
             * [pos, size()) of *this.
             * @param s The basic_string object to search for.
             * @param pos The position from where to start searching.
             * @param count The number of characters in s to search for.
            */
            constexpr size_type find(const _basic_string_type& s, size_type pos, size_type count)
            {
                return this->find(s._internalString, pos, count);
            }
            /**
             * Returns a std::size_t value indicating the value at which the basic_string 
             * object s first occurs in the substring [pos, size()) of *this.
             * @param s The basic_string object to search for.
             * @param pos The position from where to start searching.
            */
            constexpr size_type find(const _basic_string_type& s, size_type pos = 0)
            {
                return this->find(s._internalString, pos, s._length);
            }
            /**
             * Returns a std::size_t value indicating the value at which the range [first, last) 
             * first occurs in the substring [pos, size()) of *this.
             * @param first An iterator to the start of the range.
             * @param last An iterator to the end of the range.
             * @param pos The position in *this from where to start searching.
            */
            template <class InputIt>
            constexpr size_type find(InputIt first, InputIt last, size_type pos = 0)
            {
                size_type indexSubstrStart = npos;
                InputIt tempFirst = first;
                for (size_type i = pos; i < _length && first != last; i++)
                {
                    if (!traits_type::eq(_internalString[i], *first))
                    {
                        indexSubstrStart = npos;
                        first = tempFirst;
                    }
                    if (traits_type::eq(_internalString[i], *first))
                    {
                        first++;
                        indexSubstrStart = (indexSubstrStart == npos) ? i : indexSubstrStart;
                    }
                }
                return indexSubstrStart;
            }
            /**
             * Checks if *this contains another basic_string object.
             * @param s The basic_string object to find.
            */
            constexpr bool contains(const _basic_string_type& s)
            {
                return this->find(s) != npos;
            }
            /**
             * Checks if *this contains a character sequence p.
             * @param p The character sequence to look for.
            */
            constexpr bool contains(const_pointer p)
            {
                return this->find(p) != npos;
            }
            /**
             * Checks if *this contains a character ch.
             * @param ch The character to search for.
            */
            constexpr bool contains(const_reference ch, size_type pos = 0)
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
                _internalString[count] = value_type();
                _length = count;
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
             * Replaces the range [first, last) of *this with str.
             * @param first An iterator pointing to the start of the range to erase.
             * @param last An iterator pointing to the end of the range to erase.
             * @param str The basic_string object to replace the range.
            */
            constexpr _basic_string_type& replace(iterator first, iterator last, const _basic_string_type& str)
            {
                return this->replace(first - this->begin(), last - first, str);
            }
            /**
             * Replaces the substring [pos, pos + count) of *this with str.
             * @param pos The index from which to start replacing.
             * @param count The number of characters after pos to replace.
             * @param str The basic_string object to replace the substring with.
            */
            constexpr _basic_string_type& replace(size_type pos, size_type count, const _basic_string_type& str)
            {
                if (pos > _length)
                    throw std::out_of_range("basic_string::replace: pos > size()");
                if (count > _length - pos)
                    count = _length - pos;
                
                if (count == str._length)
                    traits_type::move(_internalString + pos, str._internalString, count);
                else
                {
                    _capacity *= _calculateSmallestPowerOfTwoGreaterThan((_length - count + str._length) / _capacity);
                    pointer temp = _internalString;
                    _internalString = allocator_type::allocate(_capacity);
                    move(temp, temp + pos, _internalString);
                    move(str._internalString, str._internalString + str._length, _internalString + pos);
                    move(temp + pos + count, temp + _length, _internalString + pos + str._length);
                    _length -= count - str._length;
                    _internalString[_length] = value_type();
                }
                return *this;
            }
            /**
             * Replaces the substring [pos1, pos1 + count1) of *this with the substring [pos2, pos2 + count2) 
             * of str.
             * @param pos1 The index from which to start replacing.
             * @param count1 The number of characters after pos to replace.
             * @param str The basic_string object to replace the substring with.
             * @param pos2 The index of str to start replacing the substring [pos, pos + count) in *this.
             * @param count2 The number of characters after pos2 to start replacing the substring [pos, pos + count) in *this.
            */
            constexpr _basic_string_type& replace(size_type pos1, size_type count1, const _basic_string_type& str, size_type pos2, size_type count2)
            {
                if (pos1 > _length)
                    throw std::out_of_range("basic_string::replace: pos1 > size()");
                if (pos2 > str._length)
                    throw std::out_of_range("basic_string::replace: pos2 > str.size()");
                count1 = (count1 > _length - pos1) ? _length - pos1 : count1;
                count2 = (count2 > str._length - pos2) ? str._length - pos2 : count2;

                return this->replace(pos1, count1, str._internalString + pos2, str._internalString + pos2 + count2);
            }
            /**
             * Replaces the range [first, last) of *this with s.
             * @param first An iterator pointing to the start of the range to erase.
             * @param last An iterator pointing to the end of the range to erase.
             * @param s The character sequence to replace the range.
            */
            constexpr _basic_string_type& replace(iterator first, iterator last, pointer s)
            {
                return this->replace(first - this->begin(), last - first, s);
            }
            /**
             * Replaces the substring [pos, pos + count) of *this with s.
             * @param pos The index from which to start replacing.
             * @param count The number of characters after pos to replace.
             * @param s The character sequence to replace the range.
            */
            constexpr _basic_string_type& replace(size_type pos, size_type count, pointer s)
            {
                if (pos > _length)
                    throw std::out_of_range("basic_string::replace: pos > size()");
                if (count > _length - pos)
                    count = _length - pos;

                const size_type len = traits_type::length(s);
                if (count == len)
                    traits_type::move(_internalString + pos, s, count);
                else
                {
                    _capacity *= _calculateSmallestPowerOfTwoGreaterThan((_length - count + len) / _capacity);
                    pointer temp = _internalString;
                    _internalString = allocator_type::allocate(_capacity);
                    move(temp, temp + pos, _internalString);
                    move(s, s + len, _internalString + pos);
                    move(temp + pos + count, temp + _length, _internalString + pos + len);
                    _length -= count - len;
                    _internalString[_length] = value_type();
                }
                return *this;
            }
            /**
             * Replaces the substring [pos, pos + count1) of *this with the first count2 
             * characters of s.
             * @param pos The index from which to start replacing.
             * @param count1 The number of characters after pos to replace.
             * @param s The character sequence to replace the range.
             * @param count2 The number of characters in s to replace with.
            */
            constexpr _basic_string_type& replace(size_type pos, size_type count1, pointer s, size_type count2)
            {
                const size_type len = traits_type::length(s);
                if (pos > _length)
                    throw std::out_of_range("basic_string::replace: pos > size()");
                if (count1 > _length - pos)
                    count1 = _length - pos;
                count2 = (count2 > len) ? len : count2;

                return this->replace(this->begin() + pos, this->begin() + pos + count1, s, s + count2);
            }
            /**
             * Replaces the range [first, last) of *this with the first count2 
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
             * Replaces the range [first, last) of *this with the range [first2, last2).
             * @param first An iterator pointing to the start of the range to erase.
             * @param last An iterator pointing to the end of the range to erase.
             * @param first2 An iterator to the start of the range to replace [first, last).
             * @param last2 An iterator to the end of the range to replace [first, last).
            */
            template <class InputIt>
            constexpr _basic_string_type& replace(iterator first, iterator last, InputIt first2, InputIt last2)
                requires _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIt>
            {
                return this->replace(first - this->begin(), last - first, first2, last2);
            }
            /**
             * Replaces the substring [pos, pos + count) of *this with the range [first2, last2).
             * @param pos The index from which to start replacing.
             * @param count The number of characters after pos to replace.
             * @param first An iterator to the start of the range to replace [first, last).
             * @param last An iterator to the end of the range to replace [first, last).
            */
            template <class InputIt>
            constexpr _basic_string_type& replace(size_type pos, size_type count, InputIt first, InputIt last)
                requires _std_copy_hidden::_std_copy_iterator_traits::_is_input_iterator<InputIt>
            {
                if (pos > _length)
                    throw std::out_of_range("basic_string::replace: pos > size()");
                if (count > _length - pos)
                    count = _length - pos;
                    
                const size_type len = std_copy::distance(first, last);
                if (count == len)
                    move(first, last, _internalString + pos);
                else
                {
                    _capacity *= _calculateSmallestPowerOfTwoGreaterThan((_length - count + len) / _capacity);
                    pointer temp = _internalString;
                    _internalString = allocator_type::allocate(_capacity);
                    move(temp, temp + pos, _internalString);
                    move(first, last, _internalString + pos);
                    move(temp + pos + count, temp + _length, _internalString + pos + len);
                    _length -= count - len;
                    _internalString[_length] = value_type();
                }
                return *this;
            }
            /**
             * Replaces the substring [pos, pos + count) with count elements of value ch.
             * @param pos The index to start replacing from.
             * @param count The number of characters after pos to replace.
             * @param count2 The number of elements to replace the range with.
             * @param ch The value of each element.
            */
            constexpr _basic_string_type& replace(size_type pos, size_type count, size_type count2, const_reference ch)
            {
                if (count == count2)
                    traits_type::assign(_internalString + pos, count2, ch);
                else
                {
                    _capacity *= _calculateSmallestPowerOfTwoGreaterThan((_length - count + count2) / _capacity);
                    pointer temp = _internalString;
                    _internalString = allocator_type::allocate(_capacity);
                    move(temp, temp + pos, _internalString);
                    traits_type::assign(_internalString + pos, count2, ch);
                    move(temp + pos + count, temp + _length, _internalString + pos + count2);
                    _length -= count - count2;
                    _internalString[_length] = value_type();
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
    };

    /**
     * Gets the Nth element from str. N is a template parameter.
     * @param str The basic_string object from which to get the element.
    */
    template <unsigned long long N, class CharT, class CharTraits = std_copy::char_traits<CharT>, class Alloc = std_copy::allocator<CharT>>
    CharT&& get(basic_string<CharT, CharTraits, Alloc>& str)
    {
        return move(str[N]);
    }
    /**
     * Gets the Nth element from str. N is a template parameter.
     * @param str The basic_string object from which to get the element.
    */
    template <unsigned long long N, class CharT, class CharTraits = std_copy::char_traits<CharT>, class Alloc = std_copy::allocator<CharT>>
    CharT& get(basic_string<CharT, CharTraits, Alloc>& str)
    {
        return str[N];
    }

    typedef basic_string<char>      string;
    typedef basic_string<wchar_t>   wstring;
    typedef basic_string<char8_t>   u8string;
    typedef basic_string<char16_t>  u16string;
    typedef basic_string<char32_t>  u32string;
}

#endif /* _STD_COPY_STRING */