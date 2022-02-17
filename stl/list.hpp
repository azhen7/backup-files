#ifndef _STD_COPY_LIST
#define _STD_COPY_LIST

#include "allocator.hpp"
#include "allocator_traits.hpp"
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "iterator_adaptors.hpp"
#include "move.hpp"
#include <cstdint>

#include <iostream>
#include <stdexcept>

namespace std_copy
{
    template <class T, class Alloc = std_copy::allocator<T>>
    class list
    {
        private:
            template <class _Type>
            struct _node
            {
                private:
                    typedef _node<_Type>        _self_type;
                    typedef _Type               _type;

                public:
                    _self_type* _next;
                    _self_type* _prev;

                    _Type _value;

                    void _init(_self_type* p, _self_type* n, const _Type& val)
                    {
                        _prev = move(p);
                        _next = move(n);
                        _value = move(val);
                    }
            };

            template <class _T>
            struct _node_iterator
            {
                private:
                    typedef _node<_T>    _self_type;
                    _self_type* _curr;

                public:
                    typedef std::ptrdiff_t              difference_type;
                    typedef bidirectional_iterator_tag  iterator_category;
                    typedef _Type                       value_type;
                    typedef _Type&                      reference;
                    typedef _Type*                      pointer;

                    _node_iterator(_self_type* e)
                        : _curr(e)
                    {}

                    void operator++()
                    {
                        if (_curr)
                            _curr = _curr->_next;
                    }
                    void operator--()
                    {
                        if (_curr)
                            _curr = _curr->_prev;
                    }
                    _T& operator*()
                    {
                        if (_curr)
                            return _curr->_value;
                        return _T();
                    }
                    _self_type* _get_base()
                    {
                        return _curr;
                    }
                    void operator=(const _node_iterator<_T>& l)
                    {
                        _curr = l._get_base();
                    }
            };

            template <class _Type>
            struct _const_node_iterator
            {
                private:
                    typedef const _node<_Type>    _self_type;
                    const _self_type* _curr;

                public:
                    typedef std::ptrdiff_t              difference_type;
                    typedef bidirectional_iterator_tag  iterator_category;
                    typedef _Type                       value_type;
                    typedef const _Type&                reference;
                    typedef const _Type*                pointer;

                    _const_node_iterator(_self_type* e)
                        : _curr(e)
                    {}

                    void operator++()
                    {
                        if (_curr)
                            _curr = _curr->_next;
                    }
                    void operator--()
                    {
                        if (_curr)
                            _curr = _curr->_prev;
                    }
                    _Type& operator*()
                    {
                        if (_curr)
                            return _curr->_value;
                        return _Type();
                    }
                    _self_type* _get_base()
                    {
                        return _curr;
                    }
                    void operator=(const _node_iterator<_Type>& l)
                    {
                        _curr = l._get_base();
                    }
            };

            typedef list<T, Alloc>                              _list_type;
            typedef _node<T>                                    _node_type;
            typedef allocator<_node_type>                       _node_allocator_type;

        public:
            typedef T                                           value_type;
            typedef T&                                          reference;
            typedef const T&                                    const_reference;
            typedef allocator_traits<Alloc>::pointer            pointer;
            typedef allocator_traits<Alloc>::const_pointer      const_pointer;
            typedef Alloc                                       allocator_type;
            typedef _node_iterator<T>                           iterator;
            typedef _const_node_iterator<T>                     const_iterator;
            typedef std_copy::reverse_iterator<iterator>        reverse_iterator;
            typedef std_copy::reverse_iterator<const_iterator>  const_reverse_iterator;
            typedef std::size_t                                 size_type;
            typedef std::ptrdiff_t                              difference_type;

        private:
            _node_type* _head;
            size_type _size;

            constexpr void _copy_list(_node_type* dest, _node_type* src)
            {
                while (src)
                {
                    dest->_value = src->_value;
                    src = src->_next;
                    dest = dest->_next;
                }
            }
            template <class InputIt>
            constexpr void _range_init_list(InputIt first, InputIt last)
            {
                _size = distance(first, last);
                _head->_init(nullptr, nullptr, *first++);
                _node_type* tempHead = _head;
                _size = 1;
                while (first != last)
                {
                    if (_size == size_type(-1))
                        throw std::length_error("Range is too long");
                    _size++;

                    _node_type* attach = _node_allocator_type::allocate(1);
                    attach->_init(tempHead, nullptr, *first);
                    tempHead->_next = attach;
                    tempHead = tempHead->_next;

                    ++first;
                }
            }
            constexpr void _value_init_list(size_type count, const_reference val)
            {
                _head->_init(nullptr, nullptr, val);
                _node_type* tempHead = _head;
                while (1)
                {
                    if (count == 1)
                        break;

                    _node_type* attach = _node_allocator_type::allocate(1);
                    attach->_init(tempHead, nullptr, val);
                    tempHead->_next = attach;
                    tempHead = tempHead->_next;

                    count--;
                }
            }
            void _destroy_list(_node_type* thing)
            {
                _node_type* previous = thing->_prev;
                while (thing)
                {
                    if (thing->_prev)
                        _node_allocator_type::deallocate(previous, 1);

                    thing->_value.~value_type();
                    previous = thing;
                    thing = thing->_next;
                }
                _node_allocator_type::deallocate(previous, 1);
            }

        public:
            list() : _size(0)
            {
                _head = nullptr;
            }

            explicit list(size_type count, const_reference val)
                : _size(count)
            {
                _value_init_list(count, val);
            }

            explicit list(size_type count)
                : _size(count)
            {
                _value_init_list(count, value_type());
            }

            template <class InputIt>
            list(InputIt first, InputIt last)
        #if __cplusplus > 201703L
            requires input_iterator<InputIt>
        #endif
            {
                _range_init_list(first, last);
            }

            list(_list_type&& other)
                : _size(move(other._size)),
                _head(move(other._head))
            {}

            list(const _list_type& other)
                : _size(other._size)
            {
                _copy_list(_head, other._head);
            }

            ~list()
            {
                _destroy_list(_head);
            }

            void _test_print()
            {
                _node_type* temp = _head;
                while (temp)
                {
                    std::cout << temp->_value << '\n';
                    temp = temp->_next;
                }
            }
    };
}

#endif /* _STD_COPY_LIST */