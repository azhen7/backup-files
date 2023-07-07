#ifndef _LIST_ITERATORS
#define _LIST_ITERATORS

#include "move.hpp"
#include "iterator_traits.hpp"

namespace _std_copy_hidden
{
    namespace _std_copy_forward_list_iterators
    {
        template <class _T>
        struct _node
        {
            private:
                typedef _node<_T> _self_type;
            public:
                _self_type* _next;
                _T _value;

                void _init(_self_type* n, const _T& v)
                {
                    _value = v;
                    _next = n;
                }
        };
    }
    namespace _std_copy_list_iterators
    {
        template <class _Type>
        struct _node
        {
            private:
                typedef _node<_Type> _self_type;

            public:
                _self_type *_next;
                _self_type *_prev;

                _Type _value;

                void _init(_self_type* p, _self_type* n, const _Type& val)
                {
                    _prev = p;
                    _next = n;
                    _value = std_copy::move(val);
                }
        };

        template <class _T>
        struct _node_iterator
        {
            private:
                typedef _node<_T> _node_type;
                typedef _node_iterator<_T> _self_type;
                _node_type* _curr;

            public:
                typedef std::ptrdiff_t difference_type;
                typedef std_copy::bidirectional_iterator_tag iterator_category;
                typedef _T value_type;
                typedef _T& reference;
                typedef _T* pointer;

                _node_iterator(_node_type* e)
                    : _curr(e)
                {
                }

                _self_type operator++() noexcept
                {
                    _curr = _curr->_next;
                    return *this;
                }
                _self_type operator++(int) noexcept
                {
                    _self_type temp = *this;
                    _curr = _curr->_next;
                    return temp;
                }
                _self_type operator--() noexcept
                {
                    _curr = _curr->_prev;
                    return *this;
                }
                _self_type operator--(int) noexcept
                {
                    _self_type temp = *this;
                    _curr = _curr->_prev;
                    return temp;
                }
                _T& operator*() const noexcept
                {
                    return _curr->_value;
                }
                _node_type* base() const noexcept
                {
                    return _curr;
                }
                void operator=(const _self_type& l)
                {
                    _curr = l._curr;
                }
                friend bool operator==(const _self_type& a, const _self_type& l)
                {
                    return a._curr == l._curr;
                }
                friend bool operator!=(const _self_type& a, const _self_type& l)
                {
                    return !(a == l);
                }
        };


        template <class _T>
        struct _const_node_iterator
        {
            private:
                typedef const _node<_T> _node_type;
                typedef _const_node_iterator<_T> _self_type;
                const _node_type* _curr;

            public:
                typedef std::ptrdiff_t difference_type;
                typedef std_copy::bidirectional_iterator_tag iterator_category;
                typedef _T value_type;
                typedef const _T& reference;
                typedef const _T* pointer;

                _const_node_iterator(_node_type *e)
                    : _curr(e)
                {
                }

                _self_type operator++() noexcept
                {
                    _curr = _curr->_next;
                    return *this;
                }
                _self_type operator++(int) noexcept
                {
                    _self_type temp = *this;
                    _curr = _curr->_next;
                    return temp;
                }
                _self_type operator--() noexcept
                {
                    _curr = _curr->_prev;
                    return *this;
                }
                _self_type operator--(int) noexcept
                {
                    _self_type temp = *this;
                    _curr = _curr->_prev;
                    return temp;
                }
        
                _T& operator*() const noexcept
                {
                    return _curr->_value;
                }
                _node_type* base() const noexcept
                {
                    return _curr;
                }
                void operator=(const _node_iterator<_T> &l)
                {
                    _curr = l._curr;
                }
                friend bool operator==(const _self_type& a, const _self_type& l)
                {
                    return a._curr == l._curr;
                }
                friend bool operator!=(const _self_type& a, const _self_type& l)
                {
                    return !(a == l);
                }
        };
    }
};

#endif /* _LIST_ITERATORS */