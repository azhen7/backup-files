#ifndef _STD_COPY_FORWARD_LIST
#define _STD_COPY_FORWARD_LIST

#include "allocator.hpp"
#include "allocator_traits.hpp"
#include <cstdint>

namespace _std_copy_hidden
{
    namespace _std_copy_forward_list
    {
        template <class _T>
        struct _node
        {
            private:
                typedef _node<_T>   _self_type;

            public:
                _self_type* _next;
                _T _value;

                void _init(_self_type* n, const _T& val)
                {
                    _next = n;
                    _value = val;
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
                typedef std_copy::forward_iterator_tag iterator_category;
                typedef _T value_type;
                typedef _T& reference;
                typedef _T* pointer;

                _node_iterator(_node_type* e, _node_type* _prev_if_needed = nullptr)
                    : _curr(e)
                {
                }

                _self_type operator++()
                {
                    if (!_curr) return *this;

                    _curr = _curr->_next;
                    return *this;
                }
                _self_type operator++(int)
                {
                    if (!_curr) return *this;

                    _self_type temp = *this;
                    _curr = _curr->_next;
                    return temp;
                }
                _T& operator*()
                {
                    if (!_curr) throw std::bad_alloc();

                    return _curr->_value;
                }
                _node_type* base()
                {
                    return _curr;
                }
                void operator=(const _self_type& l)
                {
                    _curr = l._curr;
                }
                bool operator==(const _self_type& l)
                {
                    return _curr == l._curr;
                }
                bool operator!=(const _self_type& l)
                {
                    return !(*this == l);
                }
        };


        template <class _Type>
        struct _const_node_iterator
        {
            private:
                typedef const _node<_Type> _node_type;
                typedef _const_node_iterator<_Type> _self_type;
                const _node_type* _curr;

            public:
                typedef std::ptrdiff_t difference_type;
                typedef std_copy::forward_iterator_tag iterator_category;
                typedef _Type value_type;
                typedef const _Type& reference;
                typedef const _Type* pointer;

                _const_node_iterator(_node_type *e, _node_type* p)
                    : _curr(e)
                {
                }

                _self_type operator++()
                {
                    if (!_curr) return *this;

                    _curr = _curr->_next;
                    return *this;
                }
                _self_type operator++(int)
                {
                    if (!_curr) return *this;

                    _self_type temp = *this;
                    _curr = _curr->_next;
                    return temp;
                }
                _Type& operator*()
                {
                    if (!_curr) throw std::bad_alloc();

                    return _curr->_value;
                }
                _node_type* base()
                {
                    return _curr;
                }
                void operator=(const _node_iterator<_Type> &l)
                {
                    _curr = l._curr;
                }
                bool operator==(const _node_iterator<_Type> &l)
                {
                    return _curr == l._curr;
                }
                bool operator!=(const _node_iterator<_Type> &l)
                {
                    return !(*this == l);
                }
        };
    }
}

namespace std_copy
{
    /**
     * An implementation of std::forward_list, defined in the header file <forward_list>.
     * @param T The type of the elements.
     * @param Alloc The type of the object used to allocate the underlying buffer
     * used for containing the values.
     */
    template <class T, class Alloc = allocator<T>>
    class forward_list
    {
        private:
            typedef forward_list<T, Alloc>                                              _forward_list_type;
            typedef _std_copy_hidden::_std_copy_forward_list::_node<T>                  _node_type;
            typedef allocator<_node_type>                                               _node_allocator_type;

        public:
            typedef T                                                                   value_type;
            typedef Alloc                                                               allocator_type;
            typedef T&                                                                  reference;
            typedef const T&                                                            const_reference;
            typedef allocator_traits<Alloc>::pointer                                    pointer;
            typedef allocator_traits<Alloc>::const_pointer                              const_pointer;
            typedef std::size_t                                                         size_type;
            typedef std::ptrdiff_t                                                      difference_type;
            typedef _std_copy_hidden::_std_copy_forward_list::_node_iterator<T>         iterator;
            typedef _std_copy_hidden::_std_copy_forward_list::_const_node_iterator<T>   const_iterator;

        private:


        public:
            
    };
}


#endif /* _STD_COPY_FORWARD_LIST */