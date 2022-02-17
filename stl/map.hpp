#ifndef _STD_COPY_MAP
#define _STD_COPY_MAP

#include <stdexcept>
#include <cstdint>
#include <iostream>

#include "functional_comp.hpp"
#include "algorithm.hpp"
#include "iterator_funcs.hpp"
#include "allocator.hpp"
#include "allocator_traits.hpp"
#include "utility.hpp"
#include "iterator_adaptors.hpp"

namespace std_copy
{
    /**
     * An implementation of std::map, defined in the <map> header file.
     * @param Key The type of the keys in the map.
     * @param T The type of the mapped values in the map.
     * @param Compare The comparison struct used to sort the keys.
     * @param Alloc The object used to allocate space for the map.
    */
    template <class Key, class T, class Compare = less<Key>, class Alloc = std_copy::allocator<std_copy::pair<Key, T>>>
#if __cplusplus > 201703L
    requires _std_copy_hidden::_std_copy_allocator::_is_valid_allocator<Alloc>
#endif
    class map
    {
        protected:
            typedef map<Key, T, Compare, Alloc>                 _map_type;
            typedef _std_copy_hidden::_std_copy_stl_containers::_iterator<_map_type> _iterator_type;
            
        public:
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef pair<Key, T>                                value_type;
            typedef Compare                                     key_compare;
            typedef value_type*                                 pointer;
            typedef const value_type*                           const_pointer;
            typedef value_type&                                 reference;
            typedef const value_type&                           const_reference;
            typedef Alloc                                       allocator_type;
            typedef std::size_t                                 size_type;
            typedef std::ptrdiff_t                              difference_type;
            typedef _iterator_type                              iterator;
            typedef const _iterator_type                        const_iterator;
            typedef reverse_iterator<pointer>                   reverse_iterator;
            typedef const reverse_iterator                      const_reverse_iterator;
        
        protected:
            typedef pair<iterator, bool>                        _iterator_and_bool;

            pointer _internalBuffer;
            size_type _numberOfElements;
            size_type _capacity;

            class value_compare
                : binary_function<value_type, value_type, bool>
            {
                friend class map;
                
                protected:
                    key_compare comp;
                    value_compare(key_compare c) : comp(c) {}

                public:
                    bool operator()(const value_type& a, const value_type& b)
                    {
                        return comp(a.first, b.first);
                    }
            };

            void _copyAndFindInsertPos(pointer copyFrom, const key_type& key, size_type& pos)
            {
                for (size_type i = 0; i < _numberOfElements; i++)
                {
                    if (!key_compare{}(copyFrom[i].first, key))
                    {
                        move_backward(copyFrom + i, copyFrom + _numberOfElements, _internalBuffer + _numberOfElements + 1);
                        pos = i;
                        break;
                    }
                    _internalBuffer[i] = move(copyFrom[i]);
                }
            }

            _iterator_and_bool _emplace(const_reference elemToConstruct)
            {
                iterator pos = this->find(elemToConstruct.first);
                if (pos != this->end())
                    return _iterator_and_bool(pos, false);

                size_type whereToInsert = 0;
                if (_numberOfElements ==  _capacity)
                {
                    _capacity = (_capacity == 0) ? 1 : _capacity * 2;

                    pointer temp = _internalBuffer;
                    _internalBuffer = allocator_type::allocate(_capacity);
                    _copyAndFindInsertPos(temp, elemToConstruct.first, whereToInsert);
                    allocator_type::deallocate(temp, (size_type) _capacity / 2);
                }
                construct_at(_internalBuffer + whereToInsert, move(elemToConstruct));
                _numberOfElements++;
                return _iterator_and_bool(iterator(_internalBuffer + whereToInsert), true);
            }

        public:
            /**
             * Default constructor
            */
            map() : _capacity(0), _numberOfElements(0) {}
            /**
             * This function constructs a map from a given map object.
             * @param copy The map used to construct the current map object.
            */
            map(const _map_type& copy)
                : _capacity(copy._capacity),
                _numberOfElements(copy._numberOfElements)
            {
                _internalBuffer = allocator_type::allocate(_capacity);
                for (size_type i = 0; i < _numberOfElements; i++)
                    _internalBuffer[i] = move(copy._internalBuffer[i]);
            }
            map(const _map_type& copy, const allocator_type& alloc)
                : _capacity(copy._capacity),
                _numberOfElements(copy._numberOfElements)
            {
                _internalBuffer = alloc.allocate(_capacity);
                for (size_type i = 0; i < _numberOfElements; i++)
                    _internalBuffer[i] = move(copy._internalBuffer[i]);
            }
            /**
             * This function constructs a map from a given rvalue reference 
             * map object.
             * @param copy The map used to construct the current map object.
            */
            map(_map_type&& copy)
                : _capacity(move(copy._capacity)),
                _internalBuffer(move(copy._internalBuffer))
            {
            }
            map(_map_type&& copy, const allocator_type& a)
                : _capacity(move(copy._capacity)),
                _internalBuffer(move(copy._internalBuffer))
            {
            }

            virtual ~map()
            {
                for (int i = 0; i < _numberOfElements; i++)
                    _internalBuffer[i].~value_type();
            }

            /**
             * Copies the contents from m to *this.
             * @param m The map to copy from.
            */
            constexpr void assign(const _map_type& m)
            {
                _numberOfElements = m._numberOfElements;
                _capacity = m._capacity;

                _internalBuffer = allocator_type::allocate(_capacity);
                for (size_type i = 0; i < _numberOfElements; i++)
                    _internalBuffer[i] = move(m._internalBuffer[i]);
            }
            /**
             * Copies the contents from m to *this.
             * @param m The rvalue-reference'd map to copy from.
            */
            constexpr void assign(_map_type&& m)
            {
                _numberOfElements = move(m._numberOfElements);
                _capacity = move(m._capacity);
                
                _internalBuffer = allocator_type::allocate(_capacity);
                for (size_type i = 0; i < _numberOfElements; i++)
                    _internalBuffer[i] = move(m._internalBuffer[i]);
            }
            /**
             * This function returns the number of elements 
             * in the map.
            */
            constexpr size_type size() const noexcept
            {
                return _numberOfElements;
            }
            /**
             * This function checks whether the map is empty (i.e. has no elements).
            */
            constexpr bool empty() const noexcept
            {
                return _numberOfElements == 0;
            }
            /**
             * This function clears the map.
            */
            constexpr void clear()
            {
                allocator_type::deallocate(_internalBuffer, _capacity);
                _numberOfElements = 0;
                _capacity = 0;
            }
            /**
             * This function returns an iterator to the first element in the container
            */
            constexpr iterator begin() { return iterator(_internalBuffer); }
            /**
             * This function returns an iterator to the theoretical element after the last 
             * element in the container;
            */
            constexpr iterator end() { return iterator(_internalBuffer + _numberOfElements); }
            /**
             * This function returns a const iterator to the first element in the container
            */
            constexpr const_iterator cbegin() { return iterator(_internalBuffer); }
            /**
             * This function returns a const iterator to the theoretical element after the last 
             * element in the container;
            */
            constexpr const_iterator cend() { return iterator(_internalBuffer + _numberOfElements); }
            /**
             * Returns a reverse iterator to the reverse beginning of the vector.
            */
            constexpr reverse_iterator rbegin() const { return reverse_iterator(_internalBuffer + _numberOfElements); }
            /**
             * Returns a reverse iterator to the reverse end of the vector.
            */
            constexpr reverse_iterator rend() const { return reverse_iterator(_internalBuffer); }
            /**
             * Returns a const reverse iterator to the reverse beginning of the vector.
            */
            constexpr const_reverse_iterator crbegin() const { return reverse_iterator(_internalBuffer + _numberOfElements); }
            /**
             * Returns a const reverse iterator to the reverse end of the vector.
            */
            constexpr const_reverse_iterator crend() const { return reverse_iterator(_internalBuffer); }
            /**
             * This function erases the element pointed to by the provided iterator.
             * @param pos The iterator which points to the element to erase.
            */
            constexpr iterator erase(iterator pos)
            {
                size_type index = 0;
                for (iterator it = this->begin(); it != this->end(); it++)
                {
                    if (it != pos)
                        _internalBuffer[index++] = *it;
                }
                _numberOfElements--;
                (_internalBuffer + _numberOfElements)->~value_type();
                return pos;
            }
            /**
             * This function erases the range [first, last).
             * @param first The start of the sequence to erase.
             * @param last The end of the sequence to erase.
            */
            constexpr iterator erase(iterator first, iterator last)
            {
                size_type index = 0;
                for (iterator it = this->begin(); it != this->end(); it++)
                {
                    if (it < first || it >= last)
                        _internalBuffer[index++] = *it;
                }
                for (int i = 0; i < last - first; i++)
                    (_internalBuffer + _numberOfElements - 1 - i)->~value_type();

                _numberOfElements = index;
                return last;
            }
            /**
             * Operator overload of operator[]. If the provided argument exists in the 
             * map, a reference to its mapped value is returned. Otherwise, the function
             * adds an element to the map with the key having the value of the argument.
             * @param key The key of the element to get, or in case an element with the same key 
             * doesn't exist, creates it.
            */
            mapped_type& operator[](const key_type& key)
            {
                iterator loc = this->find(key);
                if (loc != this->end())
                    return loc->second;
                    
                size_type whereToInsert = _numberOfElements;
                if (_numberOfElements == 0)
                {
                    _internalBuffer = allocator_type::allocate(1);
                    _capacity = 1;
                }
                else if (_numberOfElements == _capacity)
                {
                    _capacity *= 2;

                    pointer temp = _internalBuffer;
                    _internalBuffer = allocator_type::allocate(_capacity);
                    _copyAndFindInsertPos(temp, key, whereToInsert);
                    allocator_type::deallocate(temp, (size_type) _capacity / 2);
                }
                else
                {
                    iterator it = this->upper_bound(key);
                    whereToInsert = it - this->begin();
                    move_backward(it, this->end(), std_copy::next(it, 1));
                }
                
                _numberOfElements++;
                _internalBuffer[whereToInsert] = std_copy::make_pair(key, mapped_type());
                return _internalBuffer[whereToInsert].second;
            }
            /**
             * This function has the same functionality as operator[], except 
             * instead of creating a new element if the provided key doesn't 
             * exist, an out_of_range exception is thrown.
             * @param key The key of the element to return.
            */
            mapped_type& at(const key_type& key)
            {
                iterator location = this->find(key);
                if (location != this->end())
                    return location->second;

                throw std::out_of_range("map::at");
            }
            /**
             * This function inserts an element into the container. It does not 
             * insert an element when an element with the specified key already exists.
             * @param pairToInsert The element to insert into the map.
            */
            constexpr _iterator_and_bool insert(const_reference pairToInsert)
            {
                iterator pos = this->find(pairToInsert.first);
                if (pos != this->end())
                    return _iterator_and_bool(pos, false);
                
                size_type whereToInsert = _numberOfElements;
                if (_numberOfElements == 0)
                {
                    _internalBuffer = allocator_type::allocate(1);
                    _capacity = 1;
                }
                else if (_numberOfElements ==  _capacity)
                {
                    _capacity *= 2;

                    pointer temp = _internalBuffer;
                    _internalBuffer = allocator_type::allocate(_capacity);
                    _copyAndFindInsertPos(temp, pairToInsert.first, whereToInsert);
                    allocator_type::deallocate(temp, _capacity / 2);
                }
                else
                {
                    iterator it = this->upper_bound(pairToInsert.first);
                    whereToInsert = it - this->begin();
                    move_backward(it, this->end(), std_copy::next(it, 1));
                }
                
                _numberOfElements++;
                _internalBuffer[whereToInsert] = pairToInsert;
                return _iterator_and_bool(iterator(_internalBuffer + whereToInsert), true);
            }
            /**
             * This function does the same thing as insert(), except if the element with the specified 
             * key already exists, that element gets assigned to the new mapped value instead.
             * @param pairToInsert The element to insert into the map.
            */
            constexpr _iterator_and_bool insert_or_assign(const_reference pairToInsert)
            {
                _iterator_and_bool p = this->insert(pairToInsert);
                if (!p.second)
                    (*this)[p.first->first] = pairToInsert.second;
                return p;
            }
            /**
             * This function constructs an element in place if an element with the key does not exist in 
             * the container.
             * @param elemToConstruct The element to construct in place.
            */
            constexpr _iterator_and_bool emplace(const_reference elemToConstruct)
            {
                return _emplace(elemToConstruct);
            }
            /**
             * Constructs an element in place if an element with the specified key does not exist in the 
             * container.
             * @param args The arguments forwarded to the constructor.
            */
            template <class ...Args>
            constexpr _iterator_and_bool emplace(Args&&... args)
            {
                return _emplace(value_type(forward<Args>(args)...));
            }
            /**
             * Behaves like emplace() except args is forwarded to the constructed element's second parameter.
             * @param key The key of the object that will get inserted.
             * @param args The arguments forwarded to the constructed element's second parameter.
            */
            template <class ...Args>
            constexpr _iterator_and_bool try_emplace(const key_type& key, Args&&... args)
            {
                return _emplace(value_type(move(key), mapped_type(forward<Args>(args)...)));
            }
            /**
             * This function copies one map to another.
             * @param s The map to copy to this.
            */
            constexpr void operator=(const _map_type& s)
            {
                allocator_type::deallocate(_internalBuffer, _capacity);
                _numberOfElements = s._numberOfElements;
                _capacity = s._capacity;
                _internalBuffer = allocator_type::allocate(_capacity);
                std_copy::copy(s._internalBuffer, s._internalBuffer + _numberOfElements, _internalBuffer);
            }
            /**
             * This function returns an object of the provided _allocator type.
            */
            constexpr allocator_type get_allocator() const noexcept
            {
                return allocator_type();
            }
            /**
             * This function returns an iterator to the element with the 
             * same key as key.
             * @param key The key of the element to search for.
            */
            constexpr iterator find(const key_type& key)
            {
                if (_numberOfElements == 0)
                    return this->end();

                pointer start = _internalBuffer;
                pointer finish = _internalBuffer + _numberOfElements;
                size_type tempNumberOfElements = _numberOfElements;
                while (finish >= start)
                {
                    size_type addToGetMiddle = (tempNumberOfElements % 2 != 0) ? (tempNumberOfElements / 2) : (tempNumberOfElements / 2 - 1);
                    pointer middle = start + addToGetMiddle;
                    if (middle->first == key)
                        return iterator(middle);
                    else if (middle->first > key)
                    {
                        finish = middle - 1;
                        tempNumberOfElements = addToGetMiddle + 1;
                    }
                    else
                    {
                        start = middle + 1;
                        tempNumberOfElements = addToGetMiddle + 1;
                    }
                }
                return this->end();
            }
            /**
             * This function checks whether the container contains an 
             * element with a specified key.
             * The equality operator has to be provided by the user.
             * @param key The key to find.
            */
            constexpr bool contains(const key_type& key)
            {
                return this->find(key) != this->end();
            }
            /**
             * This function swaps the contents of *this with s.
             * @param s The map to swap with.
            */
            constexpr void swap(_map_type& s)
            {
                _map_type temp(move(*this));
                this->assign(s);
                s.assign(temp);

                std_copy::swap(_numberOfElements, s._numberOfElements);
                std_copy::swap(_capacity, s._capacity);
            }
            /**
             * This function returns an iterator to the first element with 
             * a key that does not compare less than key.
             * @param key The key used to compare against the keys of the 
             * other elements.
            */
            constexpr iterator lower_bound(const key_type& key)
            {
                if (!_numberOfElements)
                    return this->end();

                pointer start = _internalBuffer;
                pointer finish = _internalBuffer + _numberOfElements;
                size_type tempNumberOfElements = _numberOfElements;
                while (finish >= start)
                {
                    size_type addToGetMiddle = (tempNumberOfElements % 2 != 0) ? (tempNumberOfElements / 2) : (tempNumberOfElements / 2 - 1);
                    pointer middle = start + addToGetMiddle;
                    if (middle->first >= key)
                        return iterator(middle);
                    else
                    {
                        start = middle + 1;
                        tempNumberOfElements = addToGetMiddle + 1;
                    }
                }
                return this->end();
            }
            /**
             * This function returns an iterator to the first element with 
             * a key that is greater than key.
             * @param key The key used to compare against the keys of the 
             * other elements.
            */
            constexpr iterator upper_bound(const key_type& key)
            {
                if (!_numberOfElements)
                    return this->end();

                pointer start = _internalBuffer;
                pointer finish = _internalBuffer + _numberOfElements;
                size_type tempNumberOfElements = _numberOfElements;
                while (finish >= start)
                {
                    size_type addToGetMiddle = (tempNumberOfElements % 2 != 0) ? (tempNumberOfElements / 2) : (tempNumberOfElements / 2 - 1);
                    pointer middle = start + addToGetMiddle;
                    if (middle->first > key)
                        return iterator(middle);
                    else
                    {
                        start = middle + 1;
                        tempNumberOfElements = addToGetMiddle + 1;
                    }
                }
                return this->end();
            }
            /**
             * Returns a range containing all elements with the given key in the container.
             * @param key The key to search for.
            */
            constexpr pair<iterator, iterator> equal_range(const key_type& key)
            {
                return std_copy::make_pair(this->lower_bound(), this->upper_bound());
            }
            /**
             * Returns the object used to compare the keys.
            */
            constexpr key_compare key_comp() const noexcept
            {
                return key_compare{};
            }
            /**
             * Returns the object used to compare the mapped values.
            */
            constexpr value_compare value_comp() const noexcept
            {
                return value_compare(key_compare{});
            }
    };
    /**
     * This function swaps the contents of two maps.
     * @param lhs The first map.
     * @param rhs The second map.
    */
    template <class T1, class T2, class Alloc>
    void swap(map<T1, T2, Alloc>& lhs, map<T1, T2, Alloc>& rhs)
    {
        lhs.swap(rhs);
    }
    /**
     * This function erases all elements from a map that meet a certain criteria.
     * @param c The map to erase elements from.
     * @param pred The function used to erase elements.
    */
    template <class T1, class T2, class Compare, class Alloc, class Function>
    typename map<T1, T2, Compare, Alloc>::size_type erase_if(map<T1, T2, Compare, Alloc>& c, Function func)
    {
        typename map<T1, T2, Compare, Alloc>::size_type oldSize = c.size();
        for (typename map<T1, T2, Compare, Alloc>::iterator it = c.begin(); it != c.end(); )
        {
            if (func(*it))
                c.erase(it);
            else
                it++;
        }
        return oldSize - c.size();
    }
    /**
     * Returns an iterator to the beginning of a map. Equivalent 
     * to m.begin().
     * @param m The map.
    */
    template <class T1, class T2, class Compare, class Alloc>
    typename map<T1, T2, Compare, Alloc>::iterator begin(const map<T1, T2, Compare, Alloc>& m)
    {
        return m.begin();
    }
    /**
     * Returns an iterator to the end of a map. Equivalent 
     * to m.end();
     * @param m The map.
    */
    template <class T1, class T2, class Compare, class Alloc>
    typename map<T1, T2, Compare, Alloc>::iterator end(const map<T1, T2, Compare, Alloc>& m)
    {
        return m.end();
    }
}

#endif /* _STD_COPY_MAP */
